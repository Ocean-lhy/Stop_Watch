#include "lcd_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cst9217_driver.h"
#include "driver/spi_master.h"
#include "gui_guider.h"
#include "esp_timer.h"
#include "esp_lcd_panel_commands.h"
static const char *TAG = "lcd_driver";

lv_disp_draw_buf_t disp_buf; // 包含称为绘制缓冲区的内部图形缓冲区
lv_disp_drv_t disp_drv;      // 包含回调函数
SemaphoreHandle_t lvgl_mux = NULL;
static esp_lcd_panel_handle_t panel_handle = NULL;
static esp_lcd_touch_handle_t tp = NULL;
static esp_lcd_panel_io_handle_t io_handle = NULL;
// extern lv_ui guider_ui;

bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

void example_touch_isr_cb(esp_lcd_touch_handle_t tp)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(touch_mux, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
    }
}

void example_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
    // 将缓冲区的内容复制到显示的特定区域
    esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map);
}

void example_lvgl_rounder_cb(struct _lv_disp_drv_t *disp_drv, lv_area_t *area)
{
    // round the start of coordinate down to the nearest 2M number
    area->x1 = (area->x1 >> 1) << 1;
    area->y1 = (area->y1 >> 1) << 1;
    // round the end of coordinate up to the nearest 2N+1 number
    area->x2 = ((area->x2 >> 1) << 1) + 1;
    area->y2 = ((area->y2 >> 1) << 1) + 1;
    return;
}

void example_lvgl_update_cb(lv_disp_drv_t *drv)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;

    switch (drv->rotated) {
    case LV_DISP_ROT_NONE:
        // 旋转液晶显示屏
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, true, false);
        // 旋转液晶触摸
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
        break;
    case LV_DISP_ROT_90:
        // 旋转液晶显示屏
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, true, true);
        // 旋转液晶触摸
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
        break;
    case LV_DISP_ROT_180:
        // 旋转液晶显示屏
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, false, true);
        // 旋转液晶触摸
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
        break;
    case LV_DISP_ROT_270:
        // 旋转液晶显示屏
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, false, false);
        // 旋转液晶触摸
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
        break;
    }
}

void example_increase_lvgl_tick(void *arg)
{
    /* 告诉 LVGL 已经过去了多少毫秒*/
    lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}

void example_lvgl_touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    bool tp_pressed = false;
    /* 将触摸控制器中的数据读取到内存中 */
    if (touch_mux == NULL)
    {
        ESP_LOGE(TAG, "touch_mux is NULL");
        return;
    }
    if (xSemaphoreTake(touch_mux, portMAX_DELAY) == pdTRUE)
    {
        cst9217_update();
        tp_pressed = tp_info[0].switch_ != 0x00 ? true : false;
        touch_irq_flag = 0;
        xSemaphoreGive(touch_mux);
    }

    /* 从触摸控制器读取数据 */
    if (tp_pressed)
    {
        data->point.x = EXAMPLE_LCD_H_RES - tp_info[0].x;
        data->point.y = EXAMPLE_LCD_V_RES - tp_info[0].y;
        data->state = LV_INDEV_STATE_PRESSED;
        // ESP_LOGI(TAG, "Touch position: %d,%d", data->point.x, data->point.y);
    }
}

bool example_lvgl_lock(int timeout_ms)
{
    assert(lvgl_mux && "bsp_display_start must be called first");

    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTake(lvgl_mux, timeout_ticks) == pdTRUE;
}

void example_lvgl_unlock(void)
{
    assert(lvgl_mux && "bsp_display_start must be called first");
    xSemaphoreGive(lvgl_mux);
}

void example_lvgl_port_task(void *arg)
{
    ESP_LOGI(TAG, "Starting LVGL task");
    uint32_t task_delay_ms = EXAMPLE_LVGL_TASK_MAX_DELAY_MS;
    ESP_LOGI(TAG, "Display LVGL demos");
    if (example_lvgl_lock(-1)) {
        // lv_demo_widgets();      /* 小部件示例 */
        // lv_demo_music();        /* 类似智能手机的现代音乐播放器演示 */
        // lv_demo_stress();       /* LVGL 压力测试 */
        // lv_demo_benchmark();    /* 用于测量 LVGL 性能或比较不同设置的演示 */
        // ui_init();
        // setup_ui(&guider_ui);
        // 释放互斥锁
        example_lvgl_unlock();
    }
    while (1) {
        // 由于 LVGL API 不是线程安全的，因此锁定互斥体
        if (example_lvgl_lock(-1)) {
            task_delay_ms = lv_timer_handler();
            // 释放互斥锁
            example_lvgl_unlock();
        }
        if (task_delay_ms > EXAMPLE_LVGL_TASK_MAX_DELAY_MS) {
            task_delay_ms = EXAMPLE_LVGL_TASK_MAX_DELAY_MS;
        } else if (task_delay_ms < EXAMPLE_LVGL_TASK_MIN_DELAY_MS) {
            task_delay_ms = EXAMPLE_LVGL_TASK_MIN_DELAY_MS;
        }
        vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
    }
}

