#include "cst9217_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "system_utils.h"

static const char *TAG = "cst9217_driver";
static i2c_bus_device_handle_t cst9217_dev = NULL;
static uint32_t partno_chip_type; // 芯片类型
static uint32_t module_id; // 模块ID
static uint8_t work_mode; // 工作模式
tp_info_t tp_info[MAX_POINTS_REPORT];
SemaphoreHandle_t touch_mux = NULL;

void cst9217_init(i2c_bus_handle_t i2c_bus)
{
    cst9217_dev = i2c_bus_device_create(i2c_bus, CST9217_ADDR, 400000);
    if (cst9217_dev == NULL)
    {
        ESP_LOGE(TAG, "cst9217_dev create failed");
    }
    else
    {
        ESP_LOGI(TAG, "cst9217_dev create success");
    }
    // cst9217_read_chip_id();

    cst9217_read_tpinfo();
    touch_mux = xSemaphoreCreateBinary();
    assert(touch_mux);
}

int cst9217_update()
{
    uint8_t i2c_buf[MAX_POINTS_REPORT*5+5] = {0};
    uint8_t finger_num = 0;

    // 读取触摸数据
    if (i2c_bus_read_reg(cst9217_dev, 0xD000, 2, i2c_buf, sizeof(i2c_buf)) != ESP_OK) {
        // ESP_LOGW(TAG, "Failed to read touch data");
        return 0;
    }

    // 验证数据有效性
    if (i2c_buf[6] != 0xAB) {
        // ESP_LOGW(TAG, "Invalid touch data header");
        return 0;
    }

    finger_num = i2c_buf[5] & 0x7F;
    if (finger_num > MAX_POINTS_REPORT) {
        // ESP_LOGW(TAG, "Exceed max finger count: %d", finger_num);
        return 0;
    }

    // ESP_LOGI(TAG, "Detected fingers: %d", finger_num);

    // 清空之前的触摸数据
    memset(tp_info, 0, sizeof(tp_info));

    // 解析每个触摸点
    for (int i = 0; i < finger_num; i++) {
        uint8_t *data = (i == 0) ? i2c_buf : i2c_buf + 5*i + 2;
        
        if (data >= i2c_buf + sizeof(i2c_buf)) {
            ESP_LOGE(TAG, "Data overflow detected");
            break;
        }

        tp_info[i].id = data[0] >> 4;
        tp_info[i].switch_ = data[0] & 0x0F;
        tp_info[i].x = ((uint16_t)(data[1]) << 4) | (data[3] >> 4);
        tp_info[i].y = ((uint16_t)(data[2]) << 4) | (data[3] & 0x0F);
        tp_info[i].z = (data[3] & 0x1F) + 0x03;

        // ESP_LOGI(TAG, "Finger %d: ID=%d X=%d Y=%d Z=%d switch=%d", 
        //          i+1, tp_info[i].id, tp_info[i].x, tp_info[i].y, tp_info[i].z, tp_info[i].switch_);
    }

    return finger_num;
}

void cst9217_enter_bootloader()
{
    uint8_t i2c_buf[4] = {0};
    for (int i = 10;; i+=2)
    {
        if (i >= 30)
        {
            ESP_LOGE(TAG, "cst9217_enter_bootloader timeout");
            return;
        }
        // pi4io_tp_reset();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        i2c_buf[0] = 0xAA;
        i2c_bus_write_reg(cst9217_dev, 0xA001, 2, i2c_buf, 1);
        vTaskDelay(5 / portTICK_PERIOD_MS);
        i2c_bus_read_reg(cst9217_dev, 0xA002, 2, i2c_buf, 2);
        vTaskDelay(5 / portTICK_PERIOD_MS);
        if(i2c_buf[0] == 0x55 && i2c_buf[1] == 0xB0)
        {
            ESP_LOGI(TAG, "cst9217_enter_bootloader success");
            break;
        }
    }
    i2c_buf[0] = 0x00;
    i2c_bus_write_reg(cst9217_dev, 0xA001, 2, i2c_buf, 1);
}

void cst9217_read_chip_id()
{
    cst9217_enter_bootloader();
    for (int i = 0; i < 3; i++)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
        cst9217_read_word_from_mem(1, 0x077C, &partno_chip_type);
        cst9217_read_word_from_mem(0, 0x7FC0, &module_id);
        if ((partno_chip_type >> 16) == 0xCACA)
        {
            ESP_LOGI(TAG, "cst9217 read success");
            partno_chip_type &= 0xffff;
            break;
        }
        else
        {
            ESP_LOGW(TAG, "cst9217 read failed, retry");
        }
    }
    // pi4io_tp_reset();
    ESP_LOGI(TAG, "partno_chip_type: 0x%lx", partno_chip_type);
    ESP_LOGI(TAG, "module_id: 0x%lx", module_id);
    if ((partno_chip_type != 0x9217) && (partno_chip_type != 0x9220))
    {
        ESP_LOGE(TAG, "partno_chip_type error 0x%lx", partno_chip_type);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
}

