#include "motor_driver.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static const char *TAG = "motor_driver";

// PWM 配置
#define MOTOR_PWM_FREQ        5000    // PWM频率Hz
#define MOTOR_PWM_RESOLUTION  LEDC_TIMER_10_BIT  // 分辨率10位(0-1023)
#define MOTOR_PWM_CHANNEL     LEDC_CHANNEL_0     // 使用通道0
#define MOTOR_PWM_TIMER       LEDC_TIMER_0       // 使用定时器0

// 电机任务配置
#define MOTOR_TASK_STACK_SIZE 4096
#define MOTOR_TASK_PRIORITY   configMAX_PRIORITIES - 1

// 电机控制命令结构体
typedef struct {
    uint32_t intensity;  // 0-100强度百分比
    uint32_t duration_ms; // 持续时间(ms)
    uint32_t interval_ms; // 间隔时间(ms)
} motor_cmd_t;

motor_cmd_t motor_button_cmd = {
    .intensity = 100,
    .duration_ms = 50,
    .interval_ms = 500,
};

// 任务句柄和队列
static TaskHandle_t motor_task_handle = NULL;
static QueueHandle_t motor_cmd_queue = NULL;

// 电机任务函数
static void motor_task(void *arg)
{
    motor_cmd_t cmd;
    
    while (1) {
        // 等待命令
        if (xQueueReceive(motor_cmd_queue, &cmd, portMAX_DELAY)) {
            ESP_LOGI(TAG, "Motor command received: intensity=%ld%%, duration=%ldms", cmd.intensity, cmd.duration_ms);
            
            // 限制强度范围
            if (cmd.intensity > 100) cmd.intensity = 100;
            
            // 计算PWM值 (0-1023)
            uint32_t pwm_value = (cmd.intensity * 1023) / 100;
            
            // 设置PWM占空比
            ledc_set_duty(LEDC_LOW_SPEED_MODE, MOTOR_PWM_CHANNEL, pwm_value);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, MOTOR_PWM_CHANNEL);
            
            // 等待指定时间
            vTaskDelay(cmd.duration_ms / portTICK_PERIOD_MS);
            
            // 关闭电机
            ledc_set_duty(LEDC_LOW_SPEED_MODE, MOTOR_PWM_CHANNEL, 0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, MOTOR_PWM_CHANNEL);
        }
    }
}

void motor_init()
{
    ESP_LOGI(TAG, "motor_init");
    
    // 配置GPIO
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << MOTOR_ENABLE_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&io_conf);
    
    // 配置LEDC PWM
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = MOTOR_PWM_TIMER,
        .duty_resolution = MOTOR_PWM_RESOLUTION,
        .freq_hz = MOTOR_PWM_FREQ,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);
    
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = MOTOR_PWM_CHANNEL,
        .timer_sel = MOTOR_PWM_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = MOTOR_ENABLE_PIN,
        .duty = 0,  // 初始占空比为0
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
    
    // 创建电机命令队列
    motor_cmd_queue = xQueueCreate(5, sizeof(motor_cmd_t));
    if (motor_cmd_queue == NULL) {
        ESP_LOGE(TAG, "Failed to create motor command queue");
        return;
    }
    
    // 创建电机控制任务
    xTaskCreate(motor_task, "motor_task", MOTOR_TASK_STACK_SIZE, NULL, 
                MOTOR_TASK_PRIORITY, &motor_task_handle);
    if (motor_task_handle == NULL) {
        ESP_LOGE(TAG, "Failed to create motor control task");
        vQueueDelete(motor_cmd_queue);
        motor_cmd_queue = NULL;
        return;
    }
    
    ESP_LOGI(TAG, "Motor driver initialized successfully");
}

// 控制电机运行，参数：强度(0-100)，持续时间(ms)
esp_err_t motor_run(uint8_t intensity, uint32_t duration_ms)
{
    if (motor_cmd_queue == NULL) {
        ESP_LOGE(TAG, "Motor driver not initialized");
        return ESP_ERR_INVALID_STATE;
    }
    
    motor_cmd_t cmd = {
        .intensity = intensity,
        .duration_ms = duration_ms
    };
    
    if (xQueueSend(motor_cmd_queue, &cmd, pdMS_TO_TICKS(100)) != pdPASS) {
        ESP_LOGE(TAG, "Failed to send motor command");
        return ESP_FAIL;
    }
    
    return ESP_OK;
}

// 按钮震动 中断中调用
esp_err_t button_vibrate(void)
{
    static uint32_t last_vibrate_time = 0;
    uint32_t current_time = xTaskGetTickCountFromISR() * portTICK_PERIOD_MS;
    
    if (motor_cmd_queue == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    
    // 检查是否距离上次震动超过1秒
    if (current_time - last_vibrate_time < motor_button_cmd.interval_ms) {
        return ESP_OK;
    }
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    UBaseType_t waiting_msgs = uxQueueMessagesWaitingFromISR(motor_cmd_queue);
    if (waiting_msgs > 0) {
        return ESP_OK;
    }
    
    if (xQueueSendFromISR(motor_cmd_queue, &motor_button_cmd, &xHigherPriorityTaskWoken) != pdPASS) {
        return ESP_FAIL;
    }
    
    last_vibrate_time = current_time;
    
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    return ESP_OK;
}

void set_vibrate_cmd(uint8_t intensity, uint32_t duration_ms, uint32_t interval_ms)
{
    motor_button_cmd.intensity = intensity;
    motor_button_cmd.duration_ms = duration_ms;
    motor_button_cmd.interval_ms = interval_ms;
}

void get_vibrate_cmd(uint8_t *intensity, uint32_t *duration_ms, uint32_t *interval_ms)
{
    *intensity = motor_button_cmd.intensity;
    *duration_ms = motor_button_cmd.duration_ms;
    *interval_ms = motor_button_cmd.interval_ms;
}

// 立即停止电机
void motor_stop()
{
    if (motor_cmd_queue != NULL) {
        // 清空队列
        xQueueReset(motor_cmd_queue);
        
        // 设置PWM占空比为0
        ledc_set_duty(LEDC_LOW_SPEED_MODE, MOTOR_PWM_CHANNEL, 0);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, MOTOR_PWM_CHANNEL);
    }
}

void motor_enable()
{
    motor_run(100, 100); // 默认100%强度，持续0.1秒
}

void motor_disable()
{
    motor_stop();
}