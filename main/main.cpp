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
#include "m5_ic_aw32001.h"

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

m5_ic_aw32001 ic_aw32001(I2C_NUM_0, SYS_I2C_SDA, SYS_I2C_SCL, 400000); // I2C bus 0, SDA pin 21, SCL pin 22, 400kHz

void sleep_mode(uint8_t sleep_mode);

void app_main(void)
{
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
    // rx8130_init(i2c_bus);

    // 初始化各个驱动
    ESP_LOGI(TAG, "motor_init");
    // motor_init();
    ESP_LOGI(TAG, "pi4io_init");
    pi4io_init(i2c_bus);
    
    // 充电管理
    ESP_LOGI(TAG, "aw32001_init");
    ic_aw32001.init(AW32001_ADDR);
    uint8_t reg_data_aw32001 = 0x00;
    ic_aw32001.read_register(0x01, &reg_data_aw32001);
    setbit(reg_data_aw32001, 3);
    ic_aw32001.write_register(0x01, reg_data_aw32001);
    ic_aw32001.read_register(0x01, &reg_data_aw32001);
    ESP_LOGI(TAG, "AW32001 CEB: %d", getbit(reg_data_aw32001, 3));
    ic_aw32001.read_register(0x07, &reg_data_aw32001);
    setbit(reg_data_aw32001, 7);
    ic_aw32001.write_register(0x07, reg_data_aw32001);
    ic_aw32001.read_register(0x07, &reg_data_aw32001);
    ESP_LOGI(TAG, "AW32001 DIS_PCB_OTP: %d", getbit(reg_data_aw32001, 7));

    // 电量计
    ESP_LOGI(TAG, "bq27220_init");
    // bq27220_init(i2c_bus);
    // bq27220_exit_sealed();
    // bq27220_full_access();
    // bq27220_enter_cfg_update();

    // IMU
    ESP_LOGI(TAG, "bmi270_dev_init");
    // bmi270_dev_init(i2c_bus);
    i2c_bus_device_handle_t i2c_dev_handle_bmi270 = i2c_bus_device_create(i2c_bus, 0x68, 400000);
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
    i2c_bus_device_handle_t cst820_dev = i2c_bus_device_create(i2c_bus, 0x15, 400000);
    if (cst820_dev == NULL)
    {
        ESP_LOGE(TAG, "cst820_dev create failed");
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
    uint8_t i2c_buf[1] = {0x03};
    i2c_bus_write_reg(cst820_dev, 0xE5, 1, i2c_buf, 1); // 进入休眠

    spi_bus_free(LCD_HOST);
    i2c_bus_delete(&i2c_bus);

    gpio_reset_pin((gpio_num_t)SYS_I2C_SDA);
    gpio_reset_pin((gpio_num_t)SYS_I2C_SCL);
    gpio_set_pull_mode((gpio_num_t)SYS_I2C_SDA, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode((gpio_num_t)SYS_I2C_SCL, GPIO_PULLDOWN_ONLY);
    gpio_set_level((gpio_num_t)SYS_I2C_SDA, 0);
    gpio_set_level((gpio_num_t)SYS_I2C_SCL, 0);

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
        // bq27220_enter_sleep_mode();
        // bmi270_dev_sleep();
        // lcd_set_sleep(true);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_deep_sleep_hold_en();
        esp_deep_sleep_start();
    }
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

}
