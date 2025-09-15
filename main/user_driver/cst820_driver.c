#include "cst820_driver.h"
#include <stdint.h>
#include <string.h>
#include "i2c_bus.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define MAX_POINTS_REPORT 5

static const char *TAG = "cst820_driver";
static i2c_bus_device_handle_t cst820_dev = NULL;
static uint8_t chip_id; // 芯片ID
static uint8_t soft_ver; // 软件版本
extern SemaphoreHandle_t touch_mux;
static uint8_t i2c_buf[10] = {0};
static uint8_t finger_num = 0;
uint16_t cst820_x = 0;
uint16_t cst820_y = 0;
uint8_t cst820_status = 0;

/**
 * @brief 复位触摸屏
 */
esp_err_t cst820_tp_reset(void)
{
    ESP_LOGI(TAG, "复位触摸屏");

    // 拉低复位引脚
    gpio_set_level(TOUCH_RST_PIN, 0);

    vTaskDelay(pdMS_TO_TICKS(10));  // 延时10ms

    // 拉高复位引脚
    gpio_set_level(TOUCH_RST_PIN, 1);

    vTaskDelay(pdMS_TO_TICKS(50));  // 延时50ms等待复位完成

    return ESP_OK;
}

int cst820_init(i2c_bus_handle_t i2c_bus)
{
    cst820_tp_reset();
    if (touch_mux == NULL)
    {
        touch_mux = xSemaphoreCreateBinary();
        assert(touch_mux);
    }
    cst820_dev = i2c_bus_device_create(i2c_bus, CST820_ADDR, 100000);
    if (cst820_dev == NULL)
    {
        ESP_LOGE(TAG, "cst820_dev create failed");
        return -1;
    }
    else
    {
        ESP_LOGI(TAG, "cst820_dev create success");
    }

    if (cst820_read_tpinfo() == -1)
    {
        ESP_LOGE(TAG, "cst820_read_tpinfo failed");
        return -1;
    }
    return 0;
}

int cst820_read_tpinfo()
{
    i2c_bus_read_bytes(cst820_dev, CST820_CHIP_ID, 1, &chip_id);
    i2c_bus_read_bytes(cst820_dev, CST820_SOFT_VER, 1, &soft_ver);
    ESP_LOGI(TAG, "chip_id: %d, soft_ver: %d", chip_id, soft_ver);
    if (chip_id != 0 && soft_ver != 0)
    {
        ESP_LOGI(TAG, "cst820_read_tpinfo success");
        return 0;
    }
    else
    {
        ESP_LOGI(TAG, "cst820_read_tpinfo failed");
        return -1;
    }
}

int cst820_update()
{
    i2c_bus_read_bytes(cst820_dev, CST820_REG_STATUS, 7, i2c_buf);

    finger_num = i2c_buf[2];
    cst820_x = ((uint16_t)(i2c_buf[3] & 0x0F) << 8) | i2c_buf[4];
    cst820_y = ((uint16_t)(i2c_buf[5] & 0x0F) << 8) | i2c_buf[6];
    cst820_status = (i2c_buf[3] & 0xC0) >> 6; // 0按下 1抬起 2保持或移动
    // ESP_LOGI(TAG, "cst820_update: %d, %d, %2X", cst820_x, cst820_y, cst820_status);
    return 0;
}

void cst820_sleep()
{
    uint8_t i2c_buf[1] = {0x03};
    i2c_bus_write_bytes(cst820_dev, 0xE5, 1, i2c_buf); // 进入休眠
}
