#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <stdint.h>
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_co5300.h"
#include "esp_lcd_touch_cst9217.h"
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

// LCD引脚定义
#define QSPI_TE_PIN (gpio_num_t)38
#define QSPI_CS_PIN (gpio_num_t)39
#define QSPI_SCLK_PIN (gpio_num_t)40
#define QSPI_D0_PIN (gpio_num_t)41
#define QSPI_D1_PIN (gpio_num_t)42
#define QSPI_D2_PIN (gpio_num_t)46
#define QSPI_D3_PIN (gpio_num_t)45
#define QSPI_RST_PIN (gpio_num_t)-1 // PI4IO BIT 1

// 触摸屏引脚定义
#define TOUCH_INT_PIN (gpio_num_t)21
#define TOUCH_RST_PIN (gpio_num_t)-1 // PI4IO BIT 0
#define TOUCH_SCL_PIN (gpio_num_t)48
#define TOUCH_SDA_PIN (gpio_num_t)47

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
#define EXAMPLE_LVGL_TASK_PRIORITY     2

// 外部变量声明
extern SemaphoreHandle_t lvgl_mux;
extern lv_disp_drv_t disp_drv;

// 初始化LCD和LVGL
void lcd_init();

// LVGL刷新回调
bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx);

// 触摸中断回调
void example_touch_isr_cb(esp_lcd_touch_handle_t tp);

// LVGL显示回调
void example_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map);

// LVGL更新回调
void example_lvgl_update_cb(lv_disp_drv_t *drv);

// LVGL圆角回调
void example_lvgl_rounder_cb(struct _lv_disp_drv_t *disp_drv, lv_area_t *area);

// LVGL触摸回调
void example_lvgl_touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data);

// LVGL增加Tick计数
void example_increase_lvgl_tick(void *arg);

// LVGL锁定函数
bool example_lvgl_lock(int timeout_ms);

// LVGL解锁函数
void example_lvgl_unlock(void);

// LVGL任务
void example_lvgl_port_task(void *arg);

// 设置亮度
void lcd_set_brightness(uint8_t brightness);

// 设置休眠
void lcd_set_sleep(bool sleep);

#endif // LCD_DRIVER_H 