#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "driver/gpio.h"
#include "esp_err.h"

// 电机控制引脚定义
#define MOTOR_ENABLE_PIN (gpio_num_t)13

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



#endif // MOTOR_DRIVER_H