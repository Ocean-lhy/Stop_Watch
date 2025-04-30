#include "bmi270_driver.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "bmi270_driver";
static i2c_bus_device_handle_t bmi270_dev = NULL;
static struct bmi2_dev aux_bmi2_dev;
static struct bmi2_sens_config config[3];
static struct bmi2_sens_data bmi_sensor_data = {{0}};
static uint8_t sensor_list[3] = {BMI2_ACCEL, BMI2_GYRO, BMI2_WRIST_WEAR_WAKE_UP};/* Select features and their pins to be mapped to */
static struct bmi2_sens_int_config sens_int = { .type = BMI2_WRIST_WEAR_WAKE_UP, .hw_int_pin = BMI2_INT1 };
/* Initialize status of wrist wear wakeup interrupt */
struct bmi2_int_pin_config pin_config = { 0 };
uint16_t int_status = 0;

int8_t bmi2_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    if ((reg_data == NULL) || (len == 0) || (len > 32))
    {
        return -1;
    }
    i2c_bus_read_bytes(bmi270_dev, reg_addr, len, reg_data);
    return 0;
}

int8_t bmi2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    if ((reg_data == NULL) || (len == 0) || (len > 32))
    {
        return -1;
    }
    i2c_bus_write_bytes(bmi270_dev, reg_addr, len, reg_data);
    return 0;
}

void bmi2_delay_us(uint32_t period, void *intf_ptr)
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

void bmi270_dev_init(i2c_bus_handle_t i2c_bus)
{
    bmi270_dev = i2c_bus_device_create(i2c_bus, BMI270_ADDR, 400000);
    if (bmi270_dev == NULL)
    {
        ESP_LOGE(TAG, "bmi270_dev create failed");
    }
    else
    {
        ESP_LOGI(TAG, "bmi270_dev create success");
    }

    config[ACCEL].type = BMI2_ACCEL;
    config[GYRO].type = BMI2_GYRO;
    config[2].type = BMI2_WRIST_WEAR_WAKE_UP;

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
    bmi270_sensor_enable(sensor_list, 3, &aux_bmi2_dev);

    bmi2_get_int_pin_config(&pin_config, &aux_bmi2_dev);
    ESP_LOGI(TAG, "Pin config: %d, %d,lvl: %d, od: %d, output_en: %d, input_en: %d, lvl: %d, od: %d, output_en: %d, input_en: %d", 
        pin_config.pin_type, pin_config.int_latch, 
        pin_config.pin_cfg[0].lvl, pin_config.pin_cfg[0].od, pin_config.pin_cfg[0].output_en, pin_config.pin_cfg[0].input_en, 
        pin_config.pin_cfg[1].lvl, pin_config.pin_cfg[1].od, pin_config.pin_cfg[1].output_en, pin_config.pin_cfg[1].input_en);

    bmi270_get_sensor_config(config, 2, &aux_bmi2_dev);

    /* Set the aux configurations. */
    bmi270_set_sensor_config(config, 2, &aux_bmi2_dev);

    pin_config.pin_type = BMI2_INT1;
    pin_config.pin_cfg[0].input_en = BMI2_INT_INPUT_DISABLE;
    pin_config.pin_cfg[0].lvl = BMI2_INT_ACTIVE_HIGH;
    pin_config.pin_cfg[0].od = BMI2_INT_PUSH_PULL;
    pin_config.pin_cfg[0].output_en = BMI2_INT_OUTPUT_ENABLE;
    pin_config.int_latch = BMI2_INT_LATCH;

    /* Map data ready interrupt to interrupt pin. */
    // bmi2_map_data_int(BMI2_DRDY_INT, BMI2_INT1, &aux_bmi2_dev);

    // bmi2_set_int_pin_config(&pin_config, &aux_bmi2_dev);
    // bmi270_map_feat_int(&sens_int, 1, &aux_bmi2_dev);

}

void bmi270_wakeup_enable(uint8_t enable)
{
    if (enable)
    {
        bmi270_sensor_enable(sensor_list, 3, &aux_bmi2_dev);
    }
    else
    {
        bmi270_sensor_disable(sensor_list, 3, &aux_bmi2_dev);
    }
}

void bmi270_dev_update()
{
    bmi2_get_sensor_data(&bmi_sensor_data, &aux_bmi2_dev);
    ESP_LOGI(TAG, "Accel: x: %d, y: %d, z: %d", bmi_sensor_data.acc.x, bmi_sensor_data.acc.y, bmi_sensor_data.acc.z);
    ESP_LOGI(TAG, "Gyro: x: %d, y: %d, z: %d", bmi_sensor_data.gyr.x, bmi_sensor_data.gyr.y, bmi_sensor_data.gyr.z);
    bmi2_get_int_status(&int_status, &aux_bmi2_dev);
    ESP_LOGI(TAG, "Int status: %d", int_status);
}

void bmi270_get_data(int *ax, int *ay, int *az, int *gx, int *gy, int *gz)
{
    if (ax) *ax = bmi_sensor_data.acc.x;
    if (ay) *ay = bmi_sensor_data.acc.y;
    if (az) *az = bmi_sensor_data.acc.z;
    if (gx) *gx = bmi_sensor_data.gyr.x;
    if (gy) *gy = bmi_sensor_data.gyr.y;
    if (gz) *gz = bmi_sensor_data.gyr.z;
}

void bmi270_dev_sleep()
{
    uint8_t data = 0x04;
    bmi2_i2c_write(0x7D, &data, 1, &aux_bmi2_dev);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    data = 0x17;
    bmi2_i2c_write(0x40, &data, 1, &aux_bmi2_dev);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    data = 0x03;
    bmi2_i2c_write(0x7C, &data, 1, &aux_bmi2_dev);
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

void bmi270_dev_wakeup()
{
    uint8_t data = 0x0E;
    bmi2_i2c_write(0x7D, &data, 1, &aux_bmi2_dev);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    data = 0xA8;
    bmi2_i2c_write(0x40, &data, 1, &aux_bmi2_dev);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    data = 0xA9;
    bmi2_i2c_write(0x42, &data, 1, &aux_bmi2_dev);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    data = 0x02;
    bmi2_i2c_write(0x7C, &data, 1, &aux_bmi2_dev);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    bmi270_sensor_enable(sensor_list, 3, &aux_bmi2_dev);
}