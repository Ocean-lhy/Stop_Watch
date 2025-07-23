#include "i2c_expander.h"
#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "I2C_EXPANDER";

// 内部函数声明
static esp_err_t i2c_expander_write_reg(i2c_expander_handle_t *handle, uint8_t reg_addr, uint8_t data);
static esp_err_t i2c_expander_read_reg(i2c_expander_handle_t *handle, uint8_t reg_addr, uint8_t *data);
static esp_err_t i2c_expander_write_16bit_reg(i2c_expander_handle_t *handle, uint8_t reg_addr_l, uint16_t data);
static esp_err_t i2c_expander_read_16bit_reg(i2c_expander_handle_t *handle, uint8_t reg_addr_l, uint16_t *data);
static esp_err_t i2c_expander_write_multi_reg(i2c_expander_handle_t *handle, uint8_t reg_addr, const uint8_t *data, uint8_t length);
static esp_err_t i2c_expander_read_multi_reg(i2c_expander_handle_t *handle, uint8_t reg_addr, uint8_t *data, uint8_t length);
static bool gpio_pins_conflict(uint8_t pin1, uint8_t pin2);

// 中断互斥关系映射表
static const uint8_t gpio_conflict_map[][2] = {
    {GPIO_PIN_1, GPIO_PIN_6},   // 1-6
    {GPIO_PIN_2, GPIO_PIN_3},   // 2-3  
    {GPIO_PIN_7, GPIO_PIN_12},  // 7-12
    {GPIO_PIN_8, GPIO_PIN_9},   // 8-9
    {GPIO_PIN_10, GPIO_PIN_14}, // 10-14
    {GPIO_PIN_11, GPIO_PIN_13}, // 11-13
};

/**
 * @brief 写入单个寄存器
 */
