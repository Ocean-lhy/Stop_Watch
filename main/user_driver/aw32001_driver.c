#include "aw32001_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "system_utils.h"

static const char *TAG = "aw32001_driver";
static i2c_bus_device_handle_t aw32001_dev = NULL;

void aw32001_init(i2c_bus_handle_t i2c_bus)
{
    aw32001_dev = i2c_bus_device_create(i2c_bus, AW32001_ADDR, 400000);
    if (aw32001_dev == NULL)
    {
        ESP_LOGE(TAG, "aw32001_dev create failed");
    }
    else
    {
        ESP_LOGI(TAG, "aw32001_dev create success");
    }

    uint8_t rbuf;
    i2c_bus_read_byte(aw32001_dev, 0x02, &rbuf);
    ESP_LOGI(TAG, "aw32001 charger current: %dma", (rbuf & 0b111111) * 8);
    i2c_bus_read_byte(aw32001_dev, 0x04, &rbuf);
    ESP_LOGI(TAG, "aw32001 charger voltage: %dmv", (rbuf >> 2) * 15 + 3600);
    i2c_bus_write_byte(aw32001_dev, 0x00, 0b00001111);
    i2c_bus_write_byte(aw32001_dev, 0x05, 0b00000110);
}

void aw32001_check_status()
{
    uint8_t in_data;
    i2c_bus_read_byte(aw32001_dev, AW32001_REG_SYS_STA, &in_data);
    // B4-B3 00: NOT CHARGING 01: PRE CHARGING 10: CHARGING 11: CHARGING DONE
    // 判断充电状态, 通过Bit4 Bit3
    if ((in_data & 0b00011000) == 0b00011000)
    {
        ESP_LOGI(TAG, "bat charging done");
    }
    else if ((in_data & 0b00011000) == 0b00010000)
    {
        ESP_LOGI(TAG, "bat charging");
    }
    else if ((in_data & 0b00011000) == 0b00001000)
    {
        ESP_LOGI(TAG, "bat pre charging");
    }
    else
    {
        ESP_LOGI(TAG, "bat not charging");
    }
}

void aw32001_charge_set(bool en)
{
    uint8_t in_data;
    i2c_bus_read_byte(aw32001_dev, AW32001_REG_PWR_CFG, &in_data);
    if (en)
    {
        clrbit(in_data, 3); // 0 enable
    }
    else
    {
        setbit(in_data, 3); // 1 disable
    }
    i2c_bus_write_byte(aw32001_dev, AW32001_REG_PWR_CFG, in_data);
} 