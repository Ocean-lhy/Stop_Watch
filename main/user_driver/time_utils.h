#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#include "rx8130ce.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 时间结构体，包含毫秒级时间
 */
typedef struct {
    rx8130_datetime_t datetime;  // 日期时间
    uint16_t milliseconds;       // 毫秒 (0-999)
} time_utils_time_t;

/**
 * @brief 初始化时间模块
 * 
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t time_utils_init(void);

/**
 * @brief 连接WiFi
 * 
 * @param ssid WiFi的SSID
 * @param password WiFi的密码
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t time_utils_connect_wifi(const char *ssid, const char *password);

/**
 * @brief 同步网络时间
 * 
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t time_utils_sync_ntp(void);

/**
 * @brief 校准RTC时间模块
 * 
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t time_utils_calibrate_rtc(void);

/**
 * @brief 获取当前时间
 * 
 * @param datetime 时间结构体指针
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t time_utils_get_time(rx8130_datetime_t *datetime);

/**
 * @brief 手动设置时间
 * 
 * @param datetime 时间结构体指针
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t time_utils_set_time(const rx8130_datetime_t *datetime);

/**
 * @brief 断开WiFi连接
 * 
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t time_utils_disconnect_wifi(void);

/**
 * @brief 获取毫秒级时间
 * 
 * @param time 带毫秒的时间结构体指针
 * @return esp_err_t ESP_OK成功，其他失败
 */
esp_err_t time_utils_get_time_ms(time_utils_time_t *time);

/**
 * @brief 获取系统启动以来的毫秒数
 * 
 * @return uint64_t 系统启动以来的毫秒数
 */
uint64_t time_utils_get_system_time_ms(void);

#ifdef __cplusplus
}
#endif

#endif /* TIME_UTILS_H */ 