static esp_err_t i2c_expander_write_reg(i2c_expander_handle_t *handle, uint8_t reg_addr, uint8_t data)
{
    if (handle == NULL || !handle->initialized) {
        return ESP_ERR_INVALID_ARG;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (handle->config.device_address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(handle->config.i2c_port, cmd, pdMS_TO_TICKS(handle->config.timeout_ms));
    i2c_cmd_link_delete(cmd);

    return ret;
}

/**
 * @brief 读取单个寄存器
 */
static esp_err_t i2c_expander_read_reg(i2c_expander_handle_t *handle, uint8_t reg_addr, uint8_t *data)
{
    if (handle == NULL || !handle->initialized || data == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (handle->config.device_address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (handle->config.device_address << 1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, data, I2C_MASTER_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(handle->config.i2c_port, cmd, pdMS_TO_TICKS(handle->config.timeout_ms));
    i2c_cmd_link_delete(cmd);

    return ret;
}

/**
 * @brief 写入16位寄存器（小端序）
 */
static esp_err_t i2c_expander_write_16bit_reg(i2c_expander_handle_t *handle, uint8_t reg_addr_l, uint16_t data)
{
    uint8_t data_bytes[2] = {data & 0xFF, (data >> 8) & 0xFF};
    return i2c_expander_write_multi_reg(handle, reg_addr_l, data_bytes, 2);
}

/**
 * @brief 读取16位寄存器（小端序）
 */
static esp_err_t i2c_expander_read_16bit_reg(i2c_expander_handle_t *handle, uint8_t reg_addr_l, uint16_t *data)
{
    if (data == NULL) return ESP_ERR_INVALID_ARG;
    
    uint8_t data_bytes[2];
    esp_err_t ret = i2c_expander_read_multi_reg(handle, reg_addr_l, data_bytes, 2);
    if (ret == ESP_OK) {
        *data = (data_bytes[1] << 8) | data_bytes[0];
    }
    return ret;
}

/**
 * @brief 写入多个寄存器
 */
static esp_err_t i2c_expander_write_multi_reg(i2c_expander_handle_t *handle, uint8_t reg_addr, const uint8_t *data, uint8_t length)
{
    if (handle == NULL || !handle->initialized || data == NULL || length == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (handle->config.device_address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    
    for (uint8_t i = 0; i < length; i++) {
        i2c_master_write_byte(cmd, data[i], true);
    }
    
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(handle->config.i2c_port, cmd, pdMS_TO_TICKS(handle->config.timeout_ms));
    i2c_cmd_link_delete(cmd);

    return ret;
}

/**
 * @brief 读取多个寄存器
 */
static esp_err_t i2c_expander_read_multi_reg(i2c_expander_handle_t *handle, uint8_t reg_addr, uint8_t *data, uint8_t length)
{
    if (handle == NULL || !handle->initialized || data == NULL || length == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (handle->config.device_address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (handle->config.device_address << 1) | I2C_MASTER_READ, true);
    
    for (uint8_t i = 0; i < length; i++) {
        i2c_master_read_byte(cmd, &data[i], (i == length - 1) ? I2C_MASTER_NACK : I2C_MASTER_ACK);
    }
    
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(handle->config.i2c_port, cmd, pdMS_TO_TICKS(handle->config.timeout_ms));
    i2c_cmd_link_delete(cmd);

    return ret;
}

/**
 * @brief 检查GPIO引脚冲突
 */
static bool gpio_pins_conflict(uint8_t pin1, uint8_t pin2)
{
    for (int i = 0; i < sizeof(gpio_conflict_map) / sizeof(gpio_conflict_map[0]); i++) {
        if ((gpio_conflict_map[i][0] == pin1 && gpio_conflict_map[i][1] == pin2) ||
            (gpio_conflict_map[i][0] == pin2 && gpio_conflict_map[i][1] == pin1)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief 初始化I2C扩展器
 */
esp_err_t i2c_expander_init(const i2c_expander_config_t *config, i2c_expander_handle_t **handle)
{
    if (config == NULL || handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    // 分配内存
    i2c_expander_handle_t *h = malloc(sizeof(i2c_expander_handle_t));
    if (h == NULL) {
        return ESP_ERR_NO_MEM;
    }

    // 复制配置
    memcpy(&h->config, config, sizeof(i2c_expander_config_t));
    h->initialized = true;

    // 测试通信
    uint16_t uid;
    esp_err_t ret = i2c_expander_read_uid(h, &uid);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "无法与I2C扩展器通信: %s", esp_err_to_name(ret));
        free(h);
        return ret;
    }

    ESP_LOGI(TAG, "I2C扩展器初始化成功，UID: 0x%04X", uid);
    *handle = h;
    return ESP_OK;
}

/**
 * @brief 反初始化I2C扩展器
 */
esp_err_t i2c_expander_deinit(i2c_expander_handle_t *handle)
{
    if (handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    handle->initialized = false;
    free(handle);
    return ESP_OK;
}

/**
 * @brief 读取设备UID
 */
esp_err_t i2c_expander_read_uid(i2c_expander_handle_t *handle, uint16_t *uid)
{
    if (uid == NULL) return ESP_ERR_INVALID_ARG;
    
    return i2c_expander_read_16bit_reg(handle, REG_UID_L, uid);
}

/**
 * @brief 读取版本信息
 */
esp_err_t i2c_expander_read_version(i2c_expander_handle_t *handle, uint8_t *hw_version, uint8_t *fw_version)
{
    if (hw_version == NULL || fw_version == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t version_reg;
    esp_err_t ret = i2c_expander_read_reg(handle, REG_VERSION, &version_reg);
    if (ret == ESP_OK) {
        *hw_version = (version_reg >> 4) & 0x0F;
        *fw_version = version_reg & 0x0F;
    }
    return ret;
}

/**
 * @brief 设置GPIO模式
 */
esp_err_t i2c_expander_gpio_set_mode(i2c_expander_handle_t *handle, uint8_t pin, i2c_exp_gpio_mode_t mode)
{
    if (pin > GPIO_PIN_14) {
        return ESP_ERR_INVALID_ARG;
    }

    uint16_t gpio_mode;
    esp_err_t ret = i2c_expander_read_16bit_reg(handle, REG_GPIO_M_L, &gpio_mode);
    if (ret != ESP_OK) return ret;

    if (mode == I2C_EXP_GPIO_MODE_OUTPUT) {
        gpio_mode |= (1 << pin);
    } else {
        gpio_mode &= ~(1 << pin);
    }

    return i2c_expander_write_16bit_reg(handle, REG_GPIO_M_L, gpio_mode);
}

/**
 * @brief 设置GPIO输出电平
 */
esp_err_t i2c_expander_gpio_set_level(i2c_expander_handle_t *handle, uint8_t pin, uint8_t level)
{
    if (pin > GPIO_PIN_14) {
        return ESP_ERR_INVALID_ARG;
    }

    uint16_t gpio_output;
    esp_err_t ret = i2c_expander_read_16bit_reg(handle, REG_GPIO_O_L, &gpio_output);
    if (ret != ESP_OK) return ret;

    if (level) {
        gpio_output |= (1 << pin);
    } else {
        gpio_output &= ~(1 << pin);
    }

    return i2c_expander_write_16bit_reg(handle, REG_GPIO_O_L, gpio_output);
}

/**
 * @brief 读取GPIO输入电平
 */
esp_err_t i2c_expander_gpio_get_level(i2c_expander_handle_t *handle, uint8_t pin, uint8_t *level)
{
    if (pin > GPIO_PIN_14 || level == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint16_t gpio_input;
    esp_err_t ret = i2c_expander_read_16bit_reg(handle, REG_GPIO_I_L, &gpio_input);
    if (ret == ESP_OK) {
        *level = (gpio_input & (1 << pin)) ? 1 : 0;
    }
    return ret;
}

/**
 * @brief 设置GPIO上下拉
 */
esp_err_t i2c_expander_gpio_set_pull(i2c_expander_handle_t *handle, uint8_t pin, i2c_exp_gpio_pull_t pull)
{
    if (pin > GPIO_PIN_14) {
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret;
    uint16_t gpio_pu, gpio_pd;

    ret = i2c_expander_read_16bit_reg(handle, REG_GPIO_PU_L, &gpio_pu);
    if (ret != ESP_OK) return ret;

    ret = i2c_expander_read_16bit_reg(handle, REG_GPIO_PD_L, &gpio_pd);
    if (ret != ESP_OK) return ret;

    // 清除当前设置
    gpio_pu &= ~(1 << pin);
    gpio_pd &= ~(1 << pin);

    switch (pull) {
        case I2C_EXP_GPIO_PULL_UP:
            gpio_pu |= (1 << pin);
            break;
        case I2C_EXP_GPIO_PULL_DOWN:
            gpio_pd |= (1 << pin);
            break;
        case I2C_EXP_GPIO_PULL_NONE:
        default:
            // 已经清除了，不需要额外操作
            break;
    }

    ret = i2c_expander_write_16bit_reg(handle, REG_GPIO_PU_L, gpio_pu);
    if (ret != ESP_OK) return ret;

    return i2c_expander_write_16bit_reg(handle, REG_GPIO_PD_L, gpio_pd);
}

/**
 * @brief 设置GPIO驱动模式
 */
esp_err_t i2c_expander_gpio_set_drive(i2c_expander_handle_t *handle, uint8_t pin, i2c_exp_gpio_drive_t drive)
{
    if (pin > GPIO_PIN_14) {
        return ESP_ERR_INVALID_ARG;
    }

    uint16_t gpio_drive;
    esp_err_t ret = i2c_expander_read_16bit_reg(handle, REG_GPIO_DRV_L, &gpio_drive);
    if (ret != ESP_OK) return ret;

    if (drive == I2C_EXP_GPIO_DRIVE_OPEN_DRAIN) {
        gpio_drive |= (1 << pin);
    } else {
        gpio_drive &= ~(1 << pin);
    }

    return i2c_expander_write_16bit_reg(handle, REG_GPIO_DRV_L, gpio_drive);
}

/**
 * @brief 设置GPIO中断
 */
esp_err_t i2c_expander_gpio_set_interrupt(i2c_expander_handle_t *handle, uint8_t pin, i2c_exp_gpio_intr_t intr_type)
{
    if (pin > GPIO_PIN_14) {
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret;
    uint16_t gpio_ie, gpio_it;

    ret = i2c_expander_read_16bit_reg(handle, REG_GPIO_IE_L, &gpio_ie);
    if (ret != ESP_OK) return ret;

    ret = i2c_expander_read_16bit_reg(handle, REG_GPIO_IT_L, &gpio_it);
    if (ret != ESP_OK) return ret;

    if (intr_type == I2C_EXP_GPIO_INTR_DISABLE) {
        gpio_ie &= ~(1 << pin);
    } else {
        // 检查中断冲突
        for (int i = 0; i < 14; i++) {
            if (i != pin && (gpio_ie & (1 << i)) && gpio_pins_conflict(pin, i)) {
                ESP_LOGW(TAG, "GPIO引脚 %d 和 %d 中断功能冲突", pin, i);
                return ESP_ERR_INVALID_STATE;
            }
        }

        gpio_ie |= (1 << pin);
        
        if (intr_type == I2C_EXP_GPIO_INTR_RISING_EDGE) {
            gpio_it |= (1 << pin);
        } else {
            gpio_it &= ~(1 << pin);
        }
    }

    ret = i2c_expander_write_16bit_reg(handle, REG_GPIO_IE_L, gpio_ie);
    if (ret != ESP_OK) return ret;

    return i2c_expander_write_16bit_reg(handle, REG_GPIO_IT_L, gpio_it);
}

/**
 * @brief 读取GPIO中断状态
 */
esp_err_t i2c_expander_gpio_get_interrupt_status(i2c_expander_handle_t *handle, uint16_t *status)
{
    if (status == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    return i2c_expander_read_16bit_reg(handle, REG_GPIO_IS_L, status);
}

/**
 * @brief 清除GPIO中断状态
 */
esp_err_t i2c_expander_gpio_clear_interrupt(i2c_expander_handle_t *handle, uint8_t pin)
{
    if (pin > GPIO_PIN_14) {
        return ESP_ERR_INVALID_ARG;
    }

    uint16_t gpio_is;
    esp_err_t ret = i2c_expander_read_16bit_reg(handle, REG_GPIO_IS_L, &gpio_is);
    if (ret != ESP_OK) return ret;

    gpio_is &= ~(1 << pin);  // 写0清除
    return i2c_expander_write_16bit_reg(handle, REG_GPIO_IS_L, gpio_is);
}

/**
 * @brief 启动ADC转换
 */
esp_err_t i2c_expander_adc_read(i2c_expander_handle_t *handle, uint8_t channel, uint16_t *result)
{
    if (channel < 1 || channel > 4 || result == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret;

    // 设置通道并启动转换
    uint8_t adc_ctrl = (channel & ADC_CTRL_CH_MASK) | ADC_CTRL_START;
    ret = i2c_expander_write_reg(handle, REG_ADC_CTRL, adc_ctrl);
    if (ret != ESP_OK) return ret;

    // 等待转换完成
    uint8_t busy_count = 0;
    do {
        vTaskDelay(pdMS_TO_TICKS(1));
        ret = i2c_expander_read_reg(handle, REG_ADC_CTRL, &adc_ctrl);
        if (ret != ESP_OK) return ret;
        
        if (++busy_count > 100) {  // 超时保护
            ESP_LOGW(TAG, "ADC转换超时");
            return ESP_ERR_TIMEOUT;
        }
    } while (adc_ctrl & ADC_CTRL_BUSY);

    // 读取转换结果
    return i2c_expander_read_16bit_reg(handle, REG_ADC_D_L, result);
}

/**
 * @brief 检查ADC转换状态
 */
esp_err_t i2c_expander_adc_is_busy(i2c_expander_handle_t *handle, bool *busy)
{
    if (busy == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t adc_ctrl;
    esp_err_t ret = i2c_expander_read_reg(handle, REG_ADC_CTRL, &adc_ctrl);
    if (ret == ESP_OK) {
        *busy = (adc_ctrl & ADC_CTRL_BUSY) != 0;
    }
    return ret;
}

/**
 * @brief 读取温度
 */
esp_err_t i2c_expander_temp_read(i2c_expander_handle_t *handle, uint16_t *temperature)
{
    if (temperature == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret;

    // 启动温度转换
    ret = i2c_expander_write_reg(handle, REG_TEMP_CTRL, TEMP_CTRL_START);
    if (ret != ESP_OK) return ret;

    // 等待转换完成
    uint8_t temp_ctrl;
    uint8_t busy_count = 0;
    do {
        vTaskDelay(pdMS_TO_TICKS(1));
        ret = i2c_expander_read_reg(handle, REG_TEMP_CTRL, &temp_ctrl);
        if (ret != ESP_OK) return ret;
        
        if (++busy_count > 100) {  // 超时保护
            ESP_LOGW(TAG, "温度转换超时");
            return ESP_ERR_TIMEOUT;
        }
    } while (temp_ctrl & TEMP_CTRL_BUSY);

    // 读取转换结果
    return i2c_expander_read_16bit_reg(handle, REG_TEMP_D_L, temperature);
}

/**
 * @brief 检查温度转换状态
 */
esp_err_t i2c_expander_temp_is_busy(i2c_expander_handle_t *handle, bool *busy)
{
    if (busy == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t temp_ctrl;
    esp_err_t ret = i2c_expander_read_reg(handle, REG_TEMP_CTRL, &temp_ctrl);
    if (ret == ESP_OK) {
        *busy = (temp_ctrl & TEMP_CTRL_BUSY) != 0;
    }
    return ret;
}

/**
 * @brief 设置PWM频率
 */
esp_err_t i2c_expander_pwm_set_frequency(i2c_expander_handle_t *handle, uint16_t frequency)
{
    return i2c_expander_write_16bit_reg(handle, REG_PWM_FREQ_L, frequency);
}

/**
 * @brief 读取PWM频率
 */
esp_err_t i2c_expander_pwm_get_frequency(i2c_expander_handle_t *handle, uint16_t *frequency)
{
    if (frequency == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_expander_read_16bit_reg(handle, REG_PWM_FREQ_L, frequency);
}

/**
 * @brief 设置PWM占空比
 */
esp_err_t i2c_expander_pwm_set_duty(i2c_expander_handle_t *handle, uint8_t channel, uint8_t duty, bool polarity, bool enable)
{
    if (channel > 3 || duty > 100) {
        return ESP_ERR_INVALID_ARG;
    }

    // 将0-100的占空比转换为8位值(0-0xFFF)
    uint16_t duty_12bit = (duty * 0x0FFF) / 100;
    
    // 添加控制位到高位
    if (enable) duty_12bit |= (PWM_ENABLE << 8);
    if (polarity) duty_12bit |= (PWM_POLARITY << 8);
    
    uint8_t reg_addr_l = REG_PWM1_DUTY_L + (channel * 2);
    ESP_LOGI(TAG, "写入: %04X", duty_12bit);
    return i2c_expander_write_16bit_reg(handle, reg_addr_l, duty_12bit);
}

/**
 * @brief 读取PWM占空比
 */
esp_err_t i2c_expander_pwm_get_duty(i2c_expander_handle_t *handle, uint8_t channel, uint8_t *duty, bool *polarity, bool *enable)
{
    if (channel > 3 || duty == NULL || polarity == NULL || enable == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t reg_addr_l = REG_PWM1_DUTY_L + (channel * 2);
    uint16_t duty_16bit = 0;
    
    esp_err_t ret = i2c_expander_read_16bit_reg(handle, reg_addr_l, &duty_16bit);
    ESP_LOGI(TAG, "读取: %04X", duty_16bit);
    if (ret != ESP_OK) return ret;
    
    // 提取12位占空比值
    uint16_t duty_12bit = duty_16bit & 0x0FFF;
    
    // 转换为0-100的占空比
    *duty = (duty_12bit * 100) / 0x0FFF;
    
    // 提取极性
    *polarity = (duty_16bit & (PWM_POLARITY << 8)) != 0;
    
    // 提取使能状态
    *enable = (duty_16bit & (PWM_ENABLE << 8)) != 0;
    
    return ESP_OK;
}

/**
 * @brief 设置LED数量
 * @note LED控制复用在IO14(PB7)引脚上，使用此功能时GPIO14的普通GPIO功能不可用
 */
esp_err_t i2c_expander_led_set_count(i2c_expander_handle_t *handle, uint8_t num_leds)
{
    if (num_leds > 32) {
        return ESP_ERR_INVALID_ARG;
    }

    if (num_leds > 0) {
        ESP_LOGI(TAG, "启用LED控制，IO14(PB7)复用为Neopixel控制引脚");
    }

    uint8_t led_cfg = num_leds & LED_CFG_NUM_MASK;
    return i2c_expander_write_reg(handle, REG_LED_CFG, led_cfg);
}

/**
 * @brief 设置单个LED颜色
 */
esp_err_t i2c_expander_led_set_color(i2c_expander_handle_t *handle, uint8_t led_index, rgb_color_t color)
{
    if (led_index > 31 || color.r > 31 || color.g > 63 || color.b > 31) {
        return ESP_ERR_INVALID_ARG;
    }

    // 转换为RGB565格式
    uint16_t rgb565 = ((color.r & 0x1F) << 11) | ((color.g & 0x3F) << 5) | (color.b & 0x1F);
    
    // 计算寄存器地址
    uint8_t reg_addr = REG_LED_RAM_START + (led_index * 2);
    
    // 写入RGB565数据（高位先行）
    uint8_t data[2] = {(rgb565 >> 8) & 0xFF, rgb565 & 0xFF};
    return i2c_expander_write_multi_reg(handle, reg_addr, data, 2);
}

/**
 * @brief 刷新LED显示
 */
esp_err_t i2c_expander_led_refresh(i2c_expander_handle_t *handle)
{
    uint8_t led_cfg;
    esp_err_t ret = i2c_expander_read_reg(handle, REG_LED_CFG, &led_cfg);
    if (ret != ESP_OK) return ret;

    led_cfg |= LED_CFG_REFRESH;
    return i2c_expander_write_reg(handle, REG_LED_CFG, led_cfg);
}

/**
 * @brief 写入RTC RAM
 */
esp_err_t i2c_expander_rtc_ram_write(i2c_expander_handle_t *handle, uint8_t offset, const uint8_t *data, uint8_t length)
{
    if (offset > 31 || data == NULL || length == 0 || (offset + length) > 32) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t reg_addr = REG_RTC_RAM_START + offset;
    return i2c_expander_write_multi_reg(handle, reg_addr, data, length);
}

/**
 * @brief 读取RTC RAM
 */
esp_err_t i2c_expander_rtc_ram_read(i2c_expander_handle_t *handle, uint8_t offset, uint8_t *data, uint8_t length)
{
    if (offset > 31 || data == NULL || length == 0 || (offset + length) > 32) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t reg_addr = REG_RTC_RAM_START + offset;
    return i2c_expander_read_multi_reg(handle, reg_addr, data, length);
}

/**
 * @brief 设置I2C配置
 */
esp_err_t i2c_expander_set_i2c_config(i2c_expander_handle_t *handle, uint8_t sleep_time, bool speed_400k)
{
    if (sleep_time > 15) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t i2c_cfg = sleep_time & I2C_CFG_SLEEP_MASK;
    if (speed_400k) {
        i2c_cfg |= I2C_CFG_SPEED_400K;
    }

    return i2c_expander_write_reg(handle, REG_I2C_CFG, i2c_cfg);
}

/**
 * @brief 读取参考电压
 */
esp_err_t i2c_expander_get_ref_voltage(i2c_expander_handle_t *handle, uint16_t *ref_voltage)
{
    if (ref_voltage == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_expander_read_16bit_reg(handle, REG_REF_VOLTAGE_L, ref_voltage);
}

// 读取GPIO寄存器状态（用于调试）
esp_err_t i2c_expander_gpio_get_mode_reg(i2c_expander_handle_t *handle, uint16_t *mode_reg)
{
    if (mode_reg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_expander_read_16bit_reg(handle, REG_GPIO_M_L, mode_reg);
}

esp_err_t i2c_expander_gpio_get_output_reg(i2c_expander_handle_t *handle, uint16_t *output_reg)
{
    if (output_reg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_expander_read_16bit_reg(handle, REG_GPIO_O_L, output_reg);
}

esp_err_t i2c_expander_gpio_get_input_reg(i2c_expander_handle_t *handle, uint16_t *input_reg)
{
    if (input_reg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_expander_read_16bit_reg(handle, REG_GPIO_I_L, input_reg);
}

esp_err_t i2c_expander_gpio_get_pull_up_reg(i2c_expander_handle_t *handle, uint16_t *pull_up_reg)
{
    if (pull_up_reg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_expander_read_16bit_reg(handle, REG_GPIO_PU_L, pull_up_reg);
}

esp_err_t i2c_expander_gpio_get_pull_down_reg(i2c_expander_handle_t *handle, uint16_t *pull_down_reg)
{
    if (pull_down_reg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_expander_read_16bit_reg(handle, REG_GPIO_PD_L, pull_down_reg);
}

esp_err_t i2c_expander_gpio_get_drive_reg(i2c_expander_handle_t *handle, uint16_t *drive_reg)
{
    if (drive_reg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_expander_read_16bit_reg(handle, REG_GPIO_DRV_L, drive_reg);
}