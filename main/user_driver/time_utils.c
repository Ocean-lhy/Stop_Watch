#include "time_utils.h"
#include <string.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_sntp.h"
#include "esp_netif.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "rx8130ce.h"
#include "esp_timer.h"
#include <sys/time.h>

#define TAG "time_utils"

/* WiFi事件组位定义 */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

/* 最大WiFi连接尝试次数 */
#define MAX_RETRY_COUNT 5

static EventGroupHandle_t s_wifi_event_group;
static int s_retry_num = 0;
static bool wifi_connected = false;
static bool sntp_initialized = false;

// 用于记录RTC校准时的系统时间戳（微秒）
static int64_t rtc_calibration_time_us = 0;
// 用于记录RTC校准时的RTC时间戳（秒）
static time_t rtc_calibration_time_sec = 0;

/* WiFi事件处理函数 */
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                              int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < MAX_RETRY_COUNT) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "重试连接WiFi...");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
            wifi_connected = false;
        }
        ESP_LOGI(TAG, "连接WiFi失败");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "获取IP地址:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        wifi_connected = true;
    }
}

/* SNTP时间同步回调函数 */
static void sntp_sync_time_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "SNTP时间同步成功");
    time_t now = 0;
    struct tm timeinfo = {0};
    time(&now);
    localtime_r(&now, &timeinfo);
    
    char strftime_buf[64];
    strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d %H:%M:%S %Z", &timeinfo);
    ESP_LOGI(TAG, "北京时间: %s", strftime_buf);
}

esp_err_t time_utils_init(void)
{
    ESP_LOGI(TAG, "初始化时间模块");
    
    // 初始化默认NetIF
    ESP_ERROR_CHECK(esp_netif_init());
    
    // 创建默认事件循环
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    return ESP_OK;
}

esp_err_t time_utils_connect_wifi(const char *ssid, const char *password)
{
    if (wifi_connected) {
        ESP_LOGI(TAG, "WiFi已连接");
        return ESP_OK;
    }
    
    ESP_LOGI(TAG, "连接WiFi SSID: %s", ssid);
    
    // 创建WiFi事件组
    s_wifi_event_group = xEventGroupCreate();
    
    // 创建默认WiFi站点
    esp_netif_create_default_wifi_sta();
    
    // 初始化WiFi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    
    // 注册WiFi事件处理程序
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL));
    
    // 配置WiFi站点
    wifi_config_t wifi_config = {0};
    strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);
    
    // 设置WiFi模式并启动
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    
    ESP_LOGI(TAG, "等待WiFi连接...");
    
    // 等待WiFi连接成功或失败
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                          WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                          pdFALSE,
                                          pdFALSE,
                                          pdMS_TO_TICKS(20000)); // 20秒超时
    
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "成功连接到WiFi SSID: %s", ssid);
        wifi_connected = true;
        return ESP_OK;
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGE(TAG, "连接WiFi失败: SSID: %s, 密码: %s", ssid, password);
        wifi_connected = false;
        return ESP_FAIL;
    } else {
        ESP_LOGE(TAG, "连接WiFi超时");
        wifi_connected = false;
        return ESP_ERR_TIMEOUT;
    }
}

esp_err_t time_utils_sync_ntp(void)
{
    if (!wifi_connected) {
        ESP_LOGE(TAG, "WiFi未连接，无法同步网络时间");
        return ESP_FAIL;
    }
    
    ESP_LOGI(TAG, "开始同步北京时间");
    
    // 设置中国时区 (UTC+8)
    setenv("TZ", "CST-8", 1);
    tzset();
    
    // 初始化SNTP
    if (!sntp_initialized) {
        ESP_LOGI(TAG, "初始化SNTP");
        esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
        
        // 使用中国的NTP服务器
        esp_sntp_setservername(0, "ntp.aliyun.com");         // 阿里云NTP服务器
        esp_sntp_setservername(1, "ntp.ntsc.ac.cn");         // 中国科学院国家授时中心
        esp_sntp_setservername(2, "cn.ntp.org.cn");          // 中国NTP服务器
        esp_sntp_setservername(3, "ntp.tencent.com");        // 腾讯NTP服务器
        
        sntp_set_time_sync_notification_cb(sntp_sync_time_cb);
        sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
        esp_sntp_init();
        sntp_initialized = true;
    }
    
    // 等待时间同步
    // 设置超时：20秒
    int retry = 0;
    const int max_retry = 10;
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < max_retry) {
        ESP_LOGI(TAG, "等待NTP同步...");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    
    if (retry >= max_retry) {
        ESP_LOGE(TAG, "NTP同步超时");
        return ESP_ERR_TIMEOUT;
    }
    
    // 打印当前系统时间
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    char strftime_buf[64];
    strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d %H:%M:%S %Z", &timeinfo);
    ESP_LOGI(TAG, "NTP同步完成，北京时间: %s", strftime_buf);
    
    return ESP_OK;
}