void cst9217_read_tpinfo()
{
    uint8_t i2c_buf[30] = {0};

    // cst9217_set_workmode(0xff, 0);
    i2c_bus_write_reg(cst9217_dev, 0xD101, 2, i2c_buf, 0);
    vTaskDelay(5 / portTICK_PERIOD_MS);

    i2c_bus_read_reg(cst9217_dev, 0xD1F4, 2, i2c_buf, 28);
    ESP_LOGI(TAG, "firmware_project_id: 0x%04x", i2c_buf[17] << 8 | i2c_buf[16]);
    ESP_LOGI(TAG, "firmware_ic_type: 0x%04x", i2c_buf[19] << 8 | i2c_buf[18]);
    ESP_LOGI(TAG, "firmware_version: 0x%04x", i2c_buf[23] << 24 | i2c_buf[22] << 16 | i2c_buf[21] << 8 | i2c_buf[20]);
    ESP_LOGI(TAG, "tx_num: %d", i2c_buf[1]);
    ESP_LOGI(TAG, "rx_num: %d", i2c_buf[2]);
    ESP_LOGI(TAG, "key_num: %d", i2c_buf[3]);
    ESP_LOGI(TAG, "res_x: %d", i2c_buf[5] << 8 | i2c_buf[4]);
    ESP_LOGI(TAG, "res_y: %d", i2c_buf[7] << 8 | i2c_buf[6]);
    ESP_LOGI(TAG, "fw_checksum: 0x%04x", i2c_buf[27] << 8 | i2c_buf[26]);
    
    cst9217_set_workmode(NOMAL_MODE, 1);
}

void cst9217_set_workmode(enum work_mode mode, uint8_t enable)
{
    uint8_t i2c_buf[4] = {0};
    work_mode = mode;
    if(mode != NOMAL_MODE)
    {
        ESP_LOGI(TAG, "cst9217_set_workmode: %d", mode);
    }
    for(int i = 0; i < 3; i++)
    {
        i2c_bus_write_reg(cst9217_dev, 0xD11E, 2, i2c_buf, 0);
        vTaskDelay(5 / portTICK_PERIOD_MS);
        i2c_bus_write_reg(cst9217_dev, 0x0002, 2, i2c_buf, 2);
        if(i2c_buf[1] == 0x1E)
        {
            break;
        }
    }
    switch(mode)
    {
        case NOMAL_MODE:
            i2c_bus_write_reg(cst9217_dev, 0xD109, 2, i2c_buf, 0);
            break;
        case GESTURE_MODE:
            i2c_bus_write_reg(cst9217_dev, 0xD104, 2, i2c_buf, 0);
            break;
        case LP_MODE:
            i2c_bus_write_reg(cst9217_dev, 0xD107, 2, i2c_buf, 0);
            break;
        case DIFF_MODE:
            i2c_bus_write_reg(cst9217_dev, 0xD10D, 2, i2c_buf, 0);
            break;
        case RAWDATA_MODE:
            i2c_bus_write_reg(cst9217_dev, 0xD10A, 2, i2c_buf, 0);
            break;
        case BASELINE_MODE:
            i2c_bus_write_reg(cst9217_dev, 0xD108, 2, i2c_buf, 0);
            break;
        case CALIBRATE_MODE:
            i2c_bus_write_reg(cst9217_dev, 0xD10B, 2, i2c_buf, 0);
            break;
        case FAC_TEST_MODE:
            i2c_bus_write_reg(cst9217_dev, 0xD114, 2, i2c_buf, 0);
            break;
        case DEEPSLEEP:
            i2c_bus_write_reg(cst9217_dev, 0xD105, 2, i2c_buf, 0);
            break;
        default:
            ESP_LOGW(TAG, "cst9217_set_workmode: %d", mode);
            mode = NOMAL_MODE;
            break;
    }
}

void cst9217_read_word_from_mem(uint8_t type, uint16_t addr, uint32_t *value)
{
    uint8_t i2c_buf[4] = {0};
    i2c_buf[0] = type;
    i2c_bus_write_reg(cst9217_dev, 0xA010, 2, i2c_buf, 1);

    i2c_buf[0] = addr;
    i2c_buf[1] = addr >> 8;
    i2c_bus_write_reg(cst9217_dev, 0xA00C, 2, i2c_buf, 2);

    i2c_buf[0] = 0xE4;
    i2c_bus_write_reg(cst9217_dev, 0xA004, 2, i2c_buf, 1);

    for(int i = 0;; i++)
    {
        if (i >= 100)
        {
            ESP_LOGE(TAG, "cst9217_read_word_from_mem timeout");
            return;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_read_reg(cst9217_dev, 0xA004, 2, i2c_buf, 1);
        if (i2c_buf[0] == 0x00)
        {
            break;
        }
    }
    i2c_bus_read_reg(cst9217_dev, 0xA018, 2, i2c_buf, 4);
    *value = (i2c_buf[0] << 24) | (i2c_buf[1] << 16) | (i2c_buf[2] << 8) | i2c_buf[3];
}

void cst9217_read_data(uint8_t *data, uint16_t len)
{
    // 空实现，根据需要补充
} 