#include "motor_driver.h"
#include "py32_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static const char *TAG = "motor_driver";

// PWM 配置 (通过PY32 I2C扩展器)
#define MOTOR_PWM_FREQ        1000    // PWM频率Hz (PY32固定为1KHz)

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
    .duration_ms = 100,
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
            
            // 使用PY32驱动启用电机PWM
            if (cmd.intensity > 0) {
                esp_err_t ret = py32_motor_enable(cmd.intensity);
                if (ret != ESP_OK) {
                    ESP_LOGE(TAG, "Failed to enable motor: %s", esp_err_to_name(ret));
                    continue;
                }
            }
            
            // 等待指定时间
            vTaskDelay(cmd.duration_ms / portTICK_PERIOD_MS);
            
            // 关闭电机
            esp_err_t ret = py32_motor_enable(0);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "Failed to disable motor: %s", esp_err_to_name(ret));
            }
        }
    }
}

void motor_init()
{
    ESP_LOGI(TAG, "motor_init - using PY32 I2C expander PWM");
    
    // 注意：PWM引脚配置现在由PY32驱动管理
    // GPIO_PIN_10 (PA7-IO10) 用于电机PWM控制
    
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
    
    // 确保电机初始状态为关闭
    esp_err_t ret = py32_motor_enable(0);
    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "Failed to disable motor during init: %s", esp_err_to_name(ret));
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

// 立即停止电机
void motor_stop()
{
    if (motor_cmd_queue != NULL) {
        // 清空队列
        xQueueReset(motor_cmd_queue);
    }
    
    // 通过PY32驱动禁用电机PWM
    esp_err_t ret = py32_motor_disable();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to stop motor: %s", esp_err_to_name(ret));
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

// PWM频率控制
esp_err_t motor_set_frequency(uint16_t frequency)
{
    ESP_LOGI(TAG, "设置电机PWM频率: %d Hz", frequency);
    return py32_motor_set_frequency(frequency);
}

esp_err_t motor_get_frequency(uint16_t *frequency)
{
    if (frequency == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    
    esp_err_t ret = py32_motor_get_frequency(frequency);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "当前电机PWM频率: %d Hz", *frequency);
    }
    return ret;
}

// PWM状态读取
esp_err_t motor_get_pwm_status(uint8_t *duty_percent, bool *polarity, bool *enable)
{
    if (duty_percent == NULL || polarity == NULL || enable == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    
    esp_err_t ret = py32_motor_get_pwm(duty_percent, polarity, enable);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "电机PWM状态: 占空比=%d%%, 极性=%s, 使能=%s", 
                 *duty_percent, *polarity ? "低电平有效" : "高电平有效", *enable ? "是" : "否");
    }
    return ret;
}