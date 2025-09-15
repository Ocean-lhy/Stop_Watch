extern "C"
{
#include <math.h>
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/rtc_io.h"
#include "esp_timer.h"
#include "i2c_bus.h"
#include "esp_sleep.h"
#include "esp_littlefs.h"

// 导入模块化的驱动
#include "system_utils.h"
#include "motor_driver.h"
#include "bmi270_driver.h"
#include "es8311_driver.h"
#include "touch_driver.h"
#include "lcd_driver.h"
#include "rx8130ce.h"
#include "time_utils.h"
#include "py32_driver.h"
#include "io_expander.h"

}

#include "m5_stamp_pm1.h"
#include "m5_stamp_pm1_class.h"

extern "C"
{

#include "gui_guider.h"
#include "custom.h"

#define TAG "main"

// extern const uint8_t test_pcm_start[] asm("_binary_test_pcm_start");
// extern const uint8_t test_pcm_end[]   asm("_binary_test_pcm_end");

m5_stamp_pm1& pm1 = m5_stamp_pm1::getInstance();

lv_ui guider_ui;
i2c_bus_handle_t i2c_bus = NULL;
static uint64_t last_update_time = 0;

uint8_t battery_level = 50; // 0-100
uint16_t current = 500;
float voltage = 4.2;
int accel_x = 0;
int accel_y = 0;
int accel_z = 0;
int gyro_x = 0;
int gyro_y = 0;
int gyro_z = 0;
uint8_t charge_status = 0;

bool vin_det = false;

// 录音和播放标志
extern bool is_recording;
extern bool is_playing;
uint32_t recording_start_time = 0;

SemaphoreHandle_t touch_mux = NULL;
extern touch_point_t lv_touch_data;

// 当前界面类型
typedef enum {
    SCREEN_LOGO = 0,
    SCREEN_TIME,
    SCREEN_INFO,
    SCREEN_VIBRA,
    SCREEN_VOICE,
    SCREEN_IMG,
    SCREEN_UNKNOWN
} screen_type_t;

screen_type_t current_screen = SCREEN_UNKNOWN;
static bool update_data = false;

// 长按检测相关变量
static bool btn1_pressed = false;
static uint64_t btn1_press_start_time = 0;
static const uint64_t LONG_PRESS_DURATION = 3000000; // 3秒，单位微秒
static bool long_press_triggered = false;

// 函数声明
void sleep_mode(uint8_t sleep_mode);
void update_screen_data(void);
screen_type_t get_current_screen(void);

// 时间同步任务函数
void time_sync_task()
{
    // 初始化时间模块
    time_utils_init();
    
    // 连接WiFi
    esp_err_t ret = time_utils_connect_wifi(WIFI_SSID, WIFI_PASSWORD);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "连接WiFi失败，无法同步时间");
        vTaskDelete(NULL);
        return;
    }
    
    // 同步网络时间
    ret = time_utils_sync_ntp();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "同步网络时间失败");
        time_utils_disconnect_wifi();
        vTaskDelete(NULL);
        return;
    }
    
    // 校准RTC时间
    ret = time_utils_calibrate_rtc();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "校准RTC时间失败");
    }
    
    // 断开WiFi
    time_utils_disconnect_wifi();
    
    // 获取当前时间并打印
    rx8130_datetime_t current_time;
    if (time_utils_get_time(&current_time) == ESP_OK) {
        ESP_LOGI(TAG, "当前RTC时间: %02d/%02d/%02d %02d:%02d:%02d 星期%d",
                 current_time.year, current_time.month, current_time.date,
                 current_time.hour, current_time.minute, current_time.second,
                 current_time.day);
    }
    
    // 任务完成，删除自身
    // vTaskDelete(NULL);
}