esp_err_t time_utils_calibrate_rtc(void)
{
    ESP_LOGI(TAG, "校准RTC时间");
    
    // 获取系统时间
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    
    // 记录校准时的系统时间戳（用于后续计算毫秒级时间）
    rtc_calibration_time_sec = now;
    rtc_calibration_time_us = esp_timer_get_time();
    
    // 打印系统时间
    char strftime_buf[64];
    strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d %H:%M:%S %Z", &timeinfo);
    ESP_LOGI(TAG, "系统时间(北京): %s", strftime_buf);
    
    // 转换为RTC时间格式
    rx8130_datetime_t rtc_time;
    rtc_time.year = timeinfo.tm_year % 100;  // tm_year从1900年开始，RTC只需要后两位
    rtc_time.month = timeinfo.tm_mon + 1;    // tm_mon从0开始
    rtc_time.date = timeinfo.tm_mday;
    rtc_time.hour = timeinfo.tm_hour;
    rtc_time.minute = timeinfo.tm_min;
    rtc_time.second = timeinfo.tm_sec;
    rtc_time.day = timeinfo.tm_wday;         // 星期几 (0-6, 星期日=0)
    
    // 将系统时间写入RTC
    esp_err_t ret = rx8130_set_time(&rtc_time);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "设置RTC时间失败");
        return ret;
    }
    
    ESP_LOGI(TAG, "RTC时间校准成功");
    return ESP_OK;
}

esp_err_t time_utils_get_time(rx8130_datetime_t *datetime)
{
    if (datetime == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    
    // 从RTC获取时间
    esp_err_t ret = rx8130_get_time(datetime);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "获取RTC时间失败");
        return ret;
    }
    
    ESP_LOGI(TAG, "当前时间: %02d/%02d/%02d %02d:%02d:%02d 星期%d",
             datetime->year, datetime->month, datetime->date,
             datetime->hour, datetime->minute, datetime->second,
             datetime->day);
    
    return ESP_OK;
}

esp_err_t time_utils_set_time(const rx8130_datetime_t *datetime)
{
    if (datetime == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    
    // 手动设置RTC时间
    esp_err_t ret = rx8130_set_time(datetime);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "手动设置RTC时间失败");
        return ret;
    }
    
    // 更新校准基准点
    struct tm timeinfo = {0};
    timeinfo.tm_year = datetime->year + 100;  // 假设是21世纪（2000-2099年）
    timeinfo.tm_mon = datetime->month - 1;    // tm_mon从0开始
    timeinfo.tm_mday = datetime->date;
    timeinfo.tm_hour = datetime->hour;
    timeinfo.tm_min = datetime->minute;
    timeinfo.tm_sec = datetime->second;
    timeinfo.tm_wday = datetime->day;
    
    rtc_calibration_time_sec = mktime(&timeinfo);
    rtc_calibration_time_us = esp_timer_get_time();
    
    ESP_LOGI(TAG, "手动设置时间成功: %02d/%02d/%02d %02d:%02d:%02d 星期%d",
             datetime->year, datetime->month, datetime->date,
             datetime->hour, datetime->minute, datetime->second,
             datetime->day);
    
    return ESP_OK;
}

