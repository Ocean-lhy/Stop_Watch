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
#define PY32_TP_RST_PIN        0  // GPIO_PIN_1 (PB5-IO1): 触摸复位
#define PY32_SPK_EN_PIN        1  // GPIO_PIN_2 (PB1-IO2): 扬声器使能
#define PY32_MUX_CTR_PIN       2  // GPIO_PIN_3 (PA1-IO3): CH442E MUX控制
#define PY32_GROVE_DIR_PIN     3  // GPIO_PIN_4 (PA3-IO4): GROVE接口方向控制
#define PY32_VIN_DET_PIN       4  // GPIO_PIN_5 (PA4-IO5): 电压检测(输入)
#define PY32_OLED_RST_PIN      5  // GPIO_PIN_6 (PA5-IO6): OLED复位
#define PY32_GROVE_VOUT_EN_PIN 8  // GPIO_PIN_9 (PA0-IO9): GROVE 5V输出使能
#define PY32_MOTOR_EN_PIN      9  // GPIO_PIN_10 (PA7-IO10): 电机使能(PWM)

// PWM通道定义
#define PY32_MOTOR_PWM_CHANNEL 3  // PWM_CHANNEL_4对应IO10(PA7)

// MUX控制模式定义
typedef enum {
    PY32_MUX_MODE_U0  = 0,  // 连接U0串口
    PY32_MUX_MODE_USB = 1   // 连接USB
} py32_mux_mode_t;

// GROVE接口模式定义
typedef enum {
    PY32_GROVE_MODE_INPUT  = 0,  // GROVE接口输入模式
    PY32_GROVE_MODE_OUTPUT = 1   // GROVE接口输出模式
} py32_grove_mode_t;

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
 * @brief 复位触摸屏
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_tp_reset(void);

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
 * @brief 复位OLED/LCD显示屏
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_lcd_reset(void);

/**
 * @brief 检测输入电压
 * @param detected 返回检测结果，true表示检测到电压
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_vin_detect(bool *detected);

/**
 * @brief 启用GROVE 5V输出
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_grove_5v_enable(void);

/**
 * @brief 禁用GROVE 5V输出
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_grove_5v_disable(void);

/**
 * @brief 设置GROVE接口模式
 * @param mode GROVE接口模式，输入或输出
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_grove_set_mode(py32_grove_mode_t mode);

/**
 * @brief 获取GROVE接口当前模式
 * @param mode 返回当前GROVE接口模式
 * @return ESP_OK成功，其他值失败
 */
esp_err_t py32_grove_get_mode(py32_grove_mode_t *mode);

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