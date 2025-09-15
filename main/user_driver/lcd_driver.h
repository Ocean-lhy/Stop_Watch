#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <stdint.h>
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_co5300.h"
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "setting.h"

// 外部变量声明
extern SemaphoreHandle_t lvgl_mux;
extern lv_disp_drv_t disp_drv;

// 初始化LCD和LVGL
void lcd_init();

// LVGL刷新回调
bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx);

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