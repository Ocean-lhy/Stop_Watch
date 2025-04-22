#include "pi4io_driver.h"
#include "system_utils.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "pi4io_driver";
static i2c_bus_device_handle_t pi4io_dev = NULL;

void pi4io_init(i2c_bus_handle_t i2c_bus)
{
    pi4io_dev = i2c_bus_device_create(i2c_bus, PI4IO_ADDR, 400000);
    if (pi4io_dev == NULL)
    {
        ESP_LOGE(TAG, "pi4io_dev create failed");
    }
    else
    {
        ESP_LOGI(TAG, "pi4io_dev create success");
    }

    uint8_t in_data;
    // P0 TP_RST
    // P1 OLED_RST
    // P5 VIN_DET
    // P6 VOUT_EN
    // P7 SPK_EN
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_CHIP_RESET, 0xFF);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_read_byte(pi4io_dev, PI4IO_REG_CHIP_RESET, &in_data);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_IO_DIR, 0b11000011); // 0: input 1: output
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_H_IM, 0b00111000); // 使用到的引脚关闭High-Impedance
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_PULL_SEL, 0b11000111); // pull up/down select, 0 down, 1 up
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_PULL_EN, 0b11000111); // pull up/down enable, 0 disable, 1 enable
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_IN_DEF_STA, 0b00000000); // P0 P1 默认高电平, 按键按下触发中断
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_INT_MASK, 0b11111111); // P0 P1 中断使能 0 enable, 1 disable
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, 0b11000011); // 默认输出为0
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

void pi4io_release_all()
{
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_H_IM, 0xFF);
}

void pi4io_lcd_reset()
{
    uint8_t in_data;
    i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
    clrbit(in_data, 1); // LOW
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    setbit(in_data, 1); // HIGH
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
    vTaskDelay(100 / portTICK_PERIOD_MS);
}

void pi4io_tp_reset()
{
    uint8_t in_data;
    i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
    clrbit(in_data, 0);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    setbit(in_data, 0);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
    vTaskDelay(100 / portTICK_PERIOD_MS);
}

void pi4io_speaker_enable()
{
    uint8_t in_data;
    i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
    setbit(in_data, 7);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
}

void pi4io_speaker_disable()
{
    uint8_t in_data;
    i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
    clrbit(in_data, 7);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
}

uint8_t pi4io_vin_detect()
{
    uint8_t in_data;
    i2c_bus_read_byte(pi4io_dev, PI4IO_REG_IN_STA, &in_data);
    return getbit(in_data, 5);
}

void pi4io_5V_out_enable()
{
    uint8_t in_data;
    i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
    setbit(in_data, 6);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
}

void pi4io_5V_out_disable()
{
    uint8_t in_data;
    i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
    clrbit(in_data, 6);
    i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
} 