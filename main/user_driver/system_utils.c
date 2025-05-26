#include "system_utils.h"
#include "esp_log.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <inttypes.h>
#include "i2c_bus.h"
#include "pi4io_driver.h"
#include "aw32001_driver.h"
#include "bmi270_driver.h"
#include "bq27220_driver.h"
#include "cst9217_driver.h"
#include "motor_driver.h"
static const char *TAG = "system_utils";

uint8_t btn1 = 0;
uint8_t btn2 = 0;
volatile bool touch_irq_flag = false;
static int32_t restart_counter = 0;
extern SemaphoreHandle_t touch_mux;


void print_chip_info()
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "This is %s chip with %d CPU core(s), %s%s%s%s, ",
             CONFIG_IDF_TARGET,
             chip_info.cores,
             (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
             (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
             (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
             (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    ESP_LOGI(TAG, "silicon revision v%d.%d, ", major_rev, minor_rev);
    if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
    {
        ESP_LOGE(TAG, "Get flash size failed");
        return;
    }

    ESP_LOGI(TAG, "%" PRIu32 "MB %s flash", flash_size / (uint32_t)(1024 * 1024),
             (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    ESP_LOGI(TAG, "Minimum free heap size: %" PRIu32 " bytes", esp_get_minimum_free_heap_size());
}

bool global_irq_init()
{
    ESP_LOGI(TAG, "global_irq_init");
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1 << USER_BUTTON1_PIN) | (1 << USER_BUTTON2_PIN) | (1 << TP_INT_IRQ_PIN) /* | 1 << IMU_IRQ_PIN*/;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(USER_BUTTON1_PIN, global_irq_handler, (void *)USER_BUTTON1_PIN);
    gpio_isr_handler_add(USER_BUTTON2_PIN, global_irq_handler, (void *)USER_BUTTON2_PIN);
    gpio_isr_handler_add(TP_INT_IRQ_PIN, global_irq_handler, (void *)TP_INT_IRQ_PIN);
    // gpio_isr_handler_add(IMU_IRQ_PIN, global_irq_handler, (void *)IMU_IRQ_PIN);
    return true;
}

void IRAM_ATTR global_irq_handler(void *arg)
{
    if ((uint32_t)arg == TP_INT_IRQ_PIN)
    {
        touch_irq_flag = true;
        if (touch_mux == NULL)
        {
            return;
        }
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(touch_mux, &xHigherPriorityTaskWoken);

        if (xHigherPriorityTaskWoken) {
            portYIELD_FROM_ISR();
        }
    }
    else 
    if ((uint32_t)arg == USER_BUTTON1_PIN)
    {
        btn1 = 1;
    }
    else 
    if ((uint32_t)arg == USER_BUTTON2_PIN)
    {
        btn2 = 1;
    }
    button_vibrate();
}

void enter_light_sleep_mode()
{
    ESP_LOGI(TAG, "enter_light_sleep_mode");
    esp_light_sleep_start();
}

void enter_deep_sleep_mode()
{
    ESP_LOGI(TAG, "enter_deep_sleep_mode");
    uint8_t in_data;
    // BQ27220 Reg 0x9206 Operation Config A

    // AW32001
    i2c_bus_device_handle_t aw32001_dev = NULL;
    i2c_bus_read_byte(aw32001_dev, 0x01, &in_data);
    setbit(in_data, 3);
    i2c_bus_write_byte(aw32001_dev, 0x01, in_data);
    i2c_bus_read_byte(aw32001_dev, 0x01, &in_data);
    ESP_LOGI(TAG, "AW32001 0x01 CEB: %d", getbit(in_data, 3));

    // BMI270
    i2c_bus_device_handle_t bmi270_dev = NULL;
    i2c_bus_write_byte(bmi270_dev, 0x7C, 0x01);
    i2c_bus_write_byte(bmi270_dev, 0x7D, 0x00);

    // Check IRQ
    ESP_LOGI(TAG, "IRQ G7 level: %d", gpio_get_level(TP_INT_IRQ_PIN));

    // PI4IO
    // i2c_bus_write_byte(pi4io_b_dev, PI4IO_REG_OUT_SET, 0b10000000); // P7 HIGH

    vTaskDelay(100 / portTICK_PERIOD_MS);

    esp_deep_sleep_start();
}

void nvs_init()
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
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
    }
    else
    {
        ESP_LOGI(TAG, "NVS handle opened successfully");

        // Read
        ESP_LOGI(TAG, "Reading restart counter from NVS ... ");
        err = nvs_get_i32(my_handle, "restart_counter", &restart_counter);
        switch (err)
        {
        case ESP_OK:
            ESP_LOGI(TAG, "Done");
            ESP_LOGI(TAG, "Restart counter = %" PRIu32, restart_counter);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            ESP_LOGI(TAG, "The value is not initialized yet!");
            break;
        default:
            ESP_LOGE(TAG, "Error (%s) reading!", esp_err_to_name(err));
        }

        // Write
        ESP_LOGI(TAG, "Updating restart counter in NVS ... ");
        restart_counter++;
        err = nvs_set_i32(my_handle, "restart_counter", restart_counter);
        ESP_LOGI(TAG, "%s", (err != ESP_OK) ? "Failed!" : "Done");

        ESP_LOGI(TAG, "Committing updates in NVS ... ");
        err = nvs_commit(my_handle);
        ESP_LOGI(TAG, "%s", (err != ESP_OK) ? "Failed!" : "Done");

        // Close
        nvs_close(my_handle);
    }
}

void littlefs_init()
{
    ESP_LOGI(TAG, "littlefs_init");
    esp_vfs_littlefs_conf_t conf = {
        .base_path = "/littlefs",
        .partition_label = "littlefs",
        .format_if_mount_failed = true,
        .dont_mount = false,
    };
    esp_err_t ret = esp_vfs_littlefs_register(&conf);
    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE(TAG, "Failed to find LittleFS partition");
        }
        else
        {
            ESP_LOGE(TAG, "Failed to initialize LittleFS (%s)", esp_err_to_name(ret));
        }
        return;
    }
    size_t total = 0, used = 0;
    ret = esp_littlefs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get LittleFS partition information (%s)", esp_err_to_name(ret));
    }
    else
    {
        ESP_LOGI(TAG, "Mounted LittleFS partition");
        ESP_LOGI(TAG, "Total: %d, Used: %d", total, used);
    }
}


void grove_i2c_test() 
{
    ESP_LOGI(TAG, "grove_i2c_test");
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GROVE_3_PIN;
    conf.scl_io_num = GROVE_4_PIN;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 400000;
    conf.clk_flags = 0;
    i2c_bus_handle_t grove_i2c_bus = i2c_bus_create(I2C_NUM_1, &conf);

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ESP_LOGI(TAG, "grove_i2c_test scan");
    uint8_t addr[128] = {0};
    i2c_bus_scan(grove_i2c_bus, addr, 0);
    for (int i = 0; i < 128; i++) 
    {
        if (addr[i] != 0) 
        {
            ESP_LOGI(TAG, "grove found device at address 0x%02X", addr[i]);
        }
    }

    i2c_bus_delete(&grove_i2c_bus);
} 

void power_off()
{
    ESP_LOGI(TAG, "power_off");
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1 << PWROFF_PLUSE_PIN);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
    gpio_set_level(PWROFF_PLUSE_PIN, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(PWROFF_PLUSE_PIN, 0);
}
