#include <M5GFX.h>
#include <lgfx/v1/panel/Panel_ST7789.hpp>
#include <lgfx/v1/touch/Touch_FT5x06.hpp>

// 管脚定义
#define C6_IRQ_PIN (gpio_num_t)3
#define LORA_IRQ_PIN (gpio_num_t)15
#define IR_TX_GPIO_NUM (gpio_num_t)9

#define I2C_0_SCL (gpio_num_t)8
#define I2C_0_SDA (gpio_num_t)10
#define I2C_DEV_TIMEOUT 4000000

#define LCD_CS_PIN (gpio_num_t)17
#define LCD_DC_PIN (gpio_num_t)16

#define BEEP_PIN (gpio_num_t)11

#define GROVE_OUT_PIN (gpio_num_t)5
#define GROVE_IN_PIN (gpio_num_t)4

#define HAT_PIN_1 (gpio_num_t)7
#define HAT_PIN_2 (gpio_num_t)2
#define HAT_PIN_3 (gpio_num_t)6

class Stick_Arduino_Lcd : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7789 _panel_instance;
    lgfx::Touch_FT5x06 _touch_instance;
    lgfx::Bus_SPI _bus_instance;

public:
    Stick_Arduino_Lcd(void)
    {
        {
            auto cfg = _bus_instance.config();

            cfg.pin_mosi = CONFIG_MOSI_GPIO;
            cfg.pin_miso = CONFIG_MISO_GPIO;
            cfg.pin_sclk = CONFIG_SCLK_GPIO;
            cfg.pin_dc = LCD_DC_PIN;
            cfg.freq_write = 40000000;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();

            cfg.invert = true;
            cfg.pin_cs = LCD_CS_PIN;
            cfg.pin_rst = -1;
            cfg.pin_busy = -1;
            cfg.panel_width = 135;
            cfg.panel_height = 240;
            cfg.offset_x = 52;
            cfg.offset_y = 40;

            _panel_instance.config(cfg);
        }

        {
            auto cfg = _touch_instance.config();

            cfg.x_min = 0;
            cfg.x_max = 135;
            cfg.y_min = 0;
            cfg.y_max = 240;
            cfg.pin_int = C6_IRQ_PIN;
            cfg.pin_rst = -1;
            cfg.bus_shared = true;
            cfg.offset_rotation = 0;

            cfg.i2c_port = 0;
            cfg.i2c_addr = 0x38;
            cfg.pin_sda = I2C_0_SDA;
            cfg.pin_scl = I2C_0_SCL;
            cfg.freq = 400000;

            _touch_instance.config(cfg);
            _panel_instance.setTouch(&_touch_instance);
        }

        setPanel(&_panel_instance);
    }
};

Stick_Arduino_Lcd Lcd;