void update_time(void *pvParameters)
{
    time_utils_time_t current_time_ms;
    while (1)
    {
        if (time_utils_get_time_ms(&current_time_ms) == ESP_OK)
        {
            // screen_ccw_digital_clock_s_hour_value = current_time_ms.datetime.hour;
            // screen_ccw_digital_clock_s_min_value = current_time_ms.datetime.minute;
            // screen_ccw_digital_clock_s_sec_value = current_time_ms.datetime.second;
            // screen_ccw_digital_clock_s_ms_value = current_time_ms.milliseconds;
            // screen_clock_digital_clock_s_hour_value = current_time_ms.datetime.hour;
            // screen_clock_digital_clock_s_min_value = current_time_ms.datetime.minute;
            // screen_clock_digital_clock_s_sec_value = current_time_ms.datetime.second;
            // screen_clock_s_year = current_time_ms.datetime.year + 2000;
            // screen_clock_s_month = current_time_ms.datetime.month;
            // screen_clock_s_day = current_time_ms.datetime.date;
            // if (current_time_ms.datetime.hour < 12)
            // {
            //     strcpy(screen_clock_digital_clock_s_meridiem, "AM");
            // }
            // else
            // {
            //     strcpy(screen_clock_digital_clock_s_meridiem, "PM");
            // }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    size_t psram_size = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
    size_t psram_free = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    printf("PSRAM size: %d bytes, free: %d bytes\n", psram_size, psram_free);

    // 初始化NVS存储
    nvs_init();
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    printf("app main start\r\n");

    // 打印芯片信息
    print_chip_info();

    // 创建触摸互斥量
    touch_mux = xSemaphoreCreateBinary();
    assert(touch_mux);

    for(int i = 0; i < 47; i++) {
        int ret = gpio_hold_dis((gpio_num_t)i);
        ESP_LOGI(TAG, "gpio_hold_dis(%d) = %d", i, ret);
    }
    gpio_deep_sleep_hold_dis();

    // 初始化全局中断
    // global_irq_init();

    gpio_config_t io_11 = {
        .pin_bit_mask = (1ULL << GPIO_NUM_11),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_11);
    gpio_set_level(GPIO_NUM_11, 0);
    
    // 初始化I2C总线
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_SDA_PIN;
    conf.scl_io_num = I2C_SCL_PIN;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_FREQ;
    conf.clk_flags = 0;
    i2c_bus = i2c_bus_create(I2C_NUM_0, &conf);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    uint8_t i2c_addr[128] = {0};
    i2c_bus_scan(i2c_bus, i2c_addr, 0);
    for (int i = 0; i < 128; i++) 
    {
        if (i2c_addr[i] != 0) 
        {
            ESP_LOGI(TAG, "i2c_addr[%d] = 0x%02x", i, i2c_addr[i]);
        }
    }

    i2c_bus_device_handle_t pm1_dev = i2c_bus_device_create(i2c_bus, PM1_ADDR, 100000);
    pm1.pm1_init(i2c_bus, &pm1_dev, 100000);
    pm1_btn_set_cfg(PM1_ADDR_BTN_TYPE_CLICK, PM1_ADDR_BTN_CLICK_DELAY_1000MS);  // 单击延迟1秒
    pm1_wdt_set(PM1_WDT_CTRL_DISABLE, 0);  // 禁用WDT

    pm1_pwr_set_cfg(PM1_PWR_CFG_5V_INOUT, PM1_PWR_CFG_5V_INOUT, NULL);  // 设置5VINOUT使能
    pm1_pwr_set_cfg(PM1_PWR_CFG_CHG_EN, PM1_PWR_CFG_CHG_EN, NULL);  // 设置充电使能
    pm1_gpio_set_mode(PM1_GPIO_NUM_1, PM1_GPIO_MODE_INPUT); // 充电检测引脚设置为输入

    // pm1_gpio_set_mode(PM1_GPIO_NUM_2, PM1_GPIO_MODE_OUTPUT); // G12 wakeup esp32s3

    // pm1_gpio_set(PM1_GPIO_NUM_3, PM1_GPIO_MODE_INPUT, PM1_GPIO_INPUT_NC, PM1_GPIO_PUPD_NC, PM1_GPIO_DRV_OPEN_DRAIN);
    pm1_gpio_set(PM1_GPIO_NUM_3, PM1_GPIO_MODE_OUTPUT, PM1_GPIO_OUTPUT_HIGH, PM1_GPIO_PUPD_NC, PM1_GPIO_DRV_PUSH_PULL); // low: quick charge, high r: normal charge

    // pm1_irq_clear_gpio_flag(PM1_ADDR_IRQ_GPIO_ALL);
    // pm1_irq_clear_sys_status(PM1_ADDR_IRQ_SYS_ALL);
    // pm1_gpio_set_func(PM1_GPIO_NUM_2, PM1_GPIO_FUNC_IRQ);
    // vTaskDelay(500 / portTICK_PERIOD_MS);
    // pm1_gpio_set_mode(PM1_GPIO_NUM_0, PM1_GPIO_MODE_INPUT); // rtc wakeup
    // pm1_gpio_set_pupd(PM1_GPIO_NUM_0, PM1_GPIO_PUPD_PULLDOWN);
    // pm1_gpio_set_drv(PM1_GPIO_NUM_0, PM1_GPIO_DRV_PUSH_PULL);
    // pm1_gpio_set_wake_en(PM1_GPIO_NUM_0, PM1_GPIO_WAKE_ENABLE);
    // pm1_gpio_set_wake_cfg(PM1_GPIO_NUM_0, PM1_GPIO_WAKE_FALLING);
    // pm1_gpio_set_mode(PM1_GPIO_NUM_4, PM1_GPIO_MODE_INPUT); // IMU wakeup
    // pm1_gpio_set_pupd(PM1_GPIO_NUM_4, PM1_GPIO_PUPD_PULLDOWN);
    // pm1_gpio_set_drv(PM1_GPIO_NUM_4, PM1_GPIO_DRV_PUSH_PULL);
    // pm1_gpio_set_wake_en(PM1_GPIO_NUM_4, PM1_GPIO_WAKE_ENABLE);
    // pm1_gpio_set_wake_cfg(PM1_GPIO_NUM_4, PM1_GPIO_WAKE_FALLING);

    pm1_wake_src_t wake_src;
    pm1_wake_src_read(&wake_src, PM1_ADDR_WAKE_FLAG_ALL_CLEAN);
    if (wake_src == PM1_WAKE_SRC_UNKNOWN || wake_src == PM1_WAKE_SRC_NULL)
    {
        ESP_LOGE(TAG, "wake_src is unknown or null");
    }
    else
    {
        if (wake_src & PM1_WAKE_SRC_TIM)
        {
            ESP_LOGI(TAG, "wake_src is TIMER");
        }
        if (wake_src & PM1_WAKE_SRC_VIN)
        {
            ESP_LOGI(TAG, "wake_src is VIN");
        }
        if (wake_src & PM1_WAKE_SRC_PWRBTN)
        {
            ESP_LOGI(TAG, "wake_src is PWRBTN");
        }
        if (wake_src & PM1_WAKE_SRC_RSTBTN)
        {
            ESP_LOGI(TAG, "wake_src is RSTBTN");
        }
        if (wake_src & PM1_WAKE_SRC_CMD_RST)
        {
            ESP_LOGI(TAG, "wake_src is CMD_RST");
        }
        if (wake_src & PM1_WAKE_SRC_EXT_WAKE)
        {
            ESP_LOGI(TAG, "wake_src is EXT_WAKE");
        }
        if (wake_src & PM1_WAKE_SRC_5VINOUT)
        {
            ESP_LOGI(TAG, "wake_src is 5VINOUT");
        }
    }

    py32_init(i2c_bus);

    ESP_LOGI(TAG, "motor_init");
    motor_init();
    
    ESP_LOGI(TAG, "touch init");
    touch_driver_init(i2c_bus);

    // 创建时间同步任务
    // time_sync_task();
    // xTaskCreate(update_time, "update_time", 4096, NULL, 5, NULL);
    
    // LCD
    ESP_LOGI(TAG, "lcd_init");
    lcd_init();
    
    // RX8130
    ESP_LOGI(TAG, "RX8130 init");
    rx8130_init(i2c_bus);
    
    // IMU
    ESP_LOGI(TAG, "bmi270_dev_init");
    // bmi270_dev_init(i2c_bus);
    i2c_bus_device_handle_t i2c_dev_handle_bmi270 = i2c_bus_device_create(i2c_bus, 0x68, 100000);
    if (i2c_dev_handle_bmi270 == NULL)
    {
        ESP_LOGE(TAG, "i2c_dev_handle_bmi270 create failed");
    }
    uint8_t reg_data[1] = {0x01};
    i2c_bus_write_reg(i2c_dev_handle_bmi270, 0x7C, 1, reg_data, 1);
    reg_data[0] = 0x00;
    i2c_bus_write_reg(i2c_dev_handle_bmi270, 0x7D, 1, reg_data, 1);

    // ES8311 音频
    ESP_LOGI(TAG, "es8311_driver_init");
    es8311_driver_init(i2c_bus);
    es8311_stop();

    // LCD
    ESP_LOGI(TAG, "lcd_init");
    lcd_init();
    lcd_set_sleep(true);

    // cst820
    ESP_LOGI(TAG, "cst820_init");
    i2c_bus_device_handle_t cst820_dev = i2c_bus_device_create(i2c_bus, 0x15, 100000);
    if (cst820_dev == NULL)
    {
        ESP_LOGE(TAG, "cst820_dev create failed");
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
    uint8_t i2c_buf[1] = {0x03};
    i2c_bus_write_reg(cst820_dev, 0xE5, 1, i2c_buf, 1); // 进入休眠

    esp_err_t ret = py32_sleep(1);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to sleep: %s", esp_err_to_name(ret));
    }

    spi_bus_free(LCD_HOST);
    i2c_bus_delete(&i2c_bus);

    gpio_reset_pin((gpio_num_t)I2C_SDA_PIN);
    gpio_reset_pin((gpio_num_t)I2C_SCL_PIN);
    gpio_set_pull_mode((gpio_num_t)I2C_SDA_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode((gpio_num_t)I2C_SCL_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_level((gpio_num_t)I2C_SDA_PIN, 0);
    gpio_set_level((gpio_num_t)I2C_SCL_PIN, 0);

    // bool timer_triggered = false;
    // rx8130_is_timer_triggered(&timer_triggered);
    // if (timer_triggered) {
    //     ESP_LOGI(TAG, "定时器已经触发");
    //     rx8130_clear_timer_flag();
    // }
    // else
    // {
    //     ESP_LOGI(TAG, "定时器未触发");
    //     rx8130_set_shutdown_timer_mode(30);
    //     power_off();
    // }
    // rx8130_enable_timer(true);

    rtc_gpio_isolate((gpio_num_t)GPIO_NUM_1);   // KEY1
    rtc_gpio_isolate((gpio_num_t)GPIO_NUM_2);   // KEY2
    rtc_gpio_isolate((gpio_num_t)GPIO_NUM_21);  // TP_INT
    rtc_gpio_isolate((gpio_num_t)GPIO_NUM_13);  // IMU_INT

    gpio_reset_pin((gpio_num_t)GPIO_NUM_39);  // OLED_CS
    gpio_set_direction((gpio_num_t)GPIO_NUM_39, GPIO_MODE_INPUT);
    
    gpio_reset_pin((gpio_num_t)GPIO_NUM_11);  // MOS_Q10
    gpio_set_direction((gpio_num_t)GPIO_NUM_11, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)GPIO_NUM_11, 1);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_deep_sleep_hold_en();
    esp_deep_sleep_start();
    
    ESP_LOGI(TAG, "Start main loop");
    while (1)
    {
        // 定期更新状态
        if (esp_timer_get_time() - last_update_time > 500 * 1000)
        {
            last_update_time = esp_timer_get_time();
            
            // 更新加速度计和陀螺仪数据
            bmi270_dev_update();
            bmi270_get_data(&accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z);
            
            pm1_gpio_in_state_t gpio_state;
            pm1_gpio_get_in_state(PM1_GPIO_NUM_1, &gpio_state); // low charge, high no charge
            ESP_LOGI(TAG, "charge status = %d", gpio_state);
            charge_status = gpio_state == PM1_GPIO_IN_STATE_LOW ? 2 : 0;

            uint16_t vbat_value;
            pm1_vbat_read(&vbat_value);
            voltage = vbat_value / 1000;

            uint16_t vref_value;
            pm1_vref_read(&vref_value);

            uint16_t vin_value;
            pm1_vin_read(&vin_value);
            current = vin_value;

            uint16_t _5vinout_value;
            pm1_5vinout_read(&_5vinout_value);

            update_data = true;
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        

        // 按键处理（带长按检测）
        if (gpio_get_level(USER_BUTTON1_PIN) == 0)
        {
            ESP_LOGI(TAG, "btn1 pressed");

            if (!btn1_pressed)
            {
                // 按键刚被按下
                btn1_pressed = true;
                btn1_press_start_time = esp_timer_get_time();
                long_press_triggered = false;
                printf("btn1 pressed, starting long press timer\n");
            }
            else
            {
                // 按键持续按下，检查是否达到长按时间
                uint64_t current_time = esp_timer_get_time();
                if (!long_press_triggered && 
                    (current_time - btn1_press_start_time) >= LONG_PRESS_DURATION)
                {
                    long_press_triggered = true;
                    printf("btn1 long press detected! Starting BMI270 deep sleep demo...\n");
                    // 调用BMI270深度睡眠唤醒demo
                    bmi270_INT_wakeup_deepsleep_test();
                }
            }
        }
        else
        {
            if (btn1_pressed)
            {
                // test grove i2c expander
                py32_mux_mode_t mode = PY32_MUX_MODE_U0;
                py32_mux_get_mode(&mode);
                ESP_LOGI(TAG, "grove mode = %d", mode);
                if (mode == PY32_MUX_MODE_U0)
                {
                    mode = PY32_MUX_MODE_USB;
                    py32_mux_set_mode(mode);
                    pm1_pwr_set_cfg(PM1_PWR_CFG_CHG_EN, 0, NULL);
                    ESP_LOGI(TAG, "IO mode = %d", mode);
                }
                else
                {
                    mode = PY32_MUX_MODE_U0;
                    py32_mux_set_mode(mode);

                    pm1_pwr_set_cfg(PM1_PWR_CFG_CHG_EN, PM1_PWR_CFG_CHG_EN, NULL);
                    
                    ESP_LOGI(TAG, "IO mode = %d", mode);
                }
                // 按键被释放
                btn1_pressed = false;
                uint64_t press_duration = esp_timer_get_time() - btn1_press_start_time;
                
                if (!long_press_triggered && press_duration < LONG_PRESS_DURATION)
                {
                    // 短按处理
                    printf("btn1 short press (duration: %llu ms)\n", press_duration / 1000);
                    if (example_lvgl_lock(-1))
                    {
                        uint8_t key = 2;
                        lv_obj_t *current = lv_scr_act();
                        lv_event_send(current, LV_EVENT_KEY, &key);
                        example_lvgl_unlock();
                    }
                }
                else if (long_press_triggered)
                {
                    printf("btn1 long press completed (duration: %llu ms)\n", press_duration / 1000);
                }
            }
        } 
        if (btn2)
        {
            printf("btn2 pressed\n");
            
            btn2 = 0;
            if (example_lvgl_lock(-1))
            {
                uint8_t key = 1;
                lv_obj_t *current = lv_scr_act();
                lv_event_send(current, LV_EVENT_KEY, &key);
                example_lvgl_unlock();
            }
        }

        update_screen_data();

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

// 获取当前屏幕
screen_type_t get_current_screen(void)
{
    lv_obj_t *current_scr = lv_scr_act();
    
    if (current_scr == guider_ui.screen_logo) {
        return SCREEN_LOGO;
    } else if (current_scr == guider_ui.screen_time) {
        return SCREEN_TIME;
    } else if (current_scr == guider_ui.screen_info) {
        return SCREEN_INFO;
    } else if (current_scr == guider_ui.screen_vibra) {
        return SCREEN_VIBRA;
    } else if (current_scr == guider_ui.screen_voice) {
        return SCREEN_VOICE;
    } else if (current_scr == guider_ui.screen_img) {
        return SCREEN_IMG;
    }
    
    return SCREEN_UNKNOWN;
}

// 更新屏幕数据
void update_screen_data(void)
{
    static char battery_level_buffer[32];
    static char current_buffer[32];
    static char accel_buffer[32];
    static char gyro_buffer[32];
    static char touch_buffer[32];
    static char charge_buffer[32];
    static char record_time_buffer[32];
    current_screen = get_current_screen();
    if (example_lvgl_lock(20))
    {
        switch (current_screen) {
            case SCREEN_LOGO:
                // Logo 界面通常不需要更新数据
                break;
                
            case SCREEN_TIME:
                // 更新时间相关数据
                // 时间日期信息
                {
                    if (update_data)
                    {
                        if (lv_obj_is_valid(guider_ui.screen_time_label_battery) && guider_ui.screen_time_label_battery != NULL) 
                        {
                            sprintf(battery_level_buffer, "%d%% %.1fV", battery_level, voltage);
                            lv_label_set_text_static(guider_ui.screen_time_label_battery, battery_level_buffer);
                        }
                        if (lv_obj_is_valid(guider_ui.screen_time_bar_battery) && guider_ui.screen_time_bar_battery != NULL)
                        {
                            lv_bar_set_value(guider_ui.screen_time_bar_battery, battery_level, LV_ANIM_OFF);
                        }
                        update_data = false;
                    }
                }
                break;
                
            case SCREEN_INFO:
                // 更新信息页面的数据
                // 电池信息
                if (update_data)
                {
                    if (lv_obj_is_valid(guider_ui.screen_info_label_battery) && guider_ui.screen_info_label_battery!= NULL) 
                    {
                        sprintf(battery_level_buffer, "%d%% %.1fV", battery_level, voltage);
                        lv_label_set_text_static(guider_ui.screen_info_label_battery, battery_level_buffer);
                    }
                    if (lv_obj_is_valid(guider_ui.screen_info_bar_battery) && guider_ui.screen_info_bar_battery != NULL)
                    {
                        lv_bar_set_value(guider_ui.screen_info_bar_battery, battery_level, LV_ANIM_OFF);
                    }
                    
                    if (lv_obj_is_valid(guider_ui.screen_info_label_current) && guider_ui.screen_info_label_current != NULL) 
                    {
                        sprintf(current_buffer, "vin: %d", current);
                        lv_label_set_text_static(guider_ui.screen_info_label_current, current_buffer);
                    }

                    if (lv_obj_is_valid(guider_ui.screen_info_label_charge) && guider_ui.screen_info_label_charge != NULL) 
                    {
                        const char* vin_str = vin_det ? ",vin" : ",no vin";
                        if (charge_status == 0)
                        {
                            strcpy(charge_buffer, "bat not charging");
                            strcat(charge_buffer, vin_str);
                        }
                        else if (charge_status == 1)
                        {
                            strcpy(charge_buffer, "bat charging done");
                            strcat(charge_buffer, vin_str);
                        }
                        else if (charge_status == 2)
                        {
                            strcpy(charge_buffer, "bat charging");
                            strcat(charge_buffer, vin_str);
                        }
                        else if (charge_status == 3)
                        {
                            strcpy(charge_buffer, "bat pre charging");
                            strcat(charge_buffer, vin_str);
                        }
                        lv_label_set_text_static(guider_ui.screen_info_label_charge, charge_buffer);
                    }
                    
                    // 更新IMU数据
                    if (lv_obj_is_valid(guider_ui.screen_info_label_accel) && guider_ui.screen_info_label_accel != NULL) 
                    {
                        sprintf(accel_buffer, "Accel: X:%d, Y:%d, Z:%d", accel_x, accel_y, accel_z);
                        lv_label_set_text_static(guider_ui.screen_info_label_accel, accel_buffer);
                    }
                    
                    if (lv_obj_is_valid(guider_ui.screen_info_label_gyro) && guider_ui.screen_info_label_gyro != NULL) 
                    {
                        sprintf(gyro_buffer, "Gyro: X:%d, Y:%d, Z:%d", gyro_x, gyro_y, gyro_z);
                        lv_label_set_text_static(guider_ui.screen_info_label_gyro, gyro_buffer);
                    }
                    update_data = false;
                }

                if (lv_touch_data.status == TOUCH_STATUS_PRESSED)
                {
                    if (lv_obj_is_valid(guider_ui.screen_info_label_touc) && guider_ui.screen_info_label_touc != NULL) 
                    {
                        sprintf(touch_buffer, "Touch: %d, %d", lv_touch_data.x, lv_touch_data.y);
                        lv_label_set_text_static(guider_ui.screen_info_label_touc, touch_buffer);
                    }
                }
                break;
                
            case SCREEN_VIBRA:
                if (update_data)
                {
                    if (lv_obj_is_valid(guider_ui.screen_vibra_label_battery) && guider_ui.screen_vibra_label_battery != NULL) 
                    {
                        sprintf(battery_level_buffer, "%d%% %.1fV", battery_level, voltage);
                        lv_label_set_text_static(guider_ui.screen_vibra_label_battery, battery_level_buffer);
                    }
                    if (lv_obj_is_valid(guider_ui.screen_vibra_bar_battery) && guider_ui.screen_vibra_bar_battery != NULL)
                    {
                        lv_bar_set_value(guider_ui.screen_vibra_bar_battery, battery_level, LV_ANIM_OFF);
                    }
                    update_data = false;
                }
                break;
                
            case SCREEN_VOICE:
                if (update_data)
                {
                    if (lv_obj_is_valid(guider_ui.screen_voice_label_battery) && guider_ui.screen_voice_label_battery != NULL) 
                    {
                        sprintf(battery_level_buffer, "%d%% %.1fV", battery_level, voltage);
                        lv_label_set_text_static(guider_ui.screen_voice_label_battery, battery_level_buffer);
                    }
                    if (lv_obj_is_valid(guider_ui.screen_voice_bar_battery) && guider_ui.screen_voice_bar_battery != NULL)
                    {
                        lv_bar_set_value(guider_ui.screen_voice_bar_battery, battery_level, LV_ANIM_OFF);
                    }
                    update_data = false;
                }
                if (is_recording || is_playing)
                {
                    if (recording_start_time == 0)
                    {
                        recording_start_time = esp_timer_get_time();
                    }
                    if (lv_obj_is_valid(guider_ui.screen_voice_label_record) && guider_ui.screen_voice_label_record != NULL) 
                    {
                        float recording_time = (esp_timer_get_time() - recording_start_time) / 1000000.0f;
                        sprintf(record_time_buffer, "%.1fs", recording_time);
                        lv_label_set_text_static(guider_ui.screen_voice_label_record, record_time_buffer);
                    }
                }
                else
                {
                    recording_start_time = 0;
                }
                break;
            case SCREEN_IMG:
                if (update_data)
                {
                    // 根据BMI270的旋转角度旋转图片
                    if (lv_obj_is_valid(guider_ui.screen_img_img) && guider_ui.screen_img_img != NULL) {
                        // 使用陀螺仪数据计算旋转角度
                        int16_t angle = (int16_t)(atan2(accel_y, accel_x) * 180.0 / M_PI);
                        // 确保角度在0-360度范围内
                        if(angle < 0) {
                            angle += 360;
                        }
                        ESP_LOGI(TAG, "angle = %d", angle);
                        
                        // 获取当前角度
                        int16_t current_angle = lv_img_get_angle(guider_ui.screen_img_img_1) / 10;
                        
                        // 计算最短路径
                        int16_t diff = angle - current_angle;
                        if(diff > 180) {
                            diff -= 360;
                        } else if(diff < -180) {
                            diff += 360;
                        }
                        int16_t target_angle = current_angle + diff;
                        
                        // 设置图片旋转动画
                        lv_anim_t a;
                        lv_anim_init(&a);
                        lv_anim_set_var(&a, guider_ui.screen_img_img_1);
                        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_angle);
                        lv_anim_set_values(&a, current_angle * 10, target_angle * 10);
                        lv_anim_set_time(&a, 500);
                        lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
                        lv_anim_start(&a);
                    }
                    update_data = false;
                }
                break;
            default:
                break;
        }
        example_lvgl_unlock();
    }
}

}
