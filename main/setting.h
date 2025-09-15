#pragma once

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "sdkconfig.h"

#define WIFI_SSID "ocean"
#define WIFI_PASSWORD "oceanocean"

// I2C设备地址
#define CST820_ADDR 0x15
#define ES8311_ADDR 0x18
#define RX8130_ADDR 0x32
#define BMI270_ADDR 0x68
#define PM1_ADDR 0x6E
#define IO_EXPANDER_ADDR 0x6F

// I2S引脚定义
#define I2S_MCLK_PIN (gpio_num_t)18
#define I2S_BCLK_PIN (gpio_num_t)17
#define I2S_DADC_IN_PIN (gpio_num_t)16
#define I2S_LRCK_PIN (gpio_num_t)15
#define I2S_DDAC_OUT_PIN (gpio_num_t)21

// I2C引脚定义
#define I2C_SCL_PIN (gpio_num_t)48
#define I2C_SDA_PIN (gpio_num_t)47
#define I2C_FREQ 100000 // 100KHz
#define I2C_DEV_TIMEOUT 4000000

// 按钮定义
#define USER_BUTTON1_PIN (gpio_num_t)1
#define USER_BUTTON2_PIN (gpio_num_t)2

// 中断管脚
#define IRQ_PIN (gpio_num_t)12
#define TP_INT_IRQ_PIN TOUCH_INT_PIN

// Grove接口
#define GROVE_3_PIN (gpio_num_t)10
#define GROVE_4_PIN (gpio_num_t)11

// LCD引脚定义
#define QSPI_TE_PIN (gpio_num_t)38
#define QSPI_CS_PIN (gpio_num_t)39
#define QSPI_SCLK_PIN (gpio_num_t)40
#define QSPI_D0_PIN (gpio_num_t)41
#define QSPI_D1_PIN (gpio_num_t)42
#define QSPI_D2_PIN (gpio_num_t)46
#define QSPI_D3_PIN (gpio_num_t)45
#define QSPI_RST_PIN (gpio_num_t)-1 // PY32 BIT 14

// 触摸屏引脚定义
#define TOUCH_INT_PIN (gpio_num_t)13
#define TOUCH_RST_PIN (gpio_num_t)14
#define TOUCH_SCL_PIN I2C_SCL_PIN
#define TOUCH_SDA_PIN I2C_SDA_PIN

// LCD主机和触摸主机
#define LCD_HOST    SPI2_HOST
#define TOUCH_HOST  I2C_NUM_0

// LCD参数
#define LCD_BIT_PER_PIXEL       (16)
#define EXAMPLE_LCD_H_RES       466
#define EXAMPLE_LCD_V_RES       466

// LVGL参数
#define EXAMPLE_LVGL_TICK_PERIOD_MS    1
#define EXAMPLE_LVGL_TASK_MAX_DELAY_MS 500
#define EXAMPLE_LVGL_TASK_MIN_DELAY_MS 1
#define EXAMPLE_LVGL_TASK_STACK_SIZE   (32 * 1024)
#define EXAMPLE_LVGL_TASK_PRIORITY     (configMAX_PRIORITIES - 2)