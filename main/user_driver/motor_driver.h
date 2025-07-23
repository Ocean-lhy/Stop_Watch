#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "esp_err.h"
#include "stdbool.h"

// 注意：电机控制现在通过PY32 I2C扩展器的PWM功能实现
// 使用GPIO_PIN_10 (PA7-IO10)，由py32_driver管理

// 初始化电机
void motor_init();

// 启动电机振动
void motor_enable();

// 停止电机振动
void motor_disable();

// 控制电机运行，参数：强度(0-100)，持续时间(ms)
esp_err_t motor_run(uint8_t intensity, uint32_t duration_ms);

// 立即停止电机
void motor_stop();

// 按钮震动 中断中调用
esp_err_t button_vibrate(void);

void set_vibrate_cmd(uint8_t intensity, uint32_t duration_ms, uint32_t interval_ms);

// 获取电机振动命令
void get_vibrate_cmd(uint8_t *intensity, uint32_t *duration_ms, uint32_t *interval_ms);

// PWM频率控制
esp_err_t motor_set_frequency(uint16_t frequency);
esp_err_t motor_get_frequency(uint16_t *frequency);

// PWM状态读取
esp_err_t motor_get_pwm_status(uint8_t *duty_percent, bool *polarity, bool *enable);



#endif // MOTOR_DRIVER_H