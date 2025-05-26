#ifndef TOUCH_DRIVER_H
#define TOUCH_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "i2c_bus.h"
#include "system_utils.h"

// 最大支持触摸点数
#define TOUCH_MAX_POINTS 5

// 触摸芯片类型
typedef enum {
    TOUCH_CHIP_NONE = 0,
    TOUCH_CHIP_CST820,
    TOUCH_CHIP_CST9217
} touch_chip_type_t;

// 触摸状态
typedef enum {
    TOUCH_STATUS_PRESSED = 0,   // 按下
    TOUCH_STATUS_RELEASED = 1,  // 抬起
    TOUCH_STATUS_CONTACT = 2    // 保持或移动
} touch_status_t;

// 统一的触摸点信息结构
typedef struct {
    uint8_t id;              // 触摸点ID
    uint16_t x;              // X坐标
    uint16_t y;              // Y坐标
    uint8_t pressure;        // 压力值
    touch_status_t status;   // 触摸状态
    bool valid;              // 数据是否有效
} touch_point_t;

// 触摸数据结构
typedef struct {
    uint8_t point_count;                    // 当前触摸点数量
    touch_point_t points[TOUCH_MAX_POINTS]; // 触摸点数组
    touch_chip_type_t chip_type;            // 芯片类型
    bool data_ready;                        // 数据是否准备好
} touch_data_t;

/**
 * @brief 初始化触摸屏驱动
 * @param i2c_bus I2C总线句柄
 * @return 0:成功 -1:失败
 */
int touch_driver_init(i2c_bus_handle_t i2c_bus);

/**
 * @brief 更新触摸数据
 * @return 0:成功 -1:失败
 */
int touch_driver_update(void);

/**
 * @brief 获取触摸数据
 * @param data 输出的触摸数据指针
 * @return 0:成功 -1:失败
 */
int touch_driver_get_data(touch_data_t *data);

/**
 * @brief 获取第一个触摸点坐标（兼容性接口）
 * @param x X坐标指针
 * @param y Y坐标指针
 * @param status 触摸状态指针
 * @return true:有触摸 false:无触摸
 */
bool touch_driver_get_point(uint16_t *x, uint16_t *y, touch_status_t *status);

/**
 * @brief 设置触摸屏休眠
 */
void touch_driver_sleep(void);

/**
 * @brief 唤醒触摸屏
 */
void touch_driver_wakeup(void);

/**
 * @brief 获取芯片类型
 * @return 芯片类型
 */
touch_chip_type_t touch_driver_get_chip_type(void);

/**
 * @brief 检查触摸数据是否准备好
 * @return true:准备好 false:未准备好
 */
bool touch_driver_is_data_ready(void);

#endif // TOUCH_DRIVER_H
