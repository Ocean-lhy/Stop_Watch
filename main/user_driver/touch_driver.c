#include "touch_driver.h"
#include "cst820_driver.h"
#include "cst9217_driver.h"
#include "esp_log.h"
#include <string.h>
#include "pi4io_driver.h"

static const char *TAG = "touch_driver";
static touch_data_t touch_data = {0};
static bool touch_initialized = false;

/**
 * @brief 自动检测触摸芯片类型
 * @param i2c_bus I2C总线句柄
 * @return 检测到的芯片类型
 */
static touch_chip_type_t detect_touch_chip(i2c_bus_handle_t i2c_bus)
{
    ESP_LOGI(TAG, "检测触摸芯片类型...");
    
    // 先尝试初始化CST9217
    if (cst9217_init(i2c_bus) == 0) {
        ESP_LOGI(TAG, "检测到CST9217芯片");
        return TOUCH_CHIP_CST9217;
    }
    
    // 如果CST9217初始化失败，尝试CST820
    if (cst820_init(i2c_bus) == 0) {
        ESP_LOGI(TAG, "检测到CST820芯片");
        return TOUCH_CHIP_CST820;
    }
    
    ESP_LOGE(TAG, "未检测到支持的触摸芯片");
    return TOUCH_CHIP_NONE;
}

/**
 * @brief 转换CST820状态到统一状态
 * @param cst820_status CST820状态值
 * @return 统一的触摸状态
 */
static touch_status_t convert_cst820_status(uint8_t cst820_status)
{
    switch (cst820_status) {
        case 0: return TOUCH_STATUS_PRESSED;   // 按下
        case 1: return TOUCH_STATUS_RELEASED;  // 抬起
        case 2: return TOUCH_STATUS_CONTACT;   // 保持或移动
        default: return TOUCH_STATUS_RELEASED;
    }
}

/**
 * @brief 转换CST9217状态到统一状态
 * @param switch_value CST9217的switch值
 * @return 统一的触摸状态
 */
static touch_status_t convert_cst9217_status(uint8_t switch_value)
{
    switch (switch_value) {
        case 0x06: return TOUCH_STATUS_PRESSED;  // 按下
        case 0x04: return TOUCH_STATUS_RELEASED; // 抬起
        case 0x05: return TOUCH_STATUS_CONTACT;  // 移动
        default: return TOUCH_STATUS_RELEASED;
    }
}

int touch_driver_init(i2c_bus_handle_t i2c_bus)
{
    ESP_LOGI(TAG, "初始化统一触摸屏驱动");
    
    // 清空触摸数据
    memset(&touch_data, 0, sizeof(touch_data));
    
    // 自动检测芯片类型并初始化
    touch_data.chip_type = detect_touch_chip(i2c_bus);
    
    if (touch_data.chip_type == TOUCH_CHIP_NONE) {
        ESP_LOGE(TAG, "触摸屏初始化失败：未检测到支持的芯片");
        return -1;
    }
    
    touch_initialized = true;
    ESP_LOGI(TAG, "触摸屏初始化成功，芯片类型：%d", touch_data.chip_type);
    return 0;
}

int touch_driver_update(void)
{
    if (!touch_initialized) {
        return -1;
    }
    
    // 清空之前的数据
    memset(touch_data.points, 0, sizeof(touch_data.points));
    touch_data.point_count = 0;
    touch_data.data_ready = false;
    
    int result = 0;
    
    switch (touch_data.chip_type) {
        case TOUCH_CHIP_CST820: {
            result = cst820_update();
            if (result == 0) {
                // CST820只支持单点触摸
                touch_data.point_count = 1;
                touch_data.points[0].id = 0;
                touch_data.points[0].x = cst820_x;
                touch_data.points[0].y = cst820_y;
                touch_data.points[0].pressure = 100; // CST820没有压力值，给个固定值
                touch_data.points[0].status = convert_cst820_status(cst820_status);
                touch_data.points[0].valid = true;
                touch_data.data_ready = true;
            }
            break;
        }
        
        case TOUCH_CHIP_CST9217: {
            int finger_count = cst9217_update();
            if (finger_count > 0 && finger_count <= TOUCH_MAX_POINTS) {
                touch_data.point_count = finger_count;
                for (int i = 0; i < finger_count; i++) {
                    touch_data.points[i].id = tp_info[i].id;
                    touch_data.points[i].x = tp_info[i].x;
                    touch_data.points[i].y = tp_info[i].y;
                    touch_data.points[i].pressure = tp_info[i].z;
                    touch_data.points[i].status = convert_cst9217_status(tp_info[i].switch_);
                    touch_data.points[i].valid = true;
                }
                touch_data.data_ready = true;
                result = 0;
            } else if (finger_count == 0) {
                // 没有触摸点
                result = 0;
            } else {
                result = -1;
            }
            break;
        }
        
        default:
            ESP_LOGE(TAG, "不支持的芯片类型：%d", touch_data.chip_type);
            result = -1;
            break;
    }
    
    return result;
}

int touch_driver_get_data(touch_data_t *data)
{
    if (!touch_initialized || data == NULL) {
        return -1;
    }
    
    // 复制触摸数据
    memcpy(data, &touch_data, sizeof(touch_data_t));
    return 0;
}

bool touch_driver_get_point(uint16_t *x, uint16_t *y, touch_status_t *status)
{
    if (!touch_initialized || !touch_data.data_ready || touch_data.point_count == 0) {
        return false;
    }
    
    // 返回第一个有效触摸点
    for (int i = 0; i < touch_data.point_count; i++) {
        if (touch_data.points[i].valid) {
            if (x) *x = touch_data.points[i].x;
            if (y) *y = touch_data.points[i].y;
            if (status) *status = touch_data.points[i].status;
            return true;
        }
    }
    
    return false;
}

void touch_driver_sleep(void)
{
    if (!touch_initialized) {
        ESP_LOGW(TAG, "触摸屏未初始化，无法休眠");
        return;
    }
    
    ESP_LOGI(TAG, "设置触摸屏进入休眠模式");
    
    switch (touch_data.chip_type) {
        case TOUCH_CHIP_CST820:
            cst820_sleep();
            break;
            
        case TOUCH_CHIP_CST9217:
            cst9217_set_workmode(DEEPSLEEP, 1);
            break;
            
        default:
            ESP_LOGW(TAG, "不支持的芯片类型，无法休眠");
            break;
    }
}

void touch_driver_wakeup(void)
{
    if (!touch_initialized) {
        ESP_LOGW(TAG, "触摸屏未初始化，无法唤醒");
        return;
    }
    
    ESP_LOGI(TAG, "唤醒触摸屏");
    
    switch (touch_data.chip_type) {
        case TOUCH_CHIP_CST820:
            pi4io_tp_reset();
            break;
            
        case TOUCH_CHIP_CST9217:
            cst9217_set_workmode(NOMAL_MODE, 1);
            break;
            
        default:
            ESP_LOGW(TAG, "不支持的芯片类型，无法唤醒");
            break;
    }
}

touch_chip_type_t touch_driver_get_chip_type(void)
{
    return touch_data.chip_type;
}

bool touch_driver_is_data_ready(void)
{
    return touch_initialized && touch_data.data_ready;
}
