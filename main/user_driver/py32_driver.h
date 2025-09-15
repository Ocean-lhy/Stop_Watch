#ifndef PY32_DRIVER_H
#define PY32_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "i2c_bus.h"

#ifdef __cplusplus
extern "C" {
#endif

// PY32引脚功能映射 (基于I2C扩展器GPIO引脚定义)
#define PY32_MUX_CTR_PIN       12  // GPIO_PIN_3 (PA2-IO13): CH442E MUX控制 临时飞线

#define PY32_AU_EN_PIN         2  // GPIO_PIN_3 (PA1-IO3): 音频使能
#define PY32_L3B_EN_PIN        7  // GPIO_PIN_8 (PB0-IO8): L3B使能
#define PY32_MOTOR_EN_PIN      8  // GPIO_PIN_9 (PA0-IO9): 电机使能(PWM)
#define PY32_SPK_EN_PIN        10 // GPIO_PIN_11 (PB2-IO11): 扬声器使能
#define PY32_OLED_RST_PIN      13 // GPIO_PIN_14 (PB7-IO14): OLED复位

// PWM通道定义
#define PY32_MOTOR_PWM_CHANNEL 0  // PWM_CHANNEL_1对应IO9(PA0)

// MUX控制模式定义
typedef enum {
    PY32_MUX_MODE_U0  = 0,  // 连接U0串口
    PY32_MUX_MODE_USB = 1   // 连接USB
} py32_mux_mode_t;

/**
 * @brief 初始化PY32驱动
 * @param i2c_bus I2C总线句柄
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_init(i2c_bus_handle_t i2c_bus);

/**
 * @brief 反初始化PY32驱动
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_deinit(void);

/**
 * @brief 启用扬声器
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_speaker_enable(void);

/**
 * @brief 禁用扬声器
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_speaker_disable(void);

/**
 * @brief 启用音频
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_au_enable(void);

/**
 * @brief 禁用音频
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_au_disable(void);

/**
 * @brief 启用L3B
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_l3b_enable(void);

/**
 * @brief 禁用L3B
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_l3b_disable(void);

/**
 * @brief 复位OLED/LCD显示屏
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_lcd_reset(void);

/**
 * @brief 设置CH442E MUX模式
 * @param mode MUX模式，选择U0串口或USB连接
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_mux_set_mode(py32_mux_mode_t mode);

/**
 * @brief 获取CH442E MUX当前模式
 * @param mode 返回当前MUX模式
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_mux_get_mode(py32_mux_mode_t *mode);

/**
 * @brief 设置电机PWM占空比
 * @param duty_percent 占空比百分比 (0-100)
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_motor_set_pwm(uint8_t duty_percent);

/**
 * @brief 启用电机
 * @param duty_percent PWM占空比百分比 (0-100)
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_motor_enable(uint8_t duty_percent);

/**
 * @brief 禁用电机
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_motor_disable(void);

/**
 * @brief 设置电机PWM频率
 * @param frequency PWM频率(Hz)
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_motor_set_frequency(uint16_t frequency);

/**
 * @brief 获取电机PWM频率
 * @param frequency 返回PWM频率(Hz)
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_motor_get_frequency(uint16_t *frequency);

/**
 * @brief 获取电机PWM占空比
 * @param duty_percent 返回占空比百分比(0-100)
 * @param polarity 返回极性
 * @param enable 返回使能状态
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_motor_get_pwm(uint8_t *duty_percent, bool *polarity, bool *enable);

/**
 * @brief 设置PY32睡眠模式
 * @param sleep_mode 睡眠模式: 0=唤醒, 1=轻睡眠, 2=深睡眠
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_sleep(uint8_t sleep_mode);

/**
 * @brief 释放所有引脚到默认状态
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_release_all(void);

#ifdef __cplusplus
}
#endif

#endif  // PY32_DRIVER_H