#include "py32_driver.h"
#include "i2c_expander.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG                    = "py32_driver";
static i2c_expander_handle_t *py32_handle = NULL;

/**
 * @brief 初始化PY32驱动
 */
// 打印所有引脚状态的辅助函数
static void print_all_pin_states(const char *stage)
{
    if (py32_handle == NULL) {
        ESP_LOGI(TAG, "[%s] PY32句柄未初始化", stage);
        return;
    }
    
    ESP_LOGI(TAG, "=== [%s] PY32所有引脚状态 ===", stage);
    
    // 读取所有相关寄存器
    uint16_t gpio_mode, gpio_output, gpio_input, gpio_pu, gpio_pd, gpio_drive;
    esp_err_t ret;
    
    ret = i2c_expander_gpio_get_mode_reg(py32_handle, &gpio_mode);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "GPIO模式寄存器: 0x%04X", gpio_mode);
    }
    
    ret = i2c_expander_gpio_get_output_reg(py32_handle, &gpio_output);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "GPIO输出寄存器: 0x%04X", gpio_output);
    }
    
    ret = i2c_expander_gpio_get_input_reg(py32_handle, &gpio_input);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "GPIO输入寄存器: 0x%04X", gpio_input);
    }
    
    ret = i2c_expander_gpio_get_pull_up_reg(py32_handle, &gpio_pu);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "GPIO上拉寄存器: 0x%04X", gpio_pu);
    }
    
    ret = i2c_expander_gpio_get_pull_down_reg(py32_handle, &gpio_pd);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "GPIO下拉寄存器: 0x%04X", gpio_pd);
    }
    
    ret = i2c_expander_gpio_get_drive_reg(py32_handle, &gpio_drive);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "GPIO驱动寄存器: 0x%04X", gpio_drive);
    }
    
    // 打印每个引脚的状态
    const char* pin_names[] = {
        "TP_RST", "SPK_EN", "MUX_CTR", "GROVE_DIR", "VIN_DET", 
        "OLED_RST", "GPIO7", "GPIO8", "GROVE_VOUT_EN", "MOTOR_EN",
        "GPIO11", "GPIO12", "GPIO13", "GPIO14"
    };
    
    for (int i = 0; i < 14; i++) {
        bool is_output = (gpio_mode & (1 << i)) != 0;
        bool output_level = (gpio_output & (1 << i)) != 0;
        bool input_level = (gpio_input & (1 << i)) != 0;
        bool pull_up = (gpio_pu & (1 << i)) != 0;
        bool pull_down = (gpio_pd & (1 << i)) != 0;
        bool open_drain = (gpio_drive & (1 << i)) != 0;
        
        const char* mode_str = is_output ? "OUT" : "IN";
        const char* drive_str = open_drain ? "OD" : "PP";
        const char* pull_str = pull_up ? "UP" : (pull_down ? "DOWN" : "NONE");
        const char* level_str = is_output ? (output_level ? "HIGH" : "LOW") : (input_level ? "HIGH" : "LOW");
        
        ESP_LOGI(TAG, "GPIO%d(%s): %s %s %s %s", 
                 i, pin_names[i], mode_str, drive_str, pull_str, level_str);
    }
    
    ESP_LOGI(TAG, "=== [%s] 状态打印完成 ===", stage);
}