extern "C"
{
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
#include "ra01s.h"

#define TAG "main"

// bit operation
#define setbit(x, y) x |= (0x01 << y)
#define clrbit(x, y) x &= ~(0x01 << y)
#define reversebit(x, y) x ^= (0x01 << y)
#define getbit(x, y) ((x) >> (y) & 0x01)

// I2C device addr
#define PI4IO_M_ADDR 0x43
#define PI4IO_B_ADDR 0x44
#define BMI270_ADDR 0x68
#define BQ27220_ADDR 0x55
#define AW32001_ADDR 0x49

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

    static void print_chip_info();

    i2c_bus_handle_t i2c_bus = NULL;

    static bool volatile c6_irq_flag = false;
    static bool volatile c6_lora_irq_flag = false;
    static bool c6_global_irq_init();
    void IRAM_ATTR c6_global_irq_handler(void *arg);

    // PI4IO
    i2c_bus_device_handle_t pi4io_m_dev = NULL;
    i2c_bus_device_handle_t pi4io_b_dev = NULL;
    static bool led_blink = false;
    static uint64_t last_blink_time = 0;
    static bool btn1, btn2 = false;
    static void pi4io_init();
    static void pi4io_led_set_level(bool level);
    static void pi4io_lcd_bl_set_level(bool level);
    static bool pi4io_vin_has_input();
    static void pi4io_ext_power_control(bool en);
    static void pi4io_power_off();
    static void pi4io_check_irq();
    static void button_update();
    static void lcd_reset();

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

// IR
    static uint16_t ir_addr = 0x5555;
    static uint16_t ir_cmd = 0x00;
    extern void ir_tx_init();
    extern void ir_tx_trans(uint16_t addr, uint16_t cmd);

// Beep
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          BEEP_PIN // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4096) // Set duty to 50%. (2 ** 13) * 50% = 4096
#define LEDC_FREQUENCY          (2000) // Frequency in Hertz. Set frequency at 2 kHz
    static void beep_init();
    static void beep_on();
    static void beep_off();

// LoRa SX1262
// carrier frequency:           915.0 MHz
// bandwidth:                   500 kHz
// spreading factor:            7
// coding rate:                 5
// sync word:                   0x34 (public network/LoRaWAN)
// output power:                22 dBm
// preamble length:             20 symbols
#define LORA_SEND 0
#define LORA_BW 125.0f
#define LORA_SF 12
#define LORA_CR 8
// #define LORA_BW 500
// #define LORA_SF 7
// #define LORA_CR 5

#define LORA_FREQ 915000000
// #define LORA_FREQ 868000000
#define LORA_SYNC_WORD 0x34
#define LORA_TX_POWER 22
#define LORA_PREAMBLE_LEN 20

    static void sx1262_init();
    static void sx1262_reset();
    static void sx1262_rf_turn_on();
    static void sx1262_rf_turn_off();
    static void sx1262_tx_test();
    static void sx1262_rx_test();

    // LCD
    uint8_t idx = 0;
    uint32_t color[5] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_WHITE, TFT_BLACK};
    uint64_t last_touch = 0;
    extern const unsigned char mesh_stick_green[7456];
    extern const unsigned char mesh_stick_pink[7450];

    // sleep mode test
    static void c6_enter_light_sleep_mode();
    static void c6_enter_deep_sleep_mode();

    // NVS
    int32_t restart_counter = 0; // value will default to 0, if not set yet in NVS
    static void nvs_init();

    // Grove I2C test
    static void grvoe_i2c_test();

    // HAT GPIO Blink test
    static bool hat_gpio_flag = false;
    static void hat_gpio_init();
    static void hat_gpio_blink();

    void app_main(void)
    {
        nvs_init();
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        printf("app main start\r\n");

        gpio_hold_dis((gpio_num_t)CONFIG_NSS_GPIO);

        print_chip_info();

        c6_global_irq_init();
        hat_gpio_init();

        i2c_config_t conf;
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = I2C_0_SDA;
        conf.scl_io_num = I2C_0_SCL;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = 400000;
        conf.clk_flags = 0;
        i2c_bus = i2c_bus_create(I2C_NUM_0, &conf);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
        i2c_bus_scan(i2c_bus, NULL, 0);

        // IO扩展
        pi4io_init();
        pi4io_ext_power_control(true);

        // 默认注释掉, 里面死循环
        // grvoe_i2c_test();

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

        // 红外发射
        ir_tx_init();

        // 蜂鸣器
        beep_init();

        // LoRa
        sx1262_init();

        // LCD
        lcd_reset();
        pi4io_lcd_bl_set_level(true);
        Lcd.begin();
        Lcd.drawPng(mesh_stick_pink, sizeof(mesh_stick_pink), 0, 0);

        // c6_enter_light_sleep_mode();
        // c6_enter_deep_sleep_mode();

        while (1)
        {
            // 按键读取
            button_update();

            if (esp_timer_get_time() - last_blink_time > 3000000)
            {
                hat_gpio_blink();
                last_blink_time = esp_timer_get_time();
                led_blink = !led_blink;
                pi4io_led_set_level(led_blink);
                pi4io_ext_power_control(led_blink);
                aw32001_check_status();
                bmi270_dev_update();
                bq27220_read_voltage();
                bq27220_read_current();
                // printf("\r\n");

                ir_tx_trans(ir_addr, ir_cmd);
                ir_cmd++;
                beep_on();
                vTaskDelay(100 / portTICK_PERIOD_MS);
                beep_off();
            }

            // 触摸
            m5gfx::touch_point_t tp[2];
            int nums = Lcd.getTouch(tp, 2);
            for (int i = 0; i < nums; ++i)
            {
                Lcd.fillCircle(tp[i].x, tp[i].y, 3, rand());
            }

            // 清屏
            if ((esp_timer_get_time() - last_touch) > 15000000)
            {
                last_touch = esp_timer_get_time();
                idx = (idx + 1) % 5;
                Lcd.clear(color[idx]);
                Lcd.drawRect(0, 0, 135, 240, TFT_WHITE);
                char buf[32] = {0};
                sprintf(buf, "Reset Count: %ld", restart_counter);
                Lcd.drawCenterString(buf, 67, 120);

                sx1262_tx_test();
            }

            // 按键
            if (btn1)
            {
                btn1 = false;
                // Lcd.drawPng(mesh_stick_pink, sizeof(mesh_stick_pink), 0, 0);
                Lcd.clear(TFT_BLACK);
            } else if (btn2)
            {
                btn2 = false;
                // Lcd.drawPng(mesh_stick_green, sizeof(mesh_stick_green), 0, 0);
                Lcd.clear(TFT_WHITE);
            }

            // LoRa 接收?
            // if (c6_lora_irq_flag) {
            //     c6_lora_irq_flag = false;
            //     printf("c6_lora_irq_flag\n");
                sx1262_rx_test();
            // }

            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
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
        io_conf.pin_bit_mask = 1 << C6_IRQ_PIN | 1 << LORA_IRQ_PIN;
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
        gpio_config(&io_conf);
        gpio_install_isr_service(0);
        gpio_isr_handler_add(C6_IRQ_PIN, c6_global_irq_handler, (void *)C6_IRQ_PIN);
        gpio_isr_handler_add(LORA_IRQ_PIN, c6_global_irq_handler, (void *)LORA_IRQ_PIN);
        return true;
    }

    void IRAM_ATTR c6_global_irq_handler(void *arg)
    {
        if ((uint32_t)arg == C6_IRQ_PIN)
        {
            c6_irq_flag = true;
        }
        else if ((uint32_t)arg == LORA_IRQ_PIN)
        {
            c6_lora_irq_flag = true;
        }
    }

    /******************************************************************************/
    static void pi4io_init()
    {
        pi4io_m_dev = i2c_bus_device_create(i2c_bus, PI4IO_M_ADDR, 400000);
        if (pi4io_m_dev == NULL)
        {
            printf("pi4io_m_dev create failed\n");
        }
        else
        {
            printf("pi4io_m_dev create success\n");
        }
        pi4io_b_dev = i2c_bus_device_create(i2c_bus, PI4IO_B_ADDR, 400000);
        if (pi4io_b_dev == NULL)
        {
            printf("pi4io_b_dev create failed\n");
        }
        else
        {
            printf("pi4io_b_dev create success\n");
        }

        uint8_t in_data;
        // 模组
        // P0 BTN1
        // P1 BTN2
        // P2-P5 NC
        // P6 SX_ANT_SW
        // P7 SX_NRST
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_CHIP_RESET, 0xFF);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_read_byte(pi4io_m_dev, PI4IO_REG_CHIP_RESET, &in_data);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_IO_DIR, 0b11000000); // 0: input 1: output
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_OUT_H_IM, 0b00111100); // 使用到的引脚关闭High-Impedance
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_PULL_SEL, 0b11000011); // pull up/down select, 0 down, 1 up
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_PULL_EN, 0b11000011); // pull up/down enable, 0 disable, 1 enable
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_IN_DEF_STA, 0b00000011); // P0 P1 默认高电平, 按键按下触发中断
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_INT_MASK, 0b11111100); // P0 P1 中断使能 0 enable, 1 disable
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_OUT_SET, 0b10000000); // 默认输出为0
        vTaskDelay(10 / portTICK_PERIOD_MS);
        // 底板
        // P0 Power OFF system
        // P1 NC
        // P2 EXT_PWR_EN
        // P3 NC
        // P4 NC
        // P5 VIN_DET
        // P6 LCD_BL
        // P7 SYS_LEDG  低电平亮
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_CHIP_RESET, 0xFF);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_read_byte(pi4io_b_dev, PI4IO_REG_CHIP_RESET, &in_data);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_IO_DIR, 0b11000111); // 0: input 1: output
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_H_IM, 0b00011000); // 使用到的引脚关闭High-Impedance
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_PULL_SEL, 0b10000000); // pull up/down select, 0 down, 1 up
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_PULL_EN, 0b11111111); // pull up/down enable, 0 disable, 1 enable
        vTaskDelay(10 / portTICK_PERIOD_MS);
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, 0b11000010); // 默认输出
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    static void pi4io_release_all()
    {
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_H_IM, 0xFF);
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_OUT_H_IM, 0xFF);
    }

    static void pi4io_led_set_level(bool level)
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, &in_data);
        if (level)
        {
            clrbit(in_data, 7);
        }
        else
        {
            setbit(in_data, 7);
        }
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, in_data);
    }

    static void lcd_reset()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, &in_data);
        clrbit(in_data, 1); // LOW
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        setbit(in_data, 1); // HIGH
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    static void pi4io_lcd_bl_set_level(bool level)
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, &in_data);
        if (level)
        {
            setbit(in_data, 6);
        }
        else
        {
            clrbit(in_data, 6);
        }
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, in_data);
    }

    static bool pi4io_vin_has_input()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_b_dev, PI4IO_REG_IN_STA, &in_data);
        return getbit(in_data, 5);
    }

    static void pi4io_ext_power_control(bool en)
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, &in_data);
        if (en)
        {
            setbit(in_data, 2);
        }
        else
        {
            clrbit(in_data, 2);
        }
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, in_data);
    }

    // 关机需要产生高电平信号 100ms ~ 500ms 之间
    static void pi4io_power_off()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, &in_data);
        in_data |= 0b1;
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(200 / portTICK_PERIOD_MS);
        in_data &= 0b0;
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    static void pi4io_check_irq()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_m_dev, PI4IO_REG_IRQ_STA, &in_data);
        printf("pi4io_check_irq: %02X\n", in_data);
    }

    static void button_update()
    {
        uint8_t in_data;
        if (c6_irq_flag)
        {
            // printf("c6_irq_flag\n");
            c6_irq_flag = false;
            // 读取模组上PI4IO的中断状态
            i2c_bus_read_byte(pi4io_m_dev, PI4IO_REG_IRQ_STA, &in_data);
            if (getbit(in_data, 0))
            {
                btn1 = true;
                printf("btn1 pressed\n");
            }

            if (getbit(in_data, 1))
            {
                btn2 = true;
                printf("btn2 pressed\n");
            }
            // 清中断
            i2c_bus_read_byte(pi4io_m_dev, PI4IO_REG_CHIP_RESET, &in_data);
        }
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
    static void sx1262_init()
    {
        // Reset
        sx1262_reset();
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        // RF Switch
        sx1262_rf_turn_on();

        LoRaInit();

        // LoRa 配置
        uint32_t frequencyInHz = LORA_FREQ; // 915MHz
        int8_t txPowerInDbm = 22;           // 发射功率

        float tcxoVoltage = 3.0;
        bool useRegulatorLDO = true;

        uint8_t bandwidth = LORA_BW;
        uint8_t spreadingFactor = LORA_SF;
        uint8_t codingRate = LORA_CR;
        uint16_t preambleLength = LORA_PREAMBLE_LEN;
        uint8_t payloadLen = 0;
        bool crcOn = true;
        bool invertIrq = false;

        // LoRaDebugPrint(true);
        if (LoRaBegin(frequencyInHz, txPowerInDbm, tcxoVoltage, useRegulatorLDO) != 0)
        {
            ESP_LOGE(TAG, "LoRa begin failed");
            while (1)
            {
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
        }
        LoRaConfig(spreadingFactor, bandwidth, codingRate, preambleLength, payloadLen, crcOn, invertIrq);
    }

    static void sx1262_reset()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_m_dev, PI4IO_REG_OUT_SET, &in_data);
        clrbit(in_data, 7); // LOW
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        setbit(in_data, 7); // HIGH
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_OUT_SET, in_data);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    static void sx1262_rf_turn_on()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_m_dev, PI4IO_REG_OUT_SET, &in_data);
        setbit(in_data, 6); // HIGH
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_OUT_SET, in_data);
    }

    static void sx1262_rf_turn_off()
    {
        uint8_t in_data;
        i2c_bus_read_byte(pi4io_m_dev, PI4IO_REG_OUT_SET, &in_data);
        clrbit(in_data, 6); // LOW
        i2c_bus_write_byte(pi4io_m_dev, PI4IO_REG_OUT_SET, in_data);
    }

    // LoRa 发射测试
    static void sx1262_tx_test()
    {
        uint8_t buf[255] = {0}; // Maximum Payload size of SX1261/62/68 is 255
        TickType_t nowTick = xTaskGetTickCount();
        int txLen = sprintf((char *)buf, "hello world, this msg from M5's LoRa C6! %" PRIu32, nowTick);
        ESP_LOGI("LoRa", "sx1262 send: %s", buf);

        // Wait for transmission to complete
        if (LoRaSend(buf, txLen, SX126x_TXMODE_SYNC) == false)
        {
            ESP_LOGE("LoRa", "LoRaSend fail");
        }

        int lost = GetPacketLost();
        if (lost != 0)
        {
            ESP_LOGW("LoRa", "%d packets lost", lost);
        }
    }

    // LoRa 接收测试
    static void sx1262_rx_test()
    {
        uint8_t buf[255] = {0}; // Maximum Payload size of SX1261/62/68 is 255
        uint8_t rxLen = LoRaReceive(buf, sizeof(buf));
        if (rxLen > 0)
        {
            ESP_LOGI("LoRa", "%d byte packet received:[%.*s]", rxLen, rxLen, buf);
            int8_t rssi, snr;
            GetPacketStatus(&rssi, &snr);
            ESP_LOGI("LoRa", "rssi=%d[dBm] snr=%d[dB]\r\n", rssi, snr);

            // Just for test
            led_blink = !led_blink;
            pi4io_led_set_level(led_blink);
        }
    }
    /******************************************************************************/
    // AW32001	Battery Mode
    // BQ27220	Sleep Mode
    // BMI270	Lowest Power Mode
    // PI4IO(底板)	BL off & LED off & EXT PWR off
    // PI4IO(模组)	LoRa RF off
    // LCD	Sleep Mode
    // Touch	Sleep Mode?
    // SX1262	Sleep Mode
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
        printf("IRQ G7 level: %d\n", gpio_get_level(C6_IRQ_PIN));

        // PI4IO
        i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, 0b10000000); // P7 HIGH

        // SX1262
        SetStandby(SX126X_STANDBY_XOSC);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        sx1262_rf_turn_off();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        SetSleep(SX126X_SLEEP_START_COLD | SX126X_SLEEP_RTC_OFF);
        gpio_hold_en((gpio_num_t)CONFIG_NSS_GPIO); // 360uA  // !重要

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

    static void beep_init() {
        // Prepare and then apply the LEDC PWM timer configuration
        ledc_timer_config_t ledc_timer;
        ledc_timer.speed_mode       = LEDC_MODE;
        ledc_timer.duty_resolution  = LEDC_DUTY_RES;
        ledc_timer.timer_num        = LEDC_TIMER;
        ledc_timer.freq_hz          = LEDC_FREQUENCY;  // Set output frequency at 4 kHz
        ledc_timer.clk_cfg          = LEDC_AUTO_CLK;
        ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

        // Prepare and then apply the LEDC PWM channel configuration
        ledc_channel_config_t ledc_channel;
        ledc_channel.speed_mode     = LEDC_MODE;
        ledc_channel.channel        = LEDC_CHANNEL;
        ledc_channel.timer_sel      = LEDC_TIMER;
        ledc_channel.intr_type      = LEDC_INTR_DISABLE;
        ledc_channel.gpio_num       = LEDC_OUTPUT_IO;
        ledc_channel.duty           = 0; // Set duty to 0%
        ledc_channel.hpoint         = 0;
        ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    }

    static void beep_on() {
        ledc_set_freq(LEDC_MODE, LEDC_TIMER, 1000);
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    }

    static void beep_off() {
        ledc_set_freq(LEDC_MODE, LEDC_TIMER, 1000);
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    }

    static void grvoe_i2c_test() {
        // 删除
        i2c_bus_device_delete(&pi4io_b_dev);
        i2c_bus_device_delete(&pi4io_m_dev);
        i2c_bus_delete(&i2c_bus);
        // 重新初始化
        i2c_config_t conf;
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = GROVE_OUT_PIN;
        conf.scl_io_num = GROVE_IN_PIN;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = 400000;
        conf.clk_flags = 0;
        i2c_bus = i2c_bus_create(I2C_NUM_0, &conf);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
        i2c_bus_scan(i2c_bus, NULL, 0);

        while (1)
        {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    static void hat_gpio_init() {
        gpio_config_t io_conf;
        io_conf.intr_type = GPIO_INTR_DISABLE;
        io_conf.mode = GPIO_MODE_OUTPUT;
        io_conf.pin_bit_mask = 1 << HAT_PIN_1 | 1 << HAT_PIN_2 | 1 << HAT_PIN_3;
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
        gpio_config(&io_conf);
    }

    static void hat_gpio_blink() {
        if (hat_gpio_flag) {
            hat_gpio_flag = false;
            gpio_set_level(HAT_PIN_1, 1);
            gpio_set_level(HAT_PIN_2, 1);
            gpio_set_level(HAT_PIN_3, 1);
        } else {
            hat_gpio_flag = true;
            gpio_set_level(HAT_PIN_1, 0);
            gpio_set_level(HAT_PIN_2, 0);
            gpio_set_level(HAT_PIN_3, 0);
        }
    }
}
