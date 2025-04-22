#include "bq27220_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "system_utils.h"

static const char *TAG = "bq27220_driver";
static i2c_bus_device_handle_t bq27220_dev = NULL;

esp_err_t bq27220_i2c_read(uint8_t reg_addr, uint16_t sub_reg, uint16_t *reg_data)
{
    uint8_t rbuf[2] = {0};
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (BQ27220_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write_byte(cmd, (sub_reg >> 8) & 0xFF, true);
    i2c_master_write_byte(cmd, sub_reg & 0xFF, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (BQ27220_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, &rbuf[0], I2C_MASTER_ACK);
    i2c_master_read_byte(cmd, &rbuf[1], I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    ESP_LOGI(TAG, "bq27220_i2c_read rbuf: %02X %02X", rbuf[0], rbuf[1]);
    *reg_data = (rbuf[1] << 8) | rbuf[0];
    return ret;
}

void bq27220_init(i2c_bus_handle_t i2c_bus)
{
    bq27220_dev = i2c_bus_device_create(i2c_bus, BQ27220_ADDR, 400000);
    if (bq27220_dev == NULL)
    {
        ESP_LOGE(TAG, "bq27220_dev create failed");
    }
    else
    {
        ESP_LOGI(TAG, "bq27220_dev create success");
    }
}

void bq27220_exit_sealed()
{
    // SEALED => UNSEAL
    i2c_bus_write_byte(bq27220_dev, 0x00, 0x80);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x00, 0x80);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

void bq27220_enter_seal()
{
    // UNSEAL => SEALED
    i2c_bus_write_byte(bq27220_dev, 0x00, 0x30);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

void bq27220_enter_sleep_mode()
{
    uint16_t data;
    i2c_bus_read_reg16(bq27220_dev, 0x9206, 2, (uint8_t *)&data);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "BQ27 0x9206: %x", data);
    i2c_bus_read_reg16(bq27220_dev, 0x9207, 2, (uint8_t *)&data);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "BQ27 0x9207: %x", data);
}

void bq27220_full_access()
{
    ESP_LOGI(TAG, "bq27220_full_access");
    i2c_bus_write_byte(bq27220_dev, 0x00, 0xFF);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x01, 0xFF);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x00, 0xFF);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x01, 0xFF);
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

bool bq27220_opration_status_check()
{
    uint16_t data;
    i2c_bus_read_bytes(bq27220_dev, 0x3A, 2, (uint8_t *)&data);
    if ((data & 0b010) == 0b010)
    {
        ESP_LOGI(TAG, "Opration Status [full access]: 0x%04X", data);
        return true;
    }
    ESP_LOGI(TAG, "Opration Status: 0x%04X", data);
    return false;
}

void bq27220_enter_cfg_update()
{
    ESP_LOGI(TAG, "bq27220_enter_cfg_update");
    i2c_bus_write_byte(bq27220_dev, 0x00, 0x90);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
    vTaskDelay(10 / portTICK_PERIOD_MS);

    uint16_t data;
    while (1)
    {
        i2c_bus_read_bytes(bq27220_dev, 0x3A, 2, (uint8_t *)&data);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        if (getbit(data, 10))
        {
            ESP_LOGI(TAG, "Opration Status [CFGUPDATE mode]: 0x%04X", data);
            break;
        }
        else
        {
            ESP_LOGI(TAG, "Opration Status: 0x%04X", data);
        }
    }
}

void bq27220_opration_config_A()
{
    uint16_t wdata = 0x9206;
    uint16_t rdata;
    i2c_bus_write_reg16(bq27220_dev, 0x3E, 2, (uint8_t *)&wdata);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_read_bytes(bq27220_dev, 0x60, 1, (uint8_t *)&rdata);
    ESP_LOGI(TAG, "Opration Config A check sum: 0x%02x", rdata);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_read_bytes(bq27220_dev, 0x61, 1, (uint8_t *)&rdata);
    ESP_LOGI(TAG, "Opration Config A data len sum: 0x%02x", rdata);
    i2c_bus_read_bytes(bq27220_dev, 0x40, 2, (uint8_t *)&rdata);
    ESP_LOGI(TAG, "Opration Config A: 0x%04X", rdata);
}

void bq27220_opration_config_B()
{
    uint8_t data[4];
    i2c_bus_write_byte(bq27220_dev, 0x3E, 0x08);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x3F, 0x92);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_read_bytes(bq27220_dev, 0x60, 1, data);
    ESP_LOGI(TAG, "Opration Config B check sum: 0x%02x", data[0]);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_read_bytes(bq27220_dev, 0x61, 1, data);
    ESP_LOGI(TAG, "Opration Config B data len sum: 0x%02x", data[0]);
    i2c_bus_read_bytes(bq27220_dev, 0x40, 2, data);
    ESP_LOGI(TAG, "Opration Config B: 0x%02x 0x%02x", data[0], data[1]);
}

void bq27220_read_design_capacity()
{
    uint16_t data;
    i2c_bus_read_bytes(bq27220_dev, 0x3C, 2, (uint8_t *)&data);
    ESP_LOGI(TAG, "design capacity: %dmV", data);
}

uint16_t bq27220_read_voltage()
{
    uint16_t voltage;
    i2c_bus_read_bytes(bq27220_dev, 0x08, 2, (uint8_t *)&voltage);
    ESP_LOGI(TAG, "voltage: %dmv", voltage);
    return voltage;
}

uint16_t bq27220_read_current()
{
    uint16_t current;
    i2c_bus_read_bytes(bq27220_dev, 0x14, 2, (uint8_t *)&current);
    ESP_LOGI(TAG, "current: %dma", current);
    return current;
}

void bq27220_read_dev_number()
{
    uint8_t data[4];
    i2c_bus_write_byte(bq27220_dev, 0x00, 0x01);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    i2c_bus_read_bytes(bq27220_dev, 0x3E, 4, data);
    ESP_LOGI(TAG, "Device Number: 0x%02x 0x%02x 0x%02x 0x%02x", data[0], data[1], data[2], data[3]);
} 