esp_err_t py32_init(i2c_bus_handle_t i2c_bus)
{
    ESP_LOGI(TAG, "初始化PY32驱动");

    // 配置I2C扩展器
    i2c_expander_config_t config = {.i2c_port       = I2C_NUM_0,  // 从i2c_bus获取端口号
                                    .device_address = I2C_EXPANDER_ADDR,
                                    .timeout_ms     = 1000};

    esp_err_t ret = i2c_expander_init(&config, &py32_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C扩展器初始化失败: %s", esp_err_to_name(ret));
        return ret;
    }
    
    // 打印初始化前的引脚状态
    print_all_pin_states("初始化前");

    // 配置引脚模式
    // 输出引脚
    i2c_expander_gpio_set_mode(py32_handle, PY32_TP_RST_PIN, I2C_EXP_GPIO_MODE_OUTPUT);
    i2c_expander_gpio_set_mode(py32_handle, PY32_SPK_EN_PIN, I2C_EXP_GPIO_MODE_OUTPUT);
    i2c_expander_gpio_set_mode(py32_handle, PY32_MUX_CTR_PIN, I2C_EXP_GPIO_MODE_OUTPUT);
    i2c_expander_gpio_set_mode(py32_handle, PY32_GROVE_DIR_PIN, I2C_EXP_GPIO_MODE_OUTPUT);
    i2c_expander_gpio_set_mode(py32_handle, PY32_OLED_RST_PIN, I2C_EXP_GPIO_MODE_OUTPUT);
    i2c_expander_gpio_set_mode(py32_handle, PY32_GROVE_VOUT_EN_PIN, I2C_EXP_GPIO_MODE_OUTPUT);
    // 注意：MOTOR_EN_PIN 使用PWM功能时不需要设置GPIO模式

    // 输入引脚
    i2c_expander_gpio_set_mode(py32_handle, PY32_VIN_DET_PIN, I2C_EXP_GPIO_MODE_INPUT);
    i2c_expander_gpio_set_pull(py32_handle, PY32_VIN_DET_PIN, I2C_EXP_GPIO_PULL_DOWN);

    // 设置输出引脚驱动模式
    i2c_expander_gpio_set_drive(py32_handle, PY32_TP_RST_PIN, I2C_EXP_GPIO_DRIVE_PUSH_PULL);
    i2c_expander_gpio_set_drive(py32_handle, PY32_SPK_EN_PIN, I2C_EXP_GPIO_DRIVE_PUSH_PULL);
    i2c_expander_gpio_set_drive(py32_handle, PY32_MUX_CTR_PIN, I2C_EXP_GPIO_DRIVE_PUSH_PULL);
    i2c_expander_gpio_set_drive(py32_handle, PY32_GROVE_DIR_PIN, I2C_EXP_GPIO_DRIVE_PUSH_PULL);
    i2c_expander_gpio_set_drive(py32_handle, PY32_OLED_RST_PIN, I2C_EXP_GPIO_DRIVE_PUSH_PULL);
    i2c_expander_gpio_set_drive(py32_handle, PY32_GROVE_VOUT_EN_PIN, I2C_EXP_GPIO_DRIVE_PUSH_PULL);

    // 初始化引脚状态
    i2c_expander_gpio_set_level(py32_handle, PY32_TP_RST_PIN, 1);         // 触摸不复位
    i2c_expander_gpio_set_level(py32_handle, PY32_SPK_EN_PIN, 1);         // 扬声器默认禁用
    i2c_expander_gpio_set_level(py32_handle, PY32_MUX_CTR_PIN, 0);        // 默认连接U0串口
    i2c_expander_gpio_set_level(py32_handle, PY32_GROVE_DIR_PIN, 0);      // GROVE默认输入模式
    i2c_expander_gpio_set_level(py32_handle, PY32_OLED_RST_PIN, 1);       // OLED不复位
    i2c_expander_gpio_set_level(py32_handle, PY32_GROVE_VOUT_EN_PIN, 0);  // GROVE 5V输出默认禁用

    // 设置PWM频率为5KHz
    i2c_expander_pwm_set_frequency(py32_handle, (uint16_t)5000);
    i2c_expander_gpio_set_drive(py32_handle, PY32_MOTOR_EN_PIN, I2C_EXP_GPIO_DRIVE_PUSH_PULL); // 电机PWM输出引脚需要设置为推挽输出

    // 禁用电机PWM
    i2c_expander_pwm_set_duty(py32_handle, PY32_MOTOR_PWM_CHANNEL, 0, false, true);

    i2c_expander_set_i2c_config(py32_handle, 0, false);

    // 打印初始化后的引脚状态
    print_all_pin_states("初始化后");
    
    ESP_LOGI(TAG, "PY32驱动初始化完成");
    uint16_t voltage = 0;
    i2c_expander_get_ref_voltage(py32_handle, &voltage);
    ESP_LOGI(TAG, "参考电压: %d", voltage);
    uint16_t temp = 0;
    i2c_expander_temp_read(py32_handle, &temp);
    ESP_LOGI(TAG, "温度: %d", temp);
    return ESP_OK;
}

/**
 * @brief 反初始化PY32驱动
 */
esp_err_t py32_deinit(void)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = i2c_expander_deinit(py32_handle);
    py32_handle   = NULL;

    ESP_LOGI(TAG, "PY32驱动反初始化完成");
    return ret;
}

/**
 * @brief 复位触摸屏
 */