void lcd_init()
{
    ESP_LOGI(TAG, "Initialize SPI bus");
    const spi_bus_config_t buscfg = CO5300_PANEL_BUS_QSPI_CONFIG(QSPI_SCLK_PIN,
                                                                QSPI_D0_PIN,
                                                                QSPI_D1_PIN,
                                                                QSPI_D2_PIN,
                                                                QSPI_D3_PIN,
                                                                EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES * LCD_BIT_PER_PIXEL / 8);
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    ESP_LOGI(TAG, "Install panel IO");
    const esp_lcd_panel_io_spi_config_t io_config = CO5300_PANEL_IO_QSPI_CONFIG(QSPI_CS_PIN, example_notify_lvgl_flush_ready, &disp_drv);
    
    co5300_vendor_config_t vendor_config = {
        .flags = {
            .use_qspi_interface = 1,
        },
    };

    // 将 LCD 连接到 SPI 总线
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = QSPI_RST_PIN,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = LCD_BIT_PER_PIXEL,
        .vendor_config = &vendor_config,
    };

    ESP_LOGI(TAG, "Install CO5300 panel driver");
    ESP_ERROR_CHECK(esp_lcd_new_panel_co5300(io_handle, &panel_config, &panel_handle));
    // ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 6, 0));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();
    size_t psram_size = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
    size_t psram_free = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    ESP_LOGI(TAG, "PSRAM size: %d bytes, free: %d bytes", psram_size, psram_free);
    // 分配 LVGL 使用的绘制缓冲区, 建议选择绘制缓冲区的大小至少为屏幕大小的 1/10
    lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(EXAMPLE_LCD_H_RES * 50, MALLOC_CAP_SPIRAM);
    assert(buf1);
    lv_color_t *buf2 = (lv_color_t *)heap_caps_malloc(EXAMPLE_LCD_H_RES * 50, MALLOC_CAP_SPIRAM);
    assert(buf2);
    // 初始化 LVGL 绘制缓冲区
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, EXAMPLE_LCD_H_RES * 50);

    ESP_LOGI(TAG, "Register display driver to LVGL");
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = EXAMPLE_LCD_H_RES;
    disp_drv.ver_res = EXAMPLE_LCD_V_RES;
    disp_drv.flush_cb = example_lvgl_flush_cb;
    disp_drv.rounder_cb = example_lvgl_rounder_cb;
    disp_drv.drv_update_cb = example_lvgl_update_cb;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = panel_handle;
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

    ESP_LOGI(TAG, "Install LVGL tick timer");
    // LVGL 的 Tick 接口（使用 esp_timer 生成 2ms 周期性事件）
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &example_increase_lvgl_tick,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000));

    static lv_indev_drv_t indev_drv;    // 输入设备驱动程序（触摸）
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = example_lvgl_touch_cb;
    
    lv_indev_drv_register(&indev_drv);

    lvgl_mux = xSemaphoreCreateMutex();
    assert(lvgl_mux);
    xTaskCreate(example_lvgl_port_task, "LVGL", EXAMPLE_LVGL_TASK_STACK_SIZE, NULL, EXAMPLE_LVGL_TASK_PRIORITY, NULL);

    
}

void lcd_set_brightness(uint8_t brightness)
{
    if (io_handle == NULL)
    {
        ESP_LOGE(TAG, "LCD driver not initialized");
        return;
    }
    int lcd_cmd = LCD_CMD_WRDISBV & 0xFF;
    lcd_cmd <<= 8;
    lcd_cmd |= 0x02ULL << 24;
    ESP_ERROR_CHECK(esp_lcd_panel_io_tx_param(io_handle, lcd_cmd, &brightness, 1));
    ESP_LOGI(TAG, "Set brightness to %d", brightness);

    esp_lcd_panel_io_rx_param(io_handle, LCD_CMD_RDDISBV, &brightness, 1);
    ESP_LOGI(TAG, "Get brightness: %d", brightness);
}