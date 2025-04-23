#ifndef PI4IO_DRIVER_H
#define PI4IO_DRIVER_H

#include <stdint.h>
#include "i2c_bus.h"

// PI4IO设备地址
#define PI4IO_ADDR 0x43

// PI4IO寄存器定义
#define PI4IO_REG_CHIP_RESET 0x01
#define PI4IO_REG_IO_DIR 0x03
#define PI4IO_REG_OUT_SET 0x05
#define PI4IO_REG_OUT_H_IM 0x07
#define PI4IO_REG_IN_DEF_STA 0x09
#define PI4IO_REG_PULL_EN 0x0B
#define PI4IO_REG_PULL_SEL 0x0D
#define PI4IO_REG_IN_STA 0x0F
#define PI4IO_REG_INT_MASK 0x11
#define PI4IO_REG_IRQ_STA 0x13

// 初始化PI4IO
void pi4io_init(i2c_bus_handle_t i2c_bus);

// 释放所有引脚
void pi4io_release_all();

// LCD复位
void pi4io_lcd_reset();

// 触摸屏复位
void pi4io_tp_reset();

// 启用扬声器
void pi4io_speaker_enable();

// 禁用扬声器
void pi4io_speaker_disable();

// 检测输入电压
uint8_t pi4io_vin_detect();

// 启用5V输出
void pi4io_5V_out_enable();

// 禁用5V输出
void pi4io_5V_out_disable();

// 设置睡眠模式
void pi4io_sleep(uint8_t sleep);

#endif // PI4IO_DRIVER_H 