esp_err_t py32_tp_reset(void)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "复位触摸屏");

    // 拉低复位引脚
    esp_err_t ret = i2c_expander_gpio_set_level(py32_handle, PY32_TP_RST_PIN, 0);
    if (ret != ESP_OK) return ret;

    vTaskDelay(pdMS_TO_TICKS(10));  // 延时10ms

    // 拉高复位引脚
    ret = i2c_expander_gpio_set_level(py32_handle, PY32_TP_RST_PIN, 1);
    if (ret != ESP_OK) return ret;

    vTaskDelay(pdMS_TO_TICKS(50));  // 延时50ms等待复位完成

    return ESP_OK;
}

/**
 * @brief 启用扬声器
 */
esp_err_t py32_speaker_enable(void)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "启用扬声器");
    return i2c_expander_gpio_set_level(py32_handle, PY32_SPK_EN_PIN, 1);
}

/**
 * @brief 禁用扬声器
 */
esp_err_t py32_speaker_disable(void)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "禁用扬声器");
    return i2c_expander_gpio_set_level(py32_handle, PY32_SPK_EN_PIN, 0);
}

/**
 * @brief 复位OLED/LCD显示屏
 */
esp_err_t py32_lcd_reset(void)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "复位LCD/OLED显示屏");

    // 拉低复位引脚
    esp_err_t ret = i2c_expander_gpio_set_level(py32_handle, PY32_OLED_RST_PIN, 0);
    if (ret != ESP_OK) return ret;

    vTaskDelay(pdMS_TO_TICKS(10));  // 延时10ms

    // 拉高复位引脚
    ret = i2c_expander_gpio_set_level(py32_handle, PY32_OLED_RST_PIN, 1);
    if (ret != ESP_OK) return ret;

    vTaskDelay(pdMS_TO_TICKS(50));  // 延时50ms等待复位完成

    return ESP_OK;
}

/**
 * @brief 检测输入电压
 */
esp_err_t py32_vin_detect(bool *detected)
{
    if (py32_handle == NULL || detected == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t level;
    esp_err_t ret = i2c_expander_gpio_get_level(py32_handle, PY32_VIN_DET_PIN, &level);
    if (ret == ESP_OK) {
        *detected = (level == 1);
        ESP_LOGD(TAG, "电压检测: %s", *detected ? "检测到" : "未检测到");
    }

    return ret;
}

/**
 * @brief 启用GROVE 5V输出
 */
esp_err_t py32_grove_5v_enable(void)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "启用GROVE 5V输出");
    return i2c_expander_gpio_set_level(py32_handle, PY32_GROVE_VOUT_EN_PIN, 1);
}

/**
 * @brief 禁用GROVE 5V输出
 */
esp_err_t py32_grove_5v_disable(void)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "禁用GROVE 5V输出");
    return i2c_expander_gpio_set_level(py32_handle, PY32_GROVE_VOUT_EN_PIN, 0);
}

/**
 * @brief 设置GROVE接口模式
 */
esp_err_t py32_grove_set_mode(py32_grove_mode_t mode)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "设置GROVE接口模式: %s", (mode == PY32_GROVE_MODE_INPUT) ? "输入" : "输出");

    // 0: 输入模式, 1: 输出模式
    uint8_t level = (mode == PY32_GROVE_MODE_OUTPUT) ? 1 : 0;
    return i2c_expander_gpio_set_level(py32_handle, PY32_GROVE_DIR_PIN, level);
}

/**
 * @brief 获取GROVE接口当前模式
 */
esp_err_t py32_grove_get_mode(py32_grove_mode_t *mode)
{
    if (py32_handle == NULL || mode == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t level;
    esp_err_t ret = i2c_expander_gpio_get_level(py32_handle, PY32_GROVE_DIR_PIN, &level);
    if (ret == ESP_OK) {
        *mode = (level == 1) ? PY32_GROVE_MODE_OUTPUT : PY32_GROVE_MODE_INPUT;
        ESP_LOGD(TAG, "当前GROVE接口模式: %s", (*mode == PY32_GROVE_MODE_INPUT) ? "输入" : "输出");
    }

    return ret;
}

/**
 * @brief 设置CH442E MUX模式
 */
esp_err_t py32_mux_set_mode(py32_mux_mode_t mode)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "设置MUX模式: %s", (mode == PY32_MUX_MODE_U0) ? "U0串口" : "USB");

    // 0: 连接U0串口, 1: 连接USB
    uint8_t level = (mode == PY32_MUX_MODE_USB) ? 1 : 0;
    return i2c_expander_gpio_set_level(py32_handle, PY32_MUX_CTR_PIN, level);
}