esp_err_t time_utils_disconnect_wifi(void)
{
    if (!wifi_connected) {
        ESP_LOGI(TAG, "WiFi未连接");
        return ESP_OK;
    }
    
    ESP_LOGI(TAG, "断开WiFi连接");
    
    // 停止SNTP服务
    if (sntp_initialized) {
        esp_sntp_stop();
        sntp_initialized = false;
    }
    
    // 断开WiFi连接
    ESP_ERROR_CHECK(esp_wifi_disconnect());
    ESP_ERROR_CHECK(esp_wifi_stop());
    
    // 注销事件处理程序
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler));
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler));
    
    // 删除事件组
    if (s_wifi_event_group != NULL) {
        vEventGroupDelete(s_wifi_event_group);
        s_wifi_event_group = NULL;
    }
    
    wifi_connected = false;
    ESP_LOGI(TAG, "WiFi已断开");
    
    return ESP_OK;
}

/**
 * @brief 获取毫秒级时间
 * 
 * 基于RTC和系统时间计算，提供毫秒级精度的时间
 */
esp_err_t time_utils_get_time_ms(time_utils_time_t *time)
{
    if (time == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    
    // 从RTC获取基础时间
    esp_err_t ret = rx8130_get_time(&time->datetime);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "获取RTC时间失败");
        return ret;
    }
    
    // 如果没有进行过校准，则毫秒设为0
    if (rtc_calibration_time_sec == 0) {
        time->milliseconds = 0;
        ESP_LOGW(TAG, "RTC未校准，无法提供毫秒级精度");
        return ESP_OK;
    }
    
    // 计算当前系统时间与校准时的偏差
    int64_t current_time_us = esp_timer_get_time();
    int64_t elapsed_us = current_time_us - rtc_calibration_time_us;
    
    // 转换当前RTC时间为秒级时间戳
    struct tm timeinfo = {0};
    timeinfo.tm_year = time->datetime.year + 100;  // 假设是21世纪（2000-2099年）
    timeinfo.tm_mon = time->datetime.month - 1;    // tm_mon从0开始
    timeinfo.tm_mday = time->datetime.date;
    timeinfo.tm_hour = time->datetime.hour;
    timeinfo.tm_min = time->datetime.minute;
    timeinfo.tm_sec = time->datetime.second;
    timeinfo.tm_wday = time->datetime.day;
    
    time_t current_rtc_sec = mktime(&timeinfo);
    
    // 计算RTC时钟偏差（秒）
    int64_t rtc_diff_sec = (int64_t)current_rtc_sec - (int64_t)rtc_calibration_time_sec;
    
    // 计算系统时钟过去的秒数
    int64_t sys_elapsed_sec = elapsed_us / 1000000;
    
    // 对比RTC和系统时间，如果差距过大，可能需要重新校准
    if (llabs(rtc_diff_sec - sys_elapsed_sec) > 5) {
        ESP_LOGW(TAG, "RTC与系统时间差距过大，可能需要重新校准: RTC偏差=%lld秒, 系统偏差=%lld秒", 
                 rtc_diff_sec, sys_elapsed_sec);
    }
    
    // 计算当前亚秒级时间（毫秒）
    // 使用系统时间精确计算经过的微秒数对1000000取模，转换为毫秒
    int64_t elapsed_ms = elapsed_us / 1000;
    time->milliseconds = (elapsed_ms % 1000);
    
    ESP_LOGD(TAG, "当前毫秒级时间: %02d/%02d/%02d %02d:%02d:%02d.%03d 星期%d",
             time->datetime.year, time->datetime.month, time->datetime.date,
             time->datetime.hour, time->datetime.minute, time->datetime.second,
             time->milliseconds, time->datetime.day);
    
    return ESP_OK;
}

/**
 * @brief 获取系统启动以来的毫秒数
 * 
 * 使用ESP定时器获取系统启动以来的毫秒数
 */
uint64_t time_utils_get_system_time_ms(void)
{
    // esp_timer_get_time() 返回微秒数，转换为毫秒
    return (uint64_t)(esp_timer_get_time() / 1000);
} 