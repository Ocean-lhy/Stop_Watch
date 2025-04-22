#ifndef RX8130CE_H
#define RX8130CE_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "driver/i2c.h"
#include "i2c_bus.h"

// RX-8130 I2C地址
#define RX8130_I2C_ADDR            0x32

// RX-8130 寄存器定义
#define RX8130_REG_SEC             0x10
#define RX8130_REG_MIN             0x11
#define RX8130_REG_HOUR            0x12
#define RX8130_REG_WDAY            0x13
#define RX8130_REG_MDAY            0x14
#define RX8130_REG_MONTH           0x15
#define RX8130_REG_YEAR            0x16

#define RX8130_REG_ALMIN           0x17
#define RX8130_REG_ALHOUR          0x18
#define RX8130_REG_ALWDAY          0x19
#define RX8130_REG_TCOUNT0         0x1A
#define RX8130_REG_TCOUNT1         0x1B
#define RX8130_REG_EXT             0x1C
#define RX8130_REG_FLAG            0x1D
#define RX8130_REG_CTRL0           0x1E
#define RX8130_REG_CTRL1           0x1F

// 扩展寄存器 (1Ch) 位定义
#define RX8130_BIT_EXT_TSEL        (7 << 0)
#define RX8130_BIT_EXT_WADA        (1 << 3)
#define RX8130_BIT_EXT_TE          (1 << 4)
#define RX8130_BIT_EXT_USEL        (1 << 5)
#define RX8130_BIT_EXT_FSEL        (3 << 6)

// 标志寄存器 (1Dh) 位定义
#define RX8130_BIT_FLAG_VLF        (1 << 1)
#define RX8130_BIT_FLAG_AF         (1 << 3)
#define RX8130_BIT_FLAG_TF         (1 << 4)
#define RX8130_BIT_FLAG_UF         (1 << 5)

// 控制寄存器0 (1Eh) 位定义
#define RX8130_BIT_CTRL_TSTP       (1 << 2)
#define RX8130_BIT_CTRL_AIE        (1 << 3)
#define RX8130_BIT_CTRL_TIE        (1 << 4)
#define RX8130_BIT_CTRL_UIE        (1 << 5)
#define RX8130_BIT_CTRL_STOP       (1 << 6)
#define RX8130_BIT_CTRL_TEST       (1 << 7)

// 结构体定义
typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} rx8130_datetime_t;

typedef struct {
    uint8_t minute;
    uint8_t hour;
    uint8_t day_date;
    bool use_wday;   // true使用星期，false使用日期
} rx8130_alarm_t;

// 函数声明
/**
 * @brief 初始化RX8130 RTC
 * 
 * @param i2c_bus I2C总线句柄
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_init(i2c_bus_handle_t i2c_bus);

/**
 * @brief 获取RTC当前时间
 * 
 * @param datetime 日期时间结构体指针
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_get_time(rx8130_datetime_t *datetime);

/**
 * @brief 设置RTC时间
 * 
 * @param datetime 日期时间结构体指针
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_set_time(const rx8130_datetime_t *datetime);

/**
 * @brief 检查电压低标志
 * 
 * @param vl_flag 电压低标志状态指针
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_check_voltage_low(bool *vl_flag);

/**
 * @brief 清除电压低标志
 * 
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_clear_voltage_low(void);

/**
 * @brief 关闭RTC所有中断，避免nIRQ引脚异常触发
 * 
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_disable_all_interrupts(void);

/**
 * @brief 设置定时器
 * 
 * @param seconds 秒数，有效范围1-4095秒
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_set_timer(uint16_t seconds);

/**
 * @brief 启用或禁用定时器
 * 
 * @param enable 是否启用
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_enable_timer(bool enable);

/**
 * @brief 检查定时器是否触发
 * 
 * @param triggered 定时器触发状态指针
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_is_timer_triggered(bool *triggered);

/**
 * @brief 清除定时器触发标志
 * 
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_clear_timer_flag(void);

/**
 * @brief 设置关机定时器模式
 * 此模式下，只有定时器会激活nIRQ引脚，适用于定时开机
 * 
 * @param seconds 定时器秒数，1-4095秒
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_set_shutdown_timer_mode(uint16_t seconds);

/**
 * @brief 直接读取RTC寄存器
 * 
 * @param reg_addr 寄存器地址
 * @param data 数据指针
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_read_reg(uint8_t reg_addr, uint8_t *data);

/**
 * @brief 直接写入RTC寄存器
 * 
 * @param reg_addr 寄存器地址
 * @param data 数据
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t rx8130_write_reg(uint8_t reg_addr, uint8_t data);

/**
 * @brief 打印时间
 * 
 * @param datetime 日期时间结构体指针
 */
void print_time(rx8130_datetime_t *datetime);

/**
 * @brief 设置闹钟
 * 
 * @param current_time 当前时间
 * @param alarm_time 闹钟时间（分钟）
 */
void set_alarm(rx8130_datetime_t *current_time, uint32_t alarm_time);

#endif /* RX8130CE_H */