/**
 * @brief 获取CH442E MUX当前模式
 */
esp_err_t py32_mux_get_mode(py32_mux_mode_t *mode)
{
    if (py32_handle == NULL || mode == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t level;
    esp_err_t ret = i2c_expander_gpio_get_level(py32_handle, PY32_MUX_CTR_PIN, &level);
    if (ret == ESP_OK) {
        *mode = (level == 1) ? PY32_MUX_MODE_USB : PY32_MUX_MODE_U0;
        ESP_LOGD(TAG, "当前MUX模式: %s", (*mode == PY32_MUX_MODE_U0) ? "U0串口" : "USB");
    }

    return ret;
}

/**
 * @brief 设置电机PWM占空比
 */
esp_err_t py32_motor_set_pwm(uint8_t duty_percent)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    if (duty_percent > 100) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "设置电机PWM占空比: %d%%", duty_percent);

    // 设置PWM占空比，高电平有效，使能PWM
    bool enable = (duty_percent > 0);
    esp_err_t ret = i2c_expander_pwm_set_duty(py32_handle, PY32_MOTOR_PWM_CHANNEL, duty_percent, false, enable);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "设置电机PWM占空比失败: %s", esp_err_to_name(ret));
        return ret;
    }

    // 回读校验
    uint8_t read_duty;
    bool read_polarity, read_enable;
    ret = i2c_expander_pwm_get_duty(py32_handle, PY32_MOTOR_PWM_CHANNEL, &read_duty, &read_polarity, &read_enable);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "回读电机PWM占空比失败: %s", esp_err_to_name(ret));
        return ret;
    }

    // 检查设置是否成功
    if (!(read_duty <= duty_percent+1 && read_duty >= duty_percent-1) || read_polarity != false || read_enable != enable) {
        ESP_LOGE(TAG, "电机PWM设置校验失败: 期望占空比=%d%%, 实际=%d%%; 期望极性=%s, 实际=%s; 期望使能=%s, 实际=%s",
                 duty_percent, read_duty,
                 "高电平有效", read_polarity ? "低电平有效" : "高电平有效",
                 enable ? "是" : "否", read_enable ? "是" : "否");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "电机PWM占空比设置成功，校验通过: %d%%", read_duty);
    return ESP_OK;
}

/**
 * @brief 启用电机
 */
esp_err_t py32_motor_enable(uint8_t duty_percent)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    if (duty_percent > 100) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "启用电机，PWM占空比: %d%%", duty_percent);

    // 设置PWM占空比并启用
    esp_err_t ret = i2c_expander_pwm_set_duty(py32_handle, PY32_MOTOR_PWM_CHANNEL, duty_percent, false, true);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "启用电机失败: %s", esp_err_to_name(ret));
        return ret;
    }

    // 回读校验
    uint8_t read_duty;
    bool read_polarity, read_enable;
    ret = i2c_expander_pwm_get_duty(py32_handle, PY32_MOTOR_PWM_CHANNEL, &read_duty, &read_polarity, &read_enable);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "回读电机PWM状态失败: %s", esp_err_to_name(ret));
        return ret;
    }

    // 检查设置是否成功
    if (!(read_duty <= duty_percent+1 && read_duty >= duty_percent-1) || read_polarity != false || read_enable != true) {
        ESP_LOGE(TAG, "电机启用校验失败: 期望占空比=%d%%, 实际=%d%%; 期望极性=%s, 实际=%s; 期望使能=%s, 实际=%s",
                 duty_percent, read_duty,
                 "高电平有效", read_polarity ? "低电平有效" : "高电平有效",
                 "是", read_enable ? "是" : "否");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "电机启用成功，校验通过: 占空比=%d%%, 使能=%s", read_duty, read_enable ? "是" : "否");
    return ESP_OK;
}

/**
 * @brief 禁用电机
 */
