/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include "m5_ic_aw32001.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

const char *TAG = "main";

#define AW32001_ADDR 0x49   //电池充放电IC

m5_ic_aw32001 ic_aw32001(I2C_NUM_0, GPIO_NUM_2, GPIO_NUM_1, 400000); // I2C bus 0, SDA pin 21, SCL pin 22, 400kHz

extern "C" void app_main(void)
{
    //xiaozhi 需要先打开 audio_en 引脚 （v0.2硬件版本需要，后续硬件版本不用）

    gpio_reset_pin(GPIO_NUM_8);
    gpio_set_direction(GPIO_NUM_8, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_8, 1); // Set GPIO8 to high
    vTaskDelay(200 / portTICK_PERIOD_MS); // Wait for 1 second

    ESP_LOGI(TAG, "Hello, M5Stack!");
    ESP_LOGI(TAG, "This is a test app for M5Stack Chip AW32001.");
    
    // 如果想查看寄存器变化 请先开启全局DEBUG级别日志 然后 设置 ic_aw32001.set_debug_level(ESP_LOG_DEBUG);
    //LOG_DEFAULT_LEVEL -> ESP_LOG_DEBUG; // menuconfig 设置默认日志级别为DEBUG
    ic_aw32001.set_debug_level(ESP_LOG_DEBUG);  // 设置AW日志级别为DEBUG

    // 如果只希望查看ERROR级别的日志
    // ic_aw32001.set_debug_level(ESP_LOG_ERROR);  // 设置AW日志级别为ERROR

    // 初始化时会将看门狗超时设置为0（等同于禁用全局看门狗），若有需要自行开启
    ic_aw32001.init(AW32001_ADDR);

    // 芯片复位后 默认输入电压阈值为4520mV 输入电流阈值为500mA 一般可以不设置
    // ic_aw32001.set_vin_dpm_value(4520); // 设置输入电压阈值为4520mV
    // ic_aw32001.set_iin_lim_value(500); // 设置输入电流阈值为500mA

    ic_aw32001.set_charge_current_value(512); // 设置充电电流为512mA

    ic_aw32001.set_charge_voltage_value(4250); // 设置充电电压为4250mV

    ic_aw32001.set_system_voltage_value(4950); // 设置系统电压为4950mV

    // 启用充电模式 -> 禁用高阻态，打开充电使能
    ic_aw32001.enter_charge_mode(true);

    while(1) 
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait for 1 second
        ic_aw32001.get_charge_status(); // 获取充电状态
    }
}