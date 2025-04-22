#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "esp_idf_version.h"
#include "esp_flash.h"
#include "esp_chip_info.h"
#include "spi_flash_mmap.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#include "esp_littlefs.h"

// I2C定义
#define SYS_I2C_SCL (gpio_num_t)48
#define SYS_I2C_SDA (gpio_num_t)47
#define I2C_DEV_TIMEOUT 4000000

// 按钮定义
#define USER_BUTTON1_PIN (gpio_num_t)1
#define USER_BUTTON2_PIN (gpio_num_t)2

// power off
#define PWROFF_PLUSE_PIN (gpio_num_t)12

// 中断管脚
#define TP_INT_IRQ_PIN (gpio_num_t)21

// Grove接口
#define GROVE_3_PIN (gpio_num_t)9
#define GROVE_4_PIN (gpio_num_t)10

// bit操作宏
#define setbit(x, y) x |= (0x01 << y)
#define clrbit(x, y) x &= ~(0x01 << y)
#define reversebit(x, y) x ^= (0x01 << y)
#define getbit(x, y) ((x) >> (y) & 0x01)

// 外部变量声明
extern uint8_t btn1, btn2;
extern volatile bool touch_irq_flag;

// 打印芯片信息
void print_chip_info();

// 初始化中断
bool global_irq_init();

// 中断处理函数
void global_irq_handler(void *arg);

// 进入轻度睡眠模式
void enter_light_sleep_mode();

// 进入深度睡眠模式
void enter_deep_sleep_mode();

// 初始化NVS
void nvs_init();

// Grove I2C测试
void grove_i2c_test();

// 电源关机
void power_off();

#endif // SYSTEM_UTILS_H 