esp_err_t py32_motor_disable(void)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "禁用电机");

    // 设置PWM占空比为0并禁用
    esp_err_t ret = i2c_expander_pwm_set_duty(py32_handle, PY32_MOTOR_PWM_CHANNEL, 0, false, false);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "禁用电机失败: %s", esp_err_to_name(ret));
        return ret;
    }

    // 回读校验
    uint8_t read_duty;
    bool read_polarity, read_enable;
    ret = i2c_expander_pwm_get_duty(py32_handle, PY32_MOTOR_PWM_CHANNEL, &read_duty, &read_polarity, &read_enable);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "回读电机PWM状态失败: %s", esp_err_to_name(ret));
        return ret;
    }

    // 检查设置是否成功
    if (read_duty != 0 || read_polarity != false || read_enable != false) {
        ESP_LOGE(TAG, "电机禁用校验失败: 期望占空比=0%%, 实际=%d%%; 期望极性=%s, 实际=%s; 期望使能=%s, 实际=%s",
                 read_duty,
                 "高电平有效", read_polarity ? "低电平有效" : "高电平有效",
                 "否", read_enable ? "是" : "否");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "电机禁用成功，校验通过: 占空比=%d%%, 使能=%s", read_duty, read_enable ? "是" : "否");
    return ESP_OK;
}

/**
 * @brief 设置电机PWM频率
 */
esp_err_t py32_motor_set_frequency(uint16_t frequency)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "设置电机PWM频率: %d Hz", frequency);
    
    esp_err_t ret = i2c_expander_pwm_set_frequency(py32_handle, frequency);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "设置电机PWM频率失败: %s", esp_err_to_name(ret));
        return ret;
    }

    // 回读校验
    uint16_t read_frequency;
    ret = i2c_expander_pwm_get_frequency(py32_handle, &read_frequency);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "回读电机PWM频率失败: %s", esp_err_to_name(ret));
        return ret;
    }

    // 检查设置是否成功
    if (read_frequency != frequency) {
        ESP_LOGE(TAG, "电机PWM频率设置校验失败: 期望=%d Hz, 实际=%d Hz", frequency, read_frequency);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "电机PWM频率设置成功，校验通过: %d Hz", read_frequency);
    return ESP_OK;
}

/**
 * @brief 获取电机PWM频率
 */
esp_err_t py32_motor_get_frequency(uint16_t *frequency)
{
    if (py32_handle == NULL || frequency == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret = i2c_expander_pwm_get_frequency(py32_handle, frequency);
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "当前电机PWM频率: %d Hz", *frequency);
    }
    return ret;
}

/**
 * @brief 获取电机PWM占空比
 */
esp_err_t py32_motor_get_pwm(uint8_t *duty_percent, bool *polarity, bool *enable)
{
    if (py32_handle == NULL || duty_percent == NULL || polarity == NULL || enable == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret = i2c_expander_pwm_get_duty(py32_handle, PY32_MOTOR_PWM_CHANNEL, duty_percent, polarity, enable);
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "电机PWM状态: 占空比=%d%%, 极性=%s, 使能=%s", 
                 *duty_percent, *polarity ? "低电平有效" : "高电平有效", *enable ? "是" : "否");
    }
    return ret;
}

/**
 * @brief 设置PY32睡眠模式
 */
esp_err_t py32_sleep(uint8_t sleep_mode)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "设置睡眠模式: %d", sleep_mode);

    // 根据睡眠模式设置I2C扩展器配置
    // sleep_mode: 0=不休眠, 1-15=休眠时间
    uint8_t sleep_time = (sleep_mode > 0) ? sleep_mode : 0;

    return i2c_expander_set_i2c_config(py32_handle, sleep_time, true);
}

/**
 * @brief 释放所有引脚到默认状态
 */
esp_err_t py32_release_all(void)
{
    if (py32_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "释放所有引脚到默认状态");

    esp_err_t ret = ESP_OK;

    // 设置所有输出引脚为低电平
    ret |= i2c_expander_gpio_set_level(py32_handle, PY32_TP_RST_PIN, 0);
    ret |= i2c_expander_gpio_set_level(py32_handle, PY32_SPK_EN_PIN, 0);
    ret |= i2c_expander_gpio_set_level(py32_handle, PY32_MUX_CTR_PIN, 0);    // 默认连接U0串口
    ret |= i2c_expander_gpio_set_level(py32_handle, PY32_GROVE_DIR_PIN, 0);  // GROVE默认输入模式
    ret |= i2c_expander_gpio_set_level(py32_handle, PY32_OLED_RST_PIN, 0);
    ret |= i2c_expander_gpio_set_level(py32_handle, PY32_GROVE_VOUT_EN_PIN, 0);  // 禁用GROVE 5V输出

    // 禁用PWM
    ret |= i2c_expander_pwm_set_duty(py32_handle, PY32_MOTOR_PWM_CHANNEL, 0, false, false);

    return ret;
}