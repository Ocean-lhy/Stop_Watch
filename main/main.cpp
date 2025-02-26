extern "C"
{
#include <math.h>
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/i2s_std.h"
#include "driver/i2s_tdm.h"
#include "esp_timer.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "driver/ledc.h"
#include "driver/rmt_tx.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "i2c_bus.h"
#include "bmi270.h"
#include "ir_nec_encoder.h"

#include "soc/soc_caps.h"
#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

#include "lvgl.h"
#include "lv_demos.h"
#include "esp_lcd_co5300.h"
#include "esp_lcd_touch_cst9217.h"

#include "ui.h"

// 管脚定义

// I2C
#define SYS_I2C_SCL (gpio_num_t)48
#define SYS_I2C_SDA (gpio_num_t)47
#define I2C_DEV_TIMEOUT 4000000

// IRQ
#define TP_INT_IRQ_PIN (gpio_num_t)21
// #define IMU_IRQ_PIN (gpio_num_t)14   // not yet used

// GPIO
#define MOTOR_ENABLE_PIN (gpio_num_t)13
#define PWROFF_PULSE_PIN (gpio_num_t)12
#define EXT_GPIO10_PIN (gpio_num_t)10
#define EXT_GPIO9_PIN (gpio_num_t)9
#define EXT_GPIO8_PIN (gpio_num_t)8
#define EXT_GPIO7_PIN (gpio_num_t)7
#define EXT_GPIO6_PIN (gpio_num_t)6
#define EXT_GPIO5_PIN (gpio_num_t)5
#define EXT_GPIO4_PIN (gpio_num_t)4
#define EXT_GPIO3_PIN (gpio_num_t)3

#define USER_BUTTON1_PIN (gpio_num_t)1
#define USER_BUTTON2_PIN (gpio_num_t)2

// speaker and mic ES8311
#define I2S_MCLK_PIN (gpio_num_t)18
#define I2S_BCLK_PIN (gpio_num_t)17
#define I2S_DADC_PIN (gpio_num_t)16
#define I2S_LRCK_PIN (gpio_num_t)15
#define I2S_DDAT_PIN (gpio_num_t)14
#define I2S_MAX_KEEP SOC_I2S_NUM

// grove
#define GROVE_3_PIN EXT_GPIO9_PIN
#define GROVE_4_PIN EXT_GPIO10_PIN

// QSPI for screen
#define QSPI_TE_PIN (gpio_num_t)38
#define QSPI_CS_PIN (gpio_num_t)39
#define QSPI_SCLK_PIN (gpio_num_t)40
#define QSPI_D0_PIN (gpio_num_t)41
#define QSPI_D1_PIN (gpio_num_t)42
#define QSPI_D2_PIN (gpio_num_t)46
#define QSPI_D3_PIN (gpio_num_t)45
#define QSPI_RST_PIN (gpio_num_t)-1 // PI4IO BIT 1
// TP
#define TOUCH_INT_PIN TP_INT_IRQ_PIN
#define TOUCH_RST_PIN (gpio_num_t)-1 // PI4IO BIT 0
#define TOUCH_SCL_PIN SYS_I2C_SCL
#define TOUCH_SDA_PIN SYS_I2C_SDA

// bit operation
#define setbit(x, y) x |= (0x01 << y)
#define clrbit(x, y) x &= ~(0x01 << y)
#define reversebit(x, y) x ^= (0x01 << y)
#define getbit(x, y) ((x) >> (y) & 0x01)

// I2C device addr
#define PI4IO_ADDR 0x43
#define BMI270_ADDR 0x68
#define BQ27220_ADDR 0x55
#define AW32001_ADDR 0x49
#define ES8311_ADDR 0x18
#define RX8130CE_ADDR 0x32
#define CST9217_ADDR 0x5A

// PI4IO registers
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

// https://www.ti.com/lit/ug/sluubd4a/sluubd4a.pdf?ts=1716290331889&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FBQ27220
// https://github.com/sparkfun/SparkFun_BQ27441_Arduino_Library/blob/master/src/SparkFunBQ27441.cpp
// BQ27220 registers
// TODO:

// AW32001 registers
#define AW32001_REG_PWR_CFG 0x01
#define AW32001_REG_CHR_CUR 0x02
#define AW32001_REG_CHR_VOL 0x04
#define AW32001_REG_SYS_STA 0x08

// LCD TOUCH
#define LCD_HOST    SPI2_HOST
#define TOUCH_HOST  I2C_NUM_0

#define LCD_BIT_PER_PIXEL       (16)

#define EXAMPLE_LCD_H_RES              466
#define EXAMPLE_LCD_V_RES              466

#define EXAMPLE_LVGL_TICK_PERIOD_MS    1
#define EXAMPLE_LVGL_TASK_MAX_DELAY_MS 500
#define EXAMPLE_LVGL_TASK_MIN_DELAY_MS 1
#define EXAMPLE_LVGL_TASK_STACK_SIZE   (4 * 1024)
#define EXAMPLE_LVGL_TASK_PRIORITY     2

#define MAX_POINTS_REPORT 5

#define TAG "main"


    static void print_chip_info();

    i2c_bus_handle_t i2c_bus = NULL;
    i2c_bus_handle_t grove_i2c_bus = NULL;

    static bool volatile touch_irq_flag = false;
    static bool c6_global_irq_init();
    void IRAM_ATTR c6_global_irq_handler(void *arg);

    // MOTOR
    static void motor_init();
    static void motor_enable();
    static void motor_disable();

    // PI4IO
    i2c_bus_device_handle_t pi4io_dev = NULL;
    static bool led_blink = false;
    static uint64_t last_blink_time = 0;
    static bool btn1, btn2 = false;
    static void pi4io_init();
    static void pi4io_lcd_reset();
    static void pi4io_tp_reset();
    static void pi4io_speaker_enable();
    static void pi4io_speaker_disable();
    static uint8_t pi4io_vin_detect();
    static void pi4io_5V_out_enable();
    static void pi4io_5V_out_disable();

    // ES8311
    i2c_bus_device_handle_t es8311_dev = NULL;
    esp_codec_dev_handle_t codec_dev = NULL;
    typedef struct {
        i2s_chan_handle_t tx_handle;
        i2s_chan_handle_t rx_handle;
    } i2s_keep_t;
    static i2s_comm_mode_t i2s_in_mode = I2S_COMM_MODE_STD;
    static i2s_comm_mode_t i2s_out_mode = I2S_COMM_MODE_STD;
    static i2s_keep_t *i2s_keep[I2S_MAX_KEEP];
    static void es8311_codec_init();
    static esp_err_t record_audio(uint8_t* data, size_t size);
    static esp_err_t play_audio(const uint8_t* data, size_t size);

    // BQ27220
    i2c_bus_device_handle_t bq27220_dev = NULL;
    static esp_err_t bq27220_i2c_read(uint8_t reg_addr, uint16_t sub_reg, uint16_t *reg_data);
    static void bq27220_init();
    static void bq27220_exit_sealed();
    static void bq27220_enter_seal();
    static void bq27220_enter_sleep_mode();
    static void bq27220_full_access();
    static void bq27220_read_dev_number();
    static bool bq27220_opration_status_check();
    static void bq27220_enter_cfg_update();
    static void bq27220_opration_config_A();
    static void bq27220_opration_config_B();
    static void bq27220_read_design_capacity();
    static uint16_t bq27220_read_voltage();
    static uint16_t bq27220_read_current();

    // AW32001
    i2c_bus_device_handle_t aw32001_dev = NULL;
    static void aw32001_init();
    static void aw32001_check_status();
    static void aw32001_charge_set(bool en);

// BMI270
#define ACCEL UINT8_C(0x00)
#define GYRO UINT8_C(0x01)
#define AUX UINT8_C(0x02)
    i2c_bus_device_handle_t bmi270_dev = NULL;
    struct bmi2_dev aux_bmi2_dev;
    struct bmi2_sens_config config[3];
    struct bmi2_sens_data bmi_sensor_data = {{0}};
    static uint8_t sensor_list[2] = {BMI2_ACCEL, BMI2_GYRO};
    static void bmi270_dev_init();
    static void bmi270_dev_update();

    // LCD
    static lv_disp_draw_buf_t disp_buf; // 包含称为绘制缓冲区的内部图形缓冲区
    static lv_disp_drv_t disp_drv;      //包含回调函数
    static SemaphoreHandle_t lvgl_mux = NULL;
    static bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx);
    static void example_touch_isr_cb(esp_lcd_touch_handle_t tp);
    static void example_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map);
    static void example_lvgl_update_cb(lv_disp_drv_t *drv);
    static void example_lvgl_rounder_cb(struct _lv_disp_drv_t *disp_drv, lv_area_t *area);
    static void example_lvgl_touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data);
    static void example_increase_lvgl_tick(void *arg);
    static bool example_lvgl_lock(int timeout_ms);
    static void example_lvgl_unlock(void);
    static void example_lvgl_port_task(void *arg);
    static void lcd_init();

    // touch
    enum work_mode{
        NOMAL_MODE = 0,
        GESTURE_MODE = 1,
        LP_MODE = 2,
        DEEPSLEEP = 3,
        DIFF_MODE = 4,
        RAWDATA_MODE = 5,
        BASELINE_MODE = 6,
        CALIBRATE_MODE = 7,
        FAC_TEST_MODE = 8,
        ENTER_BOOT_MODE = 0xCA,
    };
    typedef struct tp_info{
        uint8_t id;
        uint8_t switch_;
        uint16_t x;
        uint16_t y;
        uint16_t z;
    }tp_info_t;
    i2c_bus_device_handle_t cst9217_dev = NULL;
    static SemaphoreHandle_t touch_mux = NULL;
    static esp_lcd_touch_handle_t tp = NULL;
    static tp_info_t tp_info[MAX_POINTS_REPORT];
    static void cst9217_read_chip_id();
    static void cst9217_read_tpinfo();
    static void cst9217_init();
    static void cst9217_read_word_from_mem(uint8_t type, uint16_t addr, uint32_t *value);
    static void cst9217_read_data(uint8_t *data, uint16_t len);
    static void cst9217_set_workmode(enum work_mode mode, uint8_t enable);
    static void cst9217_update();

    // sleep mode test
    static void c6_enter_light_sleep_mode();
    static void c6_enter_deep_sleep_mode();

    // NVS
    int32_t restart_counter = 0; // value will default to 0, if not set yet in NVS
    static void nvs_init();

    // Grove I2C test
    static void grove_i2c_test();

    void app_main(void)
    {
        nvs_init();
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        printf("app main start\r\n");

        // gpio_hold_dis((gpio_num_t)CONFIG_NSS_GPIO);

        print_chip_info();

        c6_global_irq_init();
        
        // grove i2c test
        // grove_i2c_test();

        i2c_config_t conf;
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = SYS_I2C_SDA;
        conf.scl_io_num = SYS_I2C_SCL;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = 400000;
        conf.clk_flags = 0;
        i2c_bus = i2c_bus_create(I2C_NUM_0, &conf);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
        uint8_t i2c_addr[128] = {0};
        i2c_bus_scan(i2c_bus, i2c_addr, 0);
        for (int i = 0; i < 128; i++) 
        {
            if (i2c_addr[i] != 0) 
            {
                printf("i2c_addr[%d] = 0x%02x\n", i, i2c_addr[i]);
            }
        }

        // 震动电机
        motor_init();

        // IO扩展
        pi4io_init();
        pi4io_speaker_enable();

        // 充电管理
        aw32001_init();
        aw32001_charge_set(true);

        // 电量计
        bq27220_init();
        bq27220_exit_sealed();
        bq27220_full_access();
        bq27220_enter_cfg_update();

        // IMU
        bmi270_dev_init();

        // ES8311 初始化
        es8311_codec_init();

        // 触摸
        cst9217_init();

        // LCD
        lcd_init();

        // c6_enter_light_sleep_mode();
        // c6_enter_deep_sleep_mode();
        
        // 分配音频缓冲区
        uint8_t* audio_buffer = (uint8_t*)malloc(10240);


        {
            // 保持编解码器常开
            esp_codec_dev_sample_info_t fs = {
                .bits_per_sample = 16,
                .channel = 2,
                .sample_rate = 16000,
            };
            esp_codec_dev_open(codec_dev, &fs);
            // 生成1kHz正弦波
            const int samples = 1024;
            int16_t *wave = (int16_t *)malloc(samples * sizeof(int16_t));
            for (int i = 0; i < samples; i++) {
                wave[i] = 32767 * sin(2 * M_PI * 1000 * i / 16000);
            }
            
            for (int i = 0; i < 3; i++) {
                esp_codec_dev_write(codec_dev, (uint8_t *)wave, samples * sizeof(int16_t));
            }
            free(wave);
        }

        
        while (1)
        {
            // 按键读取
            // button_update();

            if (esp_timer_get_time() - last_blink_time > 3000000)
            {
                last_blink_time = esp_timer_get_time();
                led_blink = !led_blink;
                // pi4io_led_set_level(led_blink);
                // pi4io_ext_power_control(led_blink);
                aw32001_check_status();
                bmi270_dev_update();
                bq27220_read_voltage();
                bq27220_read_current();
                uint8_t vin_det = pi4io_vin_detect();
                printf("vin_det = %d\n", vin_det);
                printf("\r\n");

                

                // motor_enable();
                vTaskDelay(100 / portTICK_PERIOD_MS);
                // motor_disable();
            }

            // 按键
            if (btn1)
            {
                btn1 = false;
                printf("btn1 pressed\n");
                

                // 设置增益和音量
                esp_codec_dev_set_in_gain(codec_dev, 50.0); // 提高麦克风增益
                esp_codec_dev_set_out_vol(codec_dev, 80.0); // 提高音量

                // 录音3秒
                uint32_t start = esp_timer_get_time();
                size_t total_read = 0;
                while ((esp_timer_get_time() - start) < 3000000) {
                    esp_err_t ret = esp_codec_dev_read(codec_dev, audio_buffer, 10240);
                    if (ret == ESP_OK) {
                        total_read += 10240;
                        break;
                    }
                }
                printf("Recorded %d bytes\n", total_read);

                // 回放录音
                size_t remain = total_read;
                uint8_t *play_ptr = audio_buffer;
                while (remain > 0) {
                    size_t write_size = (remain > 1024) ? 1024 : remain;
                    esp_codec_dev_write(codec_dev, play_ptr, write_size);
                    play_ptr += write_size;
                    remain -= write_size;
                }
            } else if (btn2)
            {
                btn2 = false;
                printf("btn2 pressed\n");
            }

            if (touch_irq_flag)
            {
                BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                
                // 处理触摸数据
                cst9217_update();
                
                // 处理完成后重新启用中断
                touch_irq_flag = false;
                gpio_intr_enable(TP_INT_IRQ_PIN);
                
                // 可选：如果使用FreeRTOS API需要从ISR调用
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }

            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        
        free(audio_buffer);
    }

    /******************************************************************************/
    static void print_chip_info()
    {
        /* Print chip information */
        esp_chip_info_t chip_info;
        uint32_t flash_size;
        esp_chip_info(&chip_info);
        printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
               CONFIG_IDF_TARGET,
               chip_info.cores,
               (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
               (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
               (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
               (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

        unsigned major_rev = chip_info.revision / 100;
        unsigned minor_rev = chip_info.revision % 100;
        printf("silicon revision v%d.%d, ", major_rev, minor_rev);
        if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
        {
            printf("Get flash size failed");
            return;
        }

        printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
               (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

        printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());
    }

    /******************************************************************************/
    static bool c6_global_irq_init()
    {
        printf("c6_global_irq_init\n");
        gpio_config_t io_conf;
        io_conf.intr_type = GPIO_INTR_ANYEDGE;
        io_conf.mode = GPIO_MODE_INPUT;
        io_conf.pin_bit_mask = (1 << USER_BUTTON1_PIN) | (1 << USER_BUTTON2_PIN) | (1 << TP_INT_IRQ_PIN) /* | 1 << IMU_IRQ_PIN*/;
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
        gpio_config(&io_conf);
        gpio_install_isr_service(0);
        gpio_isr_handler_add(USER_BUTTON1_PIN, c6_global_irq_handler, (void *)USER_BUTTON1_PIN);
        gpio_isr_handler_add(USER_BUTTON2_PIN, c6_global_irq_handler, (void *)USER_BUTTON2_PIN);
        gpio_isr_handler_add(TP_INT_IRQ_PIN, c6_global_irq_handler, (void *)TP_INT_IRQ_PIN);
        // gpio_isr_handler_add(IMU_IRQ_PIN, c6_global_irq_handler, (void *)IMU_IRQ_PIN);
        return true;
    }

    void IRAM_ATTR c6_global_irq_handler(void *arg)
    {
        if ((uint32_t)arg == TP_INT_IRQ_PIN)
        {
            touch_irq_flag = true;
        }
        else 
        if ((uint32_t)arg == USER_BUTTON1_PIN)
        {
            btn1 = true;
        }
        else 
        if ((uint32_t)arg == USER_BUTTON2_PIN)
        {
            btn2 = true;
        }
        // else if ((uint32_t)arg == IMU_IRQ_PIN)
        // {
        //     c6_lora_irq_flag = true;
        // }
    }
    
    /******************************************************************************/
    static void motor_init()
    {
        printf("motor_init\n");
        gpio_config_t io_conf;
        io_conf.intr_type = GPIO_INTR_DISABLE;
        io_conf.mode = GPIO_MODE_OUTPUT;
        io_conf.pin_bit_mask = (1 << MOTOR_ENABLE_PIN);
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
        gpio_config(&io_conf);
    }

    static void motor_enable()
    {
        gpio_set_level(MOTOR_ENABLE_PIN, 1);
    }

    static void motor_disable()
    {
        gpio_set_level(MOTOR_ENABLE_PIN, 0);
    }

    /******************************************************************************/
    static void pi4io_init()
    {
        pi4io_dev = i2c_bus_device_create(i2c_bus, PI4IO_ADDR, 400000);
        if (pi4io_dev == NULL)
        {
            printf("pi4io_dev create failed\n");
        }
        else
        {
            printf("pi4io_dev create success\n");
        }

        uint8_t in_data;
        // P0 TP_RST
        // P1 OLED_RST
        // P5 VIN_DET
        // P6 VOUT_EN
        // P7 SPK_EN
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_CHIP_RESET, 0xFF);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_read_byte(pi4io_dev, PI4IO_REG_CHIP_RESET, &in_data);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_IO_DIR, 0b11000011); // 0: input 1: output
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_H_IM, 0b00111000); // 使用到的引脚关闭High-Impedance
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_PULL_SEL, 0b11000111); // pull up/down select, 0 down, 1 up
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_PULL_EN, 0b11000111); // pull up/down enable, 0 disable, 1 enable
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_IN_DEF_STA, 0b00000000); // P0 P1 默认高电平, 按键按下触发中断
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_INT_MASK, 0b11111111); // P0 P1 中断使能 0 enable, 1 disable
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, 0b11000011); // 默认输出为0
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    static void pi4io_release_all()
    {
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_H_IM, 0xFF);
    }

    static void pi4io_lcd_reset()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
        clrbit(in_data, 1); // LOW
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        setbit(in_data, 1); // HIGH
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    static void pi4io_tp_reset()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
        clrbit(in_data, 0);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        setbit(in_data, 0);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    static void pi4io_speaker_enable()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
        setbit(in_data, 7);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
    }

    static void pi4io_speaker_disable()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
        clrbit(in_data, 7);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
    }

    static uint8_t pi4io_vin_detect()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_dev, PI4IO_REG_IN_STA, &in_data);
        return getbit(in_data, 5);
    }

    static void pi4io_5V_out_enable()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
        setbit(in_data, 6);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
    }

    static void pi4io_5V_out_disable()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_dev, PI4IO_REG_OUT_SET, &in_data);
        clrbit(in_data, 6);
        i2c_bus_write_byte(pi4io_dev, PI4IO_REG_OUT_SET, in_data);
    }

    /******************************************************************************/
    static esp_err_t bq27220_i2c_read(uint8_t reg_addr, uint16_t sub_reg, uint16_t *reg_data)
    {
        uint8_t rbuf[2] = {0};
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (BQ27220_ADDR << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(cmd, reg_addr, true);
        i2c_master_write_byte(cmd, (sub_reg >> 8) & 0xFF, true);
        i2c_master_write_byte(cmd, sub_reg & 0xFF, true);
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (BQ27220_ADDR << 1) | I2C_MASTER_READ, true);
        i2c_master_read_byte(cmd, &rbuf[0], I2C_MASTER_ACK);
        i2c_master_read_byte(cmd, &rbuf[1], I2C_MASTER_NACK);
        i2c_master_stop(cmd);
        esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(cmd);

        printf("bq27220_i2c_read rbuf: %02X %02X\n", rbuf[0], rbuf[1]);
        *reg_data = (rbuf[1] << 8) | rbuf[0];
        return ret;
    }

    static void bq27220_init()
    {
        bq27220_dev = i2c_bus_device_create(i2c_bus, BQ27220_ADDR, 400000);
        if (bq27220_dev == NULL)
        {
            printf("bq27220_dev create failed\n");
        }
        else
        {
            printf("bq27220_dev create success\n");
        }
    }

    static void bq27220_exit_sealed()
    {
        // SEALED => UNSEAL
        i2c_bus_write_byte(bq27220_dev, 0x00, 0x80);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x00, 0x80);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    static void bq27220_enter_seal()
    {
        // UNSEAL => SEALED
        i2c_bus_write_byte(bq27220_dev, 0x00, 0x30);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    // 0x9206
    static void bq27220_enter_sleep_mode()
    {
        uint16_t data;
        i2c_bus_read_reg16(bq27220_dev, 0x9206, 2, (uint8_t *)&data);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        printf("BQ27 0x9206: %x\n", data);
        i2c_bus_read_reg16(bq27220_dev, 0x9207, 2, (uint8_t *)&data);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        printf("BQ27 0x9207: %x\n", data);
    }

    static void bq27220_full_access()
    {
        printf("bq27220_full_access\n");
        i2c_bus_write_byte(bq27220_dev, 0x00, 0xFF);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x01, 0xFF);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x00, 0xFF);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x01, 0xFF);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    static bool bq27220_opration_status_check()
    {
        uint16_t data;
        i2c_bus_read_bytes(bq27220_dev, 0x3A, 2, (uint8_t *)&data);
        if ((data & 0b010) == 0b010)
        {
            printf("Opration Status [full access]: 0x%04X\n", data);
            return true;
        }
        printf("Opration Status: 0x%04X\n", data);
        return false;
    }

    // 需要full access
    static void bq27220_enter_cfg_update()
    {
        printf("bq27220_enter_cfg_update\n");
        i2c_bus_write_byte(bq27220_dev, 0x00, 0x90);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
        vTaskDelay(10 / portTICK_PERIOD_MS);

        uint16_t data;
        while (1)
        {
            i2c_bus_read_bytes(bq27220_dev, 0x3A, 2, (uint8_t *)&data);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            if (getbit(data, 10))
            {
                printf("Opration Status [CFGUPDATE mode]: 0x%04X\n", data);
                break;
            }
            else
            {
                printf("Opration Status: 0x%04X\n", data);
            }
        }
    }

    static void bq27220_opration_config_A()
    {
        uint16_t wdata = 0x9206;
        uint16_t rdata;
        i2c_bus_write_reg16(bq27220_dev, 0x3E, 2, (uint8_t *)&wdata);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_read_bytes(bq27220_dev, 0x60, 1, (uint8_t *)&rdata);
        printf("Opration Config A check sum: 0x%02x\n", rdata);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_read_bytes(bq27220_dev, 0x61, 1, (uint8_t *)&rdata);
        printf("Opration Config A data len sum: 0x%02x\n", rdata);
        i2c_bus_read_bytes(bq27220_dev, 0x40, 2, (uint8_t *)&rdata);
        printf("Opration Config A: 0x%04X\n", rdata);
    }

    static void bq27220_opration_config_B()
    {
        uint8_t data[4];
        i2c_bus_write_byte(bq27220_dev, 0x3E, 0x08);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x3F, 0x92);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_read_bytes(bq27220_dev, 0x60, 1, data);
        printf("Opration Config B check sum: 0x%02x\n", data[0]);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_read_bytes(bq27220_dev, 0x61, 1, data);
        printf("Opration Config B data len sum: 0x%02x\n", data[0]);
        i2c_bus_read_bytes(bq27220_dev, 0x40, 2, data);
        printf("Opration Config B: 0x%02x 0x%02x\n", data[0], data[1]);
    }

    static void bq27220_read_design_capacity()
    {
        uint16_t data;
        i2c_bus_read_bytes(bq27220_dev, 0x3C, 2, (uint8_t *)&data);
        printf("design capacity: %dmV\n", data);
    }

    static uint16_t bq27220_read_voltage()
    {
        uint16_t voltage;
        i2c_bus_read_bytes(bq27220_dev, 0x08, 2, (uint8_t *)&voltage);
        printf("voltage: %dmv\n", voltage);
        return voltage;
    }

    static uint16_t bq27220_read_current()
    {
        uint16_t current;
        i2c_bus_read_bytes(bq27220_dev, 0x14, 2, (uint8_t *)&current);
        printf("current: %dma\n", current);
        return current;
    }

    static void bq27220_read_dev_number()
    {
        uint8_t data[4];
        i2c_bus_write_byte(bq27220_dev, 0x00, 0x01);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(bq27220_dev, 0x01, 0x00);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_read_bytes(bq27220_dev, 0x3E, 4, data);
        printf("Device Number: 0x%02x 0x%02x 0x%02x 0x%02x\n", data[0], data[1], data[2], data[3]);
    }

    /******************************************************************************/
    static void aw32001_init()
    {
        aw32001_dev = i2c_bus_device_create(i2c_bus, AW32001_ADDR, 400000);
        if (aw32001_dev == NULL)
        {
            printf("aw32001_dev create failed\n");
        }
        else
        {
            printf("aw32001_dev create success\n");
        }

        uint8_t rbuf;
        i2c_bus_read_byte(aw32001_dev, 0x02, &rbuf);
        printf("aw32001 charger current: %dma\n", (rbuf & 0b111111) * 8);
        i2c_bus_read_byte(aw32001_dev, 0x04, &rbuf);
        printf("aw32001 charger voltage: %dmv\n", (rbuf >> 2) * 15 + 3600);
        i2c_bus_write_byte(aw32001_dev, 0x00, 0b00001111);
        // i2c_bus_read_byte(aw32001_dev, 0x00, &rbuf);
        i2c_bus_write_byte(aw32001_dev, 0x05, 0b00000110);
        // i2c_bus_read_byte(aw32001_dev, 0x05, &rbuf);
    }

    static void aw32001_check_status()
    {
        uint8_t in_data;
        i2c_bus_read_byte(aw32001_dev, AW32001_REG_SYS_STA, &in_data);
        // B4-B3 00: NOT CHARGING 01: PRE CHARGING 10: CHARGING 11: CHARGING DONE
        // 判断充电状态, 通过Bit4 Bit3
        if ((in_data & 0b00011000) == 0b00011000)
        {
            printf("bat charging done\n");
        }
        else if ((in_data & 0b00011000) == 0b00010000)
        {
            printf("bat charging\n");
        }
        else if ((in_data & 0b00011000) == 0b00001000)
        {
            printf("bat pre charging\n");
        }
        else
        {
            printf("bat not charging\n");
        }
    }

    static void aw32001_charge_set(bool en)
    {
        uint8_t in_data;
        i2c_bus_read_byte(aw32001_dev, AW32001_REG_PWR_CFG, &in_data);
        if (en)
        {
            clrbit(in_data, 3); // 0 enable
        }
        else
        {
            setbit(in_data, 3); // 1 disable
        }
        i2c_bus_write_byte(aw32001_dev, AW32001_REG_PWR_CFG, in_data);
    }

    /******************************************************************************/
    static int8_t bmi2_i2c_read(uint8_t reg_addr, uint8_t *reg_data,
                                uint32_t len, void *intf_ptr)
    {
        if ((reg_data == NULL) || (len == 0) || (len > 32))
        {
            return -1;
        }
        i2c_bus_read_bytes(bmi270_dev, reg_addr, len, reg_data);
        return 0;
    }
    static int8_t bmi2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data,
                                 uint32_t len, void *intf_ptr)
    {
        if ((reg_data == NULL) || (len == 0) || (len > 32))
        {
            return -1;
        }
        i2c_bus_write_bytes(bmi270_dev, reg_addr, len, reg_data);
        return 0;
    }
    static void bmi2_delay_us(uint32_t period, void *intf_ptr)
    {
        uint64_t m = (uint64_t)esp_timer_get_time();
        if (period)
        {
            uint64_t e = (m + period);
            if (m > e)
            { // overflow
                while ((uint64_t)esp_timer_get_time() > e)
                {
                    asm volatile("nop");
                }
            }
            while ((uint64_t)esp_timer_get_time() < e)
            {
                asm volatile("nop");
            }
        }
    }

    static void bmi270_dev_init()
    {
        bmi270_dev = i2c_bus_device_create(i2c_bus, BMI270_ADDR, 400000);
        if (bmi270_dev == NULL)
        {
            printf("bmi270_dev create failed\n");
        }
        else
        {
            printf("bmi270_dev create success\n");
        }

        config[ACCEL].type = BMI2_ACCEL;
        config[GYRO].type = BMI2_GYRO;

        /* To enable the i2c interface settings for bmi270. */
        aux_bmi2_dev.intf = BMI2_I2C_INTF;
        aux_bmi2_dev.read = bmi2_i2c_read;
        aux_bmi2_dev.write = bmi2_i2c_write;
        aux_bmi2_dev.delay_us = bmi2_delay_us;
        aux_bmi2_dev.read_write_len = 30;
        aux_bmi2_dev.config_file_ptr = NULL;
        // aux_bmi2_dev.intf_ptr        = (void *)BMI270_ADDR;

        /* Initialize bmi270. */
        bmi270_init(&aux_bmi2_dev);

        /* Get default configurations for the type of feature selected. */
        bmi270_get_sensor_config(config, 2, &aux_bmi2_dev);

        /* Configurations for accel. */
        config[ACCEL].cfg.acc.filter_perf = BMI2_PERF_OPT_MODE;
        config[ACCEL].cfg.acc.bwp = BMI2_ACC_OSR2_AVG2;
        config[ACCEL].cfg.acc.odr = BMI2_ACC_ODR_100HZ;
        config[ACCEL].cfg.acc.range = BMI2_ACC_RANGE_2G;

        /* Configurations for gyro. */
        config[GYRO].cfg.gyr.filter_perf = BMI2_PERF_OPT_MODE;
        config[GYRO].cfg.gyr.noise_perf = BMI2_GYR_RANGE_2000;
        config[GYRO].cfg.gyr.bwp = BMI2_GYR_OSR2_MODE;
        config[GYRO].cfg.gyr.odr = BMI2_GYR_ODR_100HZ;
        config[GYRO].cfg.gyr.range = BMI2_GYR_RANGE_2000;
        config[GYRO].cfg.gyr.ois_range = BMI2_GYR_OIS_2000;

        /* Set new configurations for accel, gyro and aux. */
        bmi270_set_sensor_config(config, 2, &aux_bmi2_dev);

        /* NOTE:
         * Accel and gyro enable must be done after setting configurations
         */
        bmi270_sensor_enable(sensor_list, 2, &aux_bmi2_dev);

        bmi270_get_sensor_config(config, 2, &aux_bmi2_dev);

        /* Set the aux configurations. */
        bmi270_set_sensor_config(config, 2, &aux_bmi2_dev);

        /* Map data ready interrupt to interrupt pin. */
        bmi2_map_data_int(BMI2_DRDY_INT, BMI2_INT1, &aux_bmi2_dev);
    }

    static void bmi270_dev_update()
    {
        bmi2_get_sensor_data(&bmi_sensor_data, &aux_bmi2_dev);
        printf("Accel: x: %d, y: %d, z: %d\n", bmi_sensor_data.acc.x, bmi_sensor_data.acc.y, bmi_sensor_data.acc.z);
        printf("Gyro: x: %d, y: %d, z: %d\n", bmi_sensor_data.gyr.x, bmi_sensor_data.gyr.y, bmi_sensor_data.gyr.z);
    }

    /******************************************************************************/
    // ES8311 初始化函数
    static void es8311_codec_init() 
    {
        // i2c
        es8311_dev = i2c_bus_device_create(i2c_bus, ES8311_ADDR, 400000);
        if (es8311_dev == NULL)
        {
            printf("es8311_dev create failed\n");
        }
        else
        {
            printf("es8311_dev create success\n");
        }
        // i2s
        if (i2s_keep[0]) {
            return ;
        }
        i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
        i2s_std_config_t std_cfg =
        {
            .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000),
            .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG((i2s_data_bit_width_t)16, I2S_SLOT_MODE_STEREO),
            .gpio_cfg =
            {
                .mclk = I2S_MCLK_PIN,
                .bclk = I2S_BCLK_PIN,
                .ws = I2S_LRCK_PIN,
                .dout = I2S_DADC_PIN,
                .din = I2S_DDAT_PIN,
            },
        };
        i2s_keep[0] = (i2s_keep_t *) calloc(1, sizeof(i2s_keep_t));
        if (i2s_keep[0] == NULL) {
            return;
        }
        i2s_tdm_slot_mask_t slot_mask = (i2s_tdm_slot_mask_t)(I2S_TDM_SLOT0 | I2S_TDM_SLOT1 | I2S_TDM_SLOT2 | I2S_TDM_SLOT3);
        i2s_tdm_config_t tdm_cfg = 
        {
            .clk_cfg  = I2S_TDM_CLK_DEFAULT_CONFIG(16000),
            .slot_cfg = I2S_TDM_PHILIPS_SLOT_DEFAULT_CONFIG((i2s_data_bit_width_t)16, I2S_SLOT_MODE_STEREO, slot_mask),
            .gpio_cfg = {
                .mclk = I2S_MCLK_PIN,
                .bclk = I2S_BCLK_PIN,
                .ws = I2S_LRCK_PIN,
                .dout = I2S_DADC_PIN,
                .din = I2S_DDAT_PIN,
            },
        };
        tdm_cfg.slot_cfg.total_slot = 4;
        int ret = i2s_new_channel(&chan_cfg, &i2s_keep[0]->tx_handle, &i2s_keep[0]->rx_handle);
        if (i2s_out_mode == I2S_COMM_MODE_STD)
        {
            ret = i2s_channel_init_std_mode(i2s_keep[0]->tx_handle, &std_cfg);
        }
        else 
        if (i2s_out_mode == I2S_COMM_MODE_TDM) 
        {
        ret = i2s_channel_init_tdm_mode(i2s_keep[0]->tx_handle, &tdm_cfg);
        }
        if (i2s_in_mode == I2S_COMM_MODE_STD)
        {
            ret = i2s_channel_init_std_mode(i2s_keep[0]->rx_handle, &std_cfg);
        } 
        else 
        if (i2s_in_mode == I2S_COMM_MODE_TDM)
        {
            ret = i2s_channel_init_tdm_mode(i2s_keep[0]->rx_handle, &tdm_cfg);
        }
        i2s_channel_enable(i2s_keep[0]->tx_handle);

        // codec
        audio_codec_i2s_cfg_t i2s_cfg = {
            .rx_handle = i2s_keep[0]->rx_handle,
            .tx_handle = i2s_keep[0]->tx_handle,
        };
        const audio_codec_data_if_t *data_if = audio_codec_new_i2s_data(&i2s_cfg);

        audio_codec_i2c_cfg_t i2c_cfg = 
        {
            .port = I2C_NUM_0,
            .addr = ES8311_ADDR,
        };
        const audio_codec_ctrl_if_t *out_ctrl_if = audio_codec_new_i2c_ctrl(&i2c_cfg);
        
        const audio_codec_gpio_if_t *gpio_if = audio_codec_new_gpio();
        // New output codec interface
        es8311_codec_cfg_t es8311_cfg = 
        {
            .ctrl_if = out_ctrl_if,
            .gpio_if = gpio_if,
            .codec_mode = ESP_CODEC_DEV_WORK_MODE_DAC,
            .pa_pin = EXT_GPIO3_PIN,
            .use_mclk = true,
        };
        const audio_codec_if_t *out_codec_if = es8311_codec_new(&es8311_cfg);
        // New output codec device
        esp_codec_dev_cfg_t dev_cfg = 
        {
            .dev_type = ESP_CODEC_DEV_TYPE_IN_OUT, // 设备同时支持录制和播放
            .codec_if = out_codec_if,              // es8311_codec_new 获取到的接口实现
            .data_if = data_if,                    // audio_codec_new_i2s_data 获取到的数据接口实现
        };
        codec_dev = esp_codec_dev_new(&dev_cfg);
    }

    // 添加录音函数
    static esp_err_t record_audio(uint8_t* data, size_t size) 
    {
        return esp_codec_dev_read(codec_dev, data, size);
    }

    // 添加播放函数
    static esp_err_t play_audio(const uint8_t* data, size_t size) 
    {
        return esp_codec_dev_write(codec_dev, (void *)data, size);
    }


    /******************************************************************************/
    static uint32_t partno_chip_type; // 芯片类型
    static uint32_t module_id; // 模块ID
    static uint8_t work_mode; // 工作模式
    // CST9217 初始化函数
    static void cst9217_init()
    {
        cst9217_dev = i2c_bus_device_create(i2c_bus, CST9217_ADDR, 400000);
        if (cst9217_dev == NULL)
        {
            printf("cst9217_dev create failed\n");
        }
        else
        {
            printf("cst9217_dev create success\n");
        }
        cst9217_read_chip_id();

        cst9217_read_tpinfo();
    }

    static void cst9217_update()
    {
        uint8_t i2c_buf[MAX_POINTS_REPORT*5+5] = {0};
        uint8_t finger_num = 0;

        // 读取触摸数据
        if (i2c_bus_read_reg(cst9217_dev, 0xD000, 2, i2c_buf, sizeof(i2c_buf)) != ESP_OK) {
            printf("Failed to read touch data\n");
            return;
        }

        // 验证数据有效性
        if (i2c_buf[6] != 0xAB) {
            printf("Invalid touch data header\n");
            return;
        }

        finger_num = i2c_buf[5] & 0x7F;
        if (finger_num > MAX_POINTS_REPORT) {
            printf("Exceed max finger count: %d\n", finger_num);
            return;
        }

        printf("Detected fingers: %d\n", finger_num);

        // 清空之前的触摸数据
        memset(tp_info, 0, sizeof(tp_info));

        // 解析每个触摸点
        for (int i = 0; i < finger_num; i++) {
            uint8_t *data = (i == 0) ? i2c_buf : i2c_buf + 5*i + 2;
            
            if (data >= i2c_buf + sizeof(i2c_buf)) {
                printf("Data overflow detected\n");
                break;
            }

            tp_info[i].id = data[0] >> 4;
            tp_info[i].switch_ = data[0] & 0x0F;
            tp_info[i].x = ((uint16_t)(data[1]) << 4) | (data[3] >> 4);
            tp_info[i].y = ((uint16_t)(data[2]) << 4) | (data[3] & 0x0F);
            tp_info[i].z = (data[3] & 0x1F) + 0x03;

            printf("Finger %d: ID=%d X=%d Y=%d Z=%d\n", 
                  i+1, tp_info[i].id, tp_info[i].x, tp_info[i].y, tp_info[i].z);
        }

        // 发送触摸事件到LVGL
        // if (xSemaphoreTake(touch_mux, pdMS_TO_TICKS(100)) == pdTRUE) {
        //     esp_lcd_touch_read_data(tp);
        //     xSemaphoreGive(touch_mux);
        // }
    }

    static void cst9217_enter_bootloader()
    {
        uint8_t i2c_buf[4] = {0};
        for (int i = 10;; i+=2)
        {
            if (i >= 30)
            {
                printf("cst9217_enter_bootloader timeout\n");
                return;
            }
            pi4io_tp_reset();
            vTaskDelay(i / portTICK_PERIOD_MS);
            i2c_bus_write_reg(cst9217_dev, 0xA001AA, 3, i2c_buf, 0);
            vTaskDelay(1 / portTICK_PERIOD_MS);
            i2c_bus_read_reg(cst9217_dev, 0xA002, 2, i2c_buf, 2);
            vTaskDelay(1 / portTICK_PERIOD_MS);
            if(i2c_buf[0] == 0x55 && i2c_buf[1] == 0xB0)
            {
                printf("cst9217_enter_bootloader success\n");
                break;
            }
        }
        i2c_bus_write_reg(cst9217_dev, 0xA00100, 3, i2c_buf, 0);
    }

    static void cst9217_read_chip_id()
    {
        cst9217_enter_bootloader();
        for (int i = 0; i < 3; i++)
        {
            vTaskDelay(10 / portTICK_PERIOD_MS);
            cst9217_read_word_from_mem(1, 0x077C, &partno_chip_type);
            cst9217_read_word_from_mem(0, 0x7FC0, &module_id);
            if ((partno_chip_type >> 16) == 0xCACA)
            {
                printf("cst9217 read success\n");
                partno_chip_type &= 0xffff;
                break;
            }
            else
            {
                printf("cst9217 read failed, retry\n");
            }
        }
        pi4io_tp_reset();
        printf("partno_chip_type: 0x%lx\n", partno_chip_type);
        printf("module_id: 0x%lx\n", module_id);
        if ((partno_chip_type != 0x9217) && (partno_chip_type != 0x9220))
        {
            printf("partno_chip_type error 0x%lx\n", partno_chip_type);
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    
    static void cst9217_read_tpinfo()
    {
        uint8_t i2c_buf[30] = {0};

        // cst9217_set_workmode(0xff, 0);
        i2c_bus_write_reg(cst9217_dev, 0xD101, 2, i2c_buf, 0);
        vTaskDelay(5 / portTICK_PERIOD_MS);

        i2c_bus_read_reg(cst9217_dev, 0xD1F4, 2, i2c_buf, 28);
        printf("firmware_project_id: 0x%04x\n", i2c_buf[17] << 8 | i2c_buf[16]);
        printf("firmware_ic_type: 0x%04x\n", i2c_buf[19] << 8 | i2c_buf[18]);
        printf("firmware_version: 0x%04x\n", i2c_buf[23] << 24 | i2c_buf[22] << 16 | i2c_buf[21] << 8 | i2c_buf[20]);
        printf("tx_num: %d\n", i2c_buf[1]);
        printf("rx_num: %d\n", i2c_buf[2]);
        printf("key_num: %d\n", i2c_buf[3]);
        printf("res_x: %d\n", i2c_buf[5] << 8 | i2c_buf[4]);
        printf("res_y: %d\n", i2c_buf[7] << 8 | i2c_buf[6]);
        printf("fw_checksum: 0x%04x\n", i2c_buf[27] << 8 | i2c_buf[26]);
        
        cst9217_set_workmode(NOMAL_MODE, 1);
    }

    static void cst9217_set_workmode(enum work_mode mode, uint8_t enable)
    {
        uint8_t i2c_buf[4] = {0};
        work_mode = mode;
        if(mode != NOMAL_MODE)
        {
            printf("cst9217_set_workmode: %d\n", mode);
        }
        for(int i = 0; i < 3; i++)
        {
            i2c_bus_write_reg(cst9217_dev, 0xD11E, 2, i2c_buf, 0);
            vTaskDelay(5 / portTICK_PERIOD_MS);
            i2c_bus_write_reg(cst9217_dev, 0x0002, 2, i2c_buf, 2);
            if(i2c_buf[1] == 0x1E)
            {
                break;
            }
        }
        switch(mode)
        {
            case NOMAL_MODE:
                i2c_bus_write_reg(cst9217_dev, 0xD109, 2, i2c_buf, 0);
                break;
            case GESTURE_MODE:
                i2c_bus_write_reg(cst9217_dev, 0xD104, 2, i2c_buf, 0);
                break;
            case LP_MODE:
                i2c_bus_write_reg(cst9217_dev, 0xD107, 2, i2c_buf, 0);
                break;
            case DIFF_MODE:
                i2c_bus_write_reg(cst9217_dev, 0xD10D, 2, i2c_buf, 0);
                break;
            case RAWDATA_MODE:
                i2c_bus_write_reg(cst9217_dev, 0xD10A, 2, i2c_buf, 0);
                break;
            case BASELINE_MODE:
                i2c_bus_write_reg(cst9217_dev, 0xD108, 2, i2c_buf, 0);
                break;
            case CALIBRATE_MODE:
                i2c_bus_write_reg(cst9217_dev, 0xD10B, 2, i2c_buf, 0);
                break;
            case FAC_TEST_MODE:
                i2c_bus_write_reg(cst9217_dev, 0xD114, 2, i2c_buf, 0);
                break;
            case DEEPSLEEP:
                i2c_bus_write_reg(cst9217_dev, 0xD105, 2, i2c_buf, 0);
                break;
            default:
                printf("cst9217_set_workmode: %d\n", mode);
                mode = NOMAL_MODE;
                break;
        }
    }

    static void cst9217_read_word_from_mem(uint8_t type, uint16_t addr, uint32_t *value)
    {
        uint8_t i2c_buf[4] = {0};
        i2c_buf[0] = type;
        i2c_bus_write_reg(cst9217_dev, 0xA010, 2, i2c_buf, 1);

        i2c_buf[0] = addr;
        i2c_buf[1] = addr >> 8;
        i2c_bus_write_reg(cst9217_dev, 0xA00C, 2, i2c_buf, 2);

        i2c_buf[0] = 0xE4;
        i2c_bus_write_reg(cst9217_dev, 0xA004, 2, i2c_buf, 1);

        for(int i = 0;; i++)
        {
            if (i >= 100)
            {
                printf("cst9217_read_word_from_mem timeout\n");
                return;
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
            i2c_bus_read_reg(cst9217_dev, 0xA004, 2, i2c_buf, 1);
            if (i2c_buf[0] == 0x00)
            {
                break;
            }
        }
        i2c_bus_read_reg(cst9217_dev, 0xA018, 2, i2c_buf, 4);
        *value = (i2c_buf[0] << 24) | (i2c_buf[1] << 16) | (i2c_buf[2] << 8) | i2c_buf[3];
    }
    
    // static void cst9217_read_data(uint8_t *data, uint16_t len)
    // {
        
    // }

    // static void cst9217_write_data(uint8_t *data, uint8_t reg_len, uint16_t len)
    // {
    //     uint8_t cmd_len = reg_len&0x0F;
    //     if(cmd_len > 4) printf("cst9217_write cmd_len error: %d\n", cmd_len);
    //     uint8_t addr_buf[4] = {0};
    //     for(int i = 0; i < cmd_len; i++) 
    //     {
    //         addr_buf[cmd_len-1-i] = (cmd_len >> (i*8)) & 0xFF; // 大端存储地址
    //     }
    //     i2c_bus_write_reg(cst9217_dev, reg_addr, reg_len, data, len);
    // }

    // static void cst9217_wr_reg(uint32_t reg_addr, uint8_t reg_len, uint8_t *rbuf, uint16_t rlen)
    // {

    // }
    

    /******************************************************************************/
    static bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
    {
        lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
        lv_disp_flush_ready(disp_driver);
        return false;
    }
    
    static void example_touch_isr_cb(esp_lcd_touch_handle_t tp)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(touch_mux, &xHigherPriorityTaskWoken);

        if (xHigherPriorityTaskWoken) {
            portYIELD_FROM_ISR();
        }
    }
    
    static void example_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
    {
        esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
        const int offsetx1 = area->x1;
        const int offsetx2 = area->x2;
        const int offsety1 = area->y1;
        const int offsety2 = area->y2;

        // 将缓冲区的内容复制到显示的特定区域
        esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
    }

    static void example_lvgl_rounder_cb(struct _lv_disp_drv_t *disp_drv, lv_area_t *area)
    {
        uint16_t x1 = area->x1;
        uint16_t x2 = area->x2;
        uint16_t y1 = area->y1;
        uint16_t y2 = area->y2;

        // round the start of coordinate down to the nearest 2M number
        area->x1 = (x1 >> 1) << 1;
        area->y1 = (y1 >> 1) << 1;
        // round the end of coordinate up to the nearest 2N+1 number
        area->x2 = ((x2 >> 1) << 1) + 1;
        area->y2 = ((y2 >> 1) << 1) + 1;
        return;
    }

    /* 在 LVGL 中旋转屏幕时，旋转显示和触摸。 更新驱动程序参数时调用 */
    static void example_lvgl_update_cb(lv_disp_drv_t *drv)
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

    static void example_increase_lvgl_tick(void *arg)
    {
        /* 告诉 LVGL 已经过去了多少毫秒*/
        lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
    }

    static void example_lvgl_touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data)
    {
        esp_lcd_touch_handle_t tp = (esp_lcd_touch_handle_t)drv->user_data;
        assert(tp);

        uint16_t tp_x;
        uint16_t tp_y;
        uint8_t tp_cnt = 0;
        /* 将触摸控制器中的数据读取到内存中 */
        if (xSemaphoreTake(touch_mux, 0) == pdTRUE) {
            esp_lcd_touch_read_data(tp);
        }

        /* 从触摸控制器读取数据 */
        bool tp_pressed = esp_lcd_touch_get_coordinates(tp, &tp_x, &tp_y, NULL, &tp_cnt, 1);
        if (tp_pressed && tp_cnt > 0) {
            data->point.x = tp_x;
            data->point.y = tp_y;
            data->state = LV_INDEV_STATE_PRESSED;
            ESP_LOGD(TAG, "Touch position: %d,%d", tp_x, tp_y);
        } else {
            data->state = LV_INDEV_STATE_RELEASED;
        }
    }

    static bool example_lvgl_lock(int timeout_ms)
    {
        assert(lvgl_mux && "bsp_display_start must be called first");

        const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
        return xSemaphoreTake(lvgl_mux, timeout_ticks) == pdTRUE;
    }

    static void example_lvgl_unlock(void)
    {
        assert(lvgl_mux && "bsp_display_start must be called first");
        xSemaphoreGive(lvgl_mux);
    }

    static void lcd_init()
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
        esp_lcd_panel_io_handle_t io_handle = NULL;
        const esp_lcd_panel_io_spi_config_t io_config = CO5300_PANEL_IO_QSPI_CONFIG(QSPI_CS_PIN, example_notify_lvgl_flush_ready, &disp_drv);
        
        co5300_vendor_config_t vendor_config = {
            .flags = {
                .use_qspi_interface = 1,
            },
        };

        // 将 LCD 连接到 SPI 总线
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

        esp_lcd_panel_handle_t panel_handle = NULL;
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
        ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 16, 0));
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

        // ESP_LOGI(TAG, "Install CST9217 touch driver");
        // esp_lcd_panel_io_handle_t tp_io_handle = NULL;
        // const esp_lcd_panel_io_i2c_config_t tp_io_config = {
        //     .dev_addr = CST9217_ADDR,
        //     .control_phase_bytes = 1,
        //     .dc_bit_offset = 0,
        //     .lcd_cmd_bits = 8,
        //     .lcd_param_bits = 0,
        //     .flags = {
        //         .dc_low_on_data = 0,
        //         .disable_control_phase = 1,
        //     }
        // };

        // ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(TOUCH_HOST, &tp_io_config, &tp_io_handle));

        // touch_mux = xSemaphoreCreateBinary();
        // assert(touch_mux);

        // const esp_lcd_touch_config_t tp_cfg = {
        //     .x_max = EXAMPLE_LCD_H_RES,
        //     .y_max = EXAMPLE_LCD_V_RES,
        //     .rst_gpio_num = TOUCH_RST_PIN,
        //     .int_gpio_num = TOUCH_INT_PIN,
        //     .levels = {
        //         .reset = 0,
        //         .interrupt = 0,
        //     },
        //     .flags = {
        //         .swap_xy = 0,
        //         .mirror_x = 0,
        //         .mirror_y = 0,
        //     },
        //     .interrupt_callback = example_touch_isr_cb,
        // };

        // ESP_LOGI(TAG, "Initialize touch controller cst9217");
        // ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_cst9217(tp_io_handle, &tp_cfg, &tp));

        // ESP_LOGI(TAG, "Initialize touch controller cst9217");
        // ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_cst816s(tp_io_handle, &tp_cfg, &tp));

        ESP_LOGI(TAG, "Initialize LVGL library");
        lv_init();
        // 分配 LVGL 使用的绘制缓冲区, 建议选择绘制缓冲区的大小至少为屏幕大小的 1/10
        lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(EXAMPLE_LCD_H_RES * 50 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
        assert(buf1);
        lv_color_t *buf2 = (lv_color_t *)heap_caps_malloc(EXAMPLE_LCD_H_RES * 50 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
        assert(buf2);
        // 初始化 LVGL 绘制缓冲区
        lv_disp_draw_buf_init(&disp_buf, buf1, buf2, EXAMPLE_LCD_H_RES * 50 * sizeof(lv_color_t));

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

        // static lv_indev_drv_t indev_drv;    // 输入设备驱动程序（触摸）
        // lv_indev_drv_init(&indev_drv);
        // indev_drv.type = LV_INDEV_TYPE_POINTER;
        // indev_drv.disp = disp;
        // indev_drv.read_cb = example_lvgl_touch_cb;
        // indev_drv.user_data = tp;
        
        // lv_indev_drv_register(&indev_drv);

        lvgl_mux = xSemaphoreCreateMutex();
        assert(lvgl_mux);
        xTaskCreate(example_lvgl_port_task, "LVGL", EXAMPLE_LVGL_TASK_STACK_SIZE, NULL, EXAMPLE_LVGL_TASK_PRIORITY, NULL);

        ESP_LOGI(TAG, "Display LVGL demos");
        if (example_lvgl_lock(-1)) {
            // lv_demo_widgets();      /* 小部件示例 */
            // lv_demo_music();        /* 类似智能手机的现代音乐播放器演示 */
            // lv_demo_stress();       /* LVGL 压力测试 */
            // lv_demo_benchmark();    /* 用于测量 LVGL 性能或比较不同设置的演示 */
            ui_init();
            // 释放互斥锁
            example_lvgl_unlock();
        }
    }

    static void example_lvgl_port_task(void *arg)
    {
        ESP_LOGI(TAG, "Starting LVGL task");
        uint32_t task_delay_ms = EXAMPLE_LVGL_TASK_MAX_DELAY_MS;
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

    /******************************************************************************/
    // AW32001	Battery Mode
    // BQ27220	Sleep Mode
    // BMI270	Lowest Power Mode
    // PI4IO	BL off & LED off & EXT PWR off
    // LCD	    Sleep Mode
    // Touch	Sleep Mode?
    static void c6_enter_light_sleep_mode()
    {
        printf("c6_enter_light_sleep_mode\r\n");
        esp_light_sleep_start();
    }

    static void c6_enter_deep_sleep_mode()
    {
        printf("c6_enter_deep_sleep_mode\r\n");
        uint8_t in_data;
        // BQ27220 Reg 0x9206 Operation Config A

        // AW32001
        i2c_bus_read_byte(aw32001_dev, 0x01, &in_data);
        setbit(in_data, 3);
        i2c_bus_write_byte(aw32001_dev, 0x01, in_data);
        i2c_bus_read_byte(aw32001_dev, 0x01, &in_data);
        printf("AW32001 0x01 CEB: %d\n", getbit(in_data, 3));

        // BMI270
        i2c_bus_write_byte(bmi270_dev, 0x7C, 0x01);
        i2c_bus_write_byte(bmi270_dev, 0x7D, 0x00);

        // Check IRQ
        printf("IRQ G7 level: %d\n", gpio_get_level(TP_INT_IRQ_PIN));

        // PI4IO
        // i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, 0b10000000); // P7 HIGH

        vTaskDelay(100 / portTICK_PERIOD_MS);

        esp_deep_sleep_start();
    }

    static void nvs_init()
    {
        // Initialize NVS
        esp_err_t err = nvs_flash_init();
        if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            // NVS partition was truncated and needs to be erased
            // Retry nvs_flash_init
            ESP_ERROR_CHECK(nvs_flash_erase());
            err = nvs_flash_init();
        }
        ESP_ERROR_CHECK(err);

        nvs_handle_t my_handle;
        err = nvs_open("storage", NVS_READWRITE, &my_handle);
        if (err != ESP_OK)
        {
            printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
        }
        else
        {
            printf("Done\n");

            // Read
            printf("Reading restart counter from NVS ... ");
            err = nvs_get_i32(my_handle, "restart_counter", &restart_counter);
            switch (err)
            {
            case ESP_OK:
                printf("Done\n");
                printf("Restart counter = %" PRIu32 "\n", restart_counter);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The value is not initialized yet!\n");
                break;
            default:
                printf("Error (%s) reading!\n", esp_err_to_name(err));
            }

            // Write
            printf("Updating restart counter in NVS ... ");
            restart_counter++;
            err = nvs_set_i32(my_handle, "restart_counter", restart_counter);
            printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

            printf("Committing updates in NVS ... ");
            err = nvs_commit(my_handle);
            printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

            // Close
            nvs_close(my_handle);
        }
    }

    /******************************************************************************/
    static void grove_i2c_test() {
        printf("grove_i2c_test\n");
        i2c_config_t conf;
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = GROVE_3_PIN;
        conf.scl_io_num = GROVE_4_PIN;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = 400000;
        conf.clk_flags = 0;
        grove_i2c_bus = i2c_bus_create(I2C_NUM_1, &conf);

        vTaskDelay(1000 / portTICK_PERIOD_MS);

        printf("grove_i2c_test scan\n");
        uint8_t addr[128] = {0};
        i2c_bus_scan(grove_i2c_bus, addr, 0);
        for (int i = 0; i < 128; i++) 
        {
            if (addr[i] != 0) 
            {
                printf("grove found device at address 0x%02X\n", addr[i]);
            }
        }

        i2c_bus_delete(&grove_i2c_bus);
    }
}
