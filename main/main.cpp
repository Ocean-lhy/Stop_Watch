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
#include "esp_timer.h"
#include "i2c_bus.h"
#include "esp_sleep.h"

// 导入模块化的驱动
#include "system_utils.h"
#include "motor_driver.h"
#include "pi4io_driver.h"
#include "aw32001_driver.h"
#include "bq27220_driver.h"
#include "bmi270_driver.h"
#include "es8311_driver.h"
#include "cst9217_driver.h"
#include "lcd_driver.h"
#include "rx8130ce.h"

#include "gui_guider.h"
#include "custom.h"

#define TAG "main"

// extern const uint8_t test_pcm_start[] asm("_binary_test_pcm_start");
// extern const uint8_t test_pcm_end[]   asm("_binary_test_pcm_end");

extern uint8_t play_flag;
    
lv_ui guider_ui;
i2c_bus_handle_t i2c_bus = NULL;
static uint64_t last_blink_time = 0;
static bool led_blink = false;

void sleep_mode(uint8_t sleep_mode);

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

    // 初始化全局中断
    global_irq_init();
    
    // 初始化I2C总线
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = SYS_I2C_SDA;
    conf.scl_io_num = SYS_I2C_SCL;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 400000;
    conf.clk_flags = 0;
    i2c_bus = i2c_bus_create(I2C_NUM_0, &conf);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    uint8_t i2c_addr[128] = {0};
    i2c_bus_scan(i2c_bus, i2c_addr, 0);
    for (int i = 0; i < 128; i++) 
    {
        if (i2c_addr[i] != 0) 
        {
            printf("i2c_addr[%d] = 0x%02x\n", i, i2c_addr[i]);
        }
    }
    
    // RX8130
    ESP_LOGI(TAG, "RX8130 init");
    rx8130_init(i2c_bus);

    // 初始化各个驱动
    ESP_LOGI(TAG, "motor_init");
    motor_init();
    ESP_LOGI(TAG, "pi4io_init");
    pi4io_init(i2c_bus);
    pi4io_5V_out_disable();
    
    // 充电管理
    ESP_LOGI(TAG, "aw32001_init");
    aw32001_init(i2c_bus);
    aw32001_charge_set(true);

    // 电量计
    ESP_LOGI(TAG, "bq27220_init");
    bq27220_init(i2c_bus);
    bq27220_exit_sealed();
    bq27220_full_access();
    bq27220_enter_cfg_update();

    // IMU
    ESP_LOGI(TAG, "bmi270_dev_init");
    bmi270_dev_init(i2c_bus);

    // ES8311 音频
    ESP_LOGI(TAG, "es8311_driver_init");
    es8311_driver_init(i2c_bus);

    // 触摸
    ESP_LOGI(TAG, "cst9217_init");
    cst9217_init(i2c_bus);

    // LCD
    ESP_LOGI(TAG, "lcd_init");
    lcd_init();

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

    // sleep_mode(2);

    // 设置G3-G8 G11为输出
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;    // 禁用中断
    io_conf.mode = GPIO_MODE_OUTPUT;           // 设置为输出模式
    io_conf.pin_bit_mask = ((1ULL<<3) | (1ULL<<4) | (1ULL<<5) | (1ULL<<6) | (1ULL<<7) | (1ULL<<8) | (1ULL<<11)); // G3-G7
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    // 设置输出
    gpio_set_level(GPIO_NUM_3, 0);
    gpio_set_level(GPIO_NUM_4, 0); 
    gpio_set_level(GPIO_NUM_5, 0);
    gpio_set_level(GPIO_NUM_6, 0);
    gpio_set_level(GPIO_NUM_7, 0);
    gpio_set_level(GPIO_NUM_8, 0);
    gpio_set_level(GPIO_NUM_11, 0);
    
    uint8_t brightness = 0xFF;
    ESP_LOGI(TAG, "Start main loop");
    while (1)
    {
        // 定期更新状态
        if (esp_timer_get_time() - last_blink_time > 3000000)
        {
            last_blink_time = esp_timer_get_time();
            led_blink = !led_blink;
            
            // 更新状态信息
            aw32001_check_status();
            bmi270_dev_update();
            bq27220_read_voltage();
            bq27220_read_current();
            uint8_t vin_det = pi4io_vin_detect();
            printf("vin_det = %d\n", vin_det);
            printf("\r\n");

            vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        // 按键处理
        if (btn1)
        {
            printf("btn1 pressed\n");
            play_flag = (play_flag!=0)?0:1;
            printf("test enable = %d\n", play_flag);
            btn1 = 0;
            brightness += 10;
            lcd_set_brightness(brightness);
            lcd_set_sleep(play_flag);
            // power_off();
        } 
        if (btn2)
        {
            printf("btn2 pressed\n");
            
            size_t bytes_written = 0;
            printf("start play\n");
            // i2s_write(I2S_NUM_0, test_pcm_start, test_pcm_end - test_pcm_start, &bytes_written, portMAX_DELAY);
            // i2s_zero_dma_buffer(I2S_NUM_0);
            printf("end play\n");
            btn2 = 0;

            brightness -= 10;
            lcd_set_brightness(brightness);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void sleep_mode(uint8_t sleep_mode) // 0: wake up, 1: light sleep, 2: deep sleep
{
    pi4io_sleep(sleep_mode);
    if (sleep_mode == 0)
    {
        lcd_set_sleep(false);
        cst9217_set_workmode(LP_MODE, 1);
    }
    else 
    if (sleep_mode == 1)
    {
        bq27220_enter_sleep_mode();
        bmi270_dev_sleep();
        lcd_set_sleep(true);
        cst9217_set_workmode(NOMAL_MODE, 1);
        esp_light_sleep_start();
    }
    else 
    if (sleep_mode == 2)
    {
        bq27220_enter_sleep_mode();
        bmi270_dev_sleep();
        esp_deep_sleep_start();
    }
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

}
