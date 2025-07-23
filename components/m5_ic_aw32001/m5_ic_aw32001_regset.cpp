/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include "m5_ic_aw32001.h"


// 配置输入电压阈值（VIN_DPM）
// INPUT: uint16_t vin_dpm_value: 输入电压阈值 (3880-5080V,步进80mV,默认4520mV)
// RETURN: esp_err_t: 错误码
// REG: 00H[7:4]-(VIN_DPM)
// 注明1：该值是芯片的输入电压阈值，低于该值时，芯片会降低电流以防止输入源过载
esp_err_t m5_ic_aw32001::set_vin_dpm_value(uint16_t vin_dpm_value) 
{
    if (vin_dpm_value < 3880 || vin_dpm_value > 5080) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid input voltage: %d mV, valid range is 3880-5080mV", vin_dpm_value);
        return ESP_ERR_INVALID_ARG;
    }
    uint8_t step = (uint8_t)round((vin_dpm_value - 3880) / 80.0f);
    if (step > 0x0F) step = 0x0F;
    
    esp_err_t ret = write_reg_bits(AWREG_INPUT_SOURCE_CONTROL, 0xF0, (step << 4));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write VIN_DPM bits to AWREG_INPUT_SOURCE_CONTROL");
        return ret;
    }
    uint16_t actual_vin_dpm = 3880 + step * 80;
    ESP_LOGI(_m5_io_aw32001_TAG, "Input voltage limit set to %d mV (step: %d, bits: 0b%s)", actual_vin_dpm, step, UINT8_TO_BINARY_STRING(step,4));
    return ESP_OK;
}

// 配置输入电流阈值（IIN_LIM）
// INPUT: uint16_t current_ma: 输入电流阈值 (50-500mA, 步进30mA, 默认500mA)
// RETURN: esp_err_t: 错误码
// REG: 00H[3:0]-(IIN_LIM)
// 注明1：该值是芯片的输入电流阈值，高于该值时，芯片会降低电流以防止输入源过载
esp_err_t m5_ic_aw32001::set_iin_lim_value(uint16_t current_ma) 
{
    if (current_ma < 50 || current_ma > 500) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid input current: %d mA, valid range is 50-500mA", current_ma);
        return ESP_ERR_INVALID_ARG;
    }
    // 四舍五入
    uint8_t step = (uint8_t)((current_ma - 50 + 15) / 30);
    if (step > 0x0F) step = 0x0F;
    
    esp_err_t ret = write_reg_bits(AWREG_INPUT_SOURCE_CONTROL, 0x0F, step);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write IIN_LIM bits to AWREG_INPUT_SOURCE_CONTROL");
        return ret;
    }
    uint16_t actual_current = 50 + step * 30;
    ESP_LOGI(_m5_io_aw32001_TAG, "Input current limit set to %d mA (step: %d, bits: 0b%s)", actual_current, step, UINT8_TO_BINARY_STRING(step,4));
    return ESP_OK;
}

// 配置INT长时间拉低以复位系统的所需拉低时间（RST_DGL）
// INPUT: uint16_t rst_dgl_time: INT引脚拉低时间 (8-20s, 步进2s, 默认16s)
// RETURN: esp_err_t: 错误码
// REG: 01H[7:6]-(RST_DGL)
esp_err_t m5_ic_aw32001::set_rst_dgl_time(uint16_t rst_dgl_time) 
{
    if (rst_dgl_time < 8 || rst_dgl_time > 20) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid reset duration: %d s, valid range is 8-20s", rst_dgl_time);
        return ESP_ERR_INVALID_ARG;
    }
    uint8_t step = (uint8_t)round((rst_dgl_time - 8) / 2.0f);
    if (step > 0x03) step = 0x03;
    
    esp_err_t ret = write_reg_bits(AWREG_POWER_ON_CONFIGURATION, 0xC0, (step << 6));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write RST_DGL bits to AWREG_POWER_ON_CONFIGURATION");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "Reset duration set to %d s (step: %d, bits: 0b%s)", rst_dgl_time, step, UINT8_TO_BINARY_STRING(step,2));
    return ESP_OK;
}

// 配置INT长时间拉低以复位系统的持续时间（或看门狗复位）
// INPUT: uint16_t int_down_time: INT引脚拉低时间 (2, 4s, 默认4s)
// RETURN: esp_err_t: 错误码
// REG: 01H[5]-(INT_DOWN_TIME)
esp_err_t m5_ic_aw32001::set_rst_dur_time(uint16_t int_down_time) 
{
    uint8_t bit_val = 0;
    switch (int_down_time) {
        case 2: bit_val = 0; break;
        case 4: bit_val = 1; break;
        default:
            ESP_LOGE(_m5_io_aw32001_TAG, "Invalid int_down_time value, using default (2s)");
            bit_val = 0;
            break;
    }
    
    esp_err_t ret = write_reg_bits(AWREG_POWER_ON_CONFIGURATION, 0x20, (bit_val << 5));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write INT_DOWN_TIME bit to AWREG_POWER_ON_CONFIGURATION");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "INT down time set to %d s (bit: %d)", int_down_time, bit_val);
    return ESP_OK;
}

// 寄存器命令 启用高阻态（EN_HIZ）
// INPUT: bool enable: 是否启用高阻态 0: 关闭（默认） 1: 启用
// RETURN: esp_err_t: 错误码
// REG: 01H[4]-(EN_HIZ)
esp_err_t m5_ic_aw32001::set_enable_hiz(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_POWER_ON_CONFIGURATION, 0x10, (enable ? 0x10 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EN_HIZ bit to AWREG_POWER_ON_CONFIGURATION");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s high impedance mode", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 寄存器命令 启用充电（CEB）
// INPUT: bool enable: 是否启用充电 0: 启用 1: 禁用（默认）
// RETURN: esp_err_t: 错误码
// REG: 01H[3]-(CEB)
esp_err_t m5_ic_aw32001::set_enable_charge(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_POWER_ON_CONFIGURATION, 0x08, (enable ? 0x00 : 0x08));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write CEB bit to AWREG_POWER_ON_CONFIGURATION");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s charging", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 配置电池电压过低阈值（VBAT_UVLO）
// INPUT: uint16 vbat_uvlo: 电池电压阈值 (2430-3030mV, 步进60mV, 默认2760mV)
// RETURN: esp_err_t: 错误码
// REG: 01H[2:0]-(VBAT_UVLO)
// 注明1：该值是电池电压过低阈值，低于将断开电池供电，若有USB供电则从USB取电
// 注明2：低于该值后，电池需要恢复到该值+190mV后，才会允许电池供电
esp_err_t m5_ic_aw32001::set_vbat_uvlo_value(uint16_t vbat_uvlo) 
{
    if (vbat_uvlo < 2430 || vbat_uvlo > 3030) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid battery voltage threshold: %d mV, valid range is 2430-3030mV", vbat_uvlo);
        return ESP_ERR_INVALID_ARG;
    }
    uint8_t step = (uint8_t)((vbat_uvlo - 2430 + 30) / 60); // 四舍五入
    if (step > 0x07) step = 0x07;
    
    esp_err_t ret = write_reg_bits(AWREG_POWER_ON_CONFIGURATION, 0x07, step);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write VBAT_UVLO bits to AWREG_POWER_ON_CONFIGURATION");
        return ret;
    }
    uint16_t actual_vbat_uvlo = 2430 + step * 60;
    uint16_t recovery_threshold = actual_vbat_uvlo + 190;
    ESP_LOGI(_m5_io_aw32001_TAG, "Battery voltage threshold set to %d mV (recovery at %d mV, step: %d, bits: 0b%s)", actual_vbat_uvlo, recovery_threshold, step, UINT8_TO_BINARY_STRING(step,3));
    return ESP_OK;
}

// 寄存器命令 芯片寄存器复位（REG_RST）
// INPUT: none
// RETURN: esp_err_t: 错误码
// REG: 02H[7]-(REG_RST) = 0: 保持现状 (1: 复位寄存器状态)
esp_err_t m5_ic_aw32001::set_register_reset(void) 
{
    esp_err_t ret = write_reg_bits(AWREG_CHARGE_CURRENT_CONTROL, 0x80, 0x80);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write REG_RST bit to AWREG_CHARGE_CURRENT_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "Resetting registers");
    return ESP_OK;
}

// 寄存器命令 复位看门狗计数器
// INPUT: none
// RETURN: esp_err_t: 错误码
// REG: 02H[6]-(WD_TMR_RST) = 0: 保持现状 (1: 复位看门狗计数器)
// 注明1：若芯片处于主机模式且未将看门狗计时器超时置为0，则必须调用该函数以防止看门狗复位
esp_err_t m5_ic_aw32001::set_reset_watchdog(void) {
    
    esp_err_t ret = write_reg_bits(AWREG_CHARGE_CURRENT_CONTROL, 0x40, 0x40);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write WD_TMR_RST bit to AWREG_CHARGE_CURRENT_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "Watchdog timer reset");
    return ESP_OK;
}

// 配置电池充电电流值（ICHG）
// INPUT: uint16_t ichg_value: 充电电流值 (8-512mA, 步进8mA , 默认128mA) 
// RETURN: esp_err_t: 错误码
// REG: 02H[5:0](ICHG)
// 注明1：当设置电流大于456mA时，必须打开REG0CH[7]:ENOP55,
//       并将IIN_LIM设置为0b1111，此时输入负载电流限制将达到550mA
// 注明2：本函数将自动修改IIN_LIM、ENOP55的值以适配充电电流值
esp_err_t m5_ic_aw32001::set_charge_current_value(uint16_t ichg_value)
{
    esp_err_t ret;
    if (ichg_value < 8 || ichg_value > 512) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid charge current: %d mA (valid 8-512mA)", ichg_value);
        return ESP_ERR_INVALID_ARG;
    }
    
    if (ichg_value < 456) {
        ret = set_iin_lim_value((float)ichg_value + 30);
    } else {
        ret = set_iin_lim_value(500.0f);
        // 设置 ENOP55 位 (REG0CH[7]) 为 1
        ret = write_reg_bits(AWREG_ADDITIONAL_FUNCTION_CONTROL1, 0x80, 0x80);
        if (ret != ESP_OK) {
            ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write ENOP55 bit to AWREG_ADDITIONAL_FUNCTION_CONTROL1");
            return ret;
        }
        ESP_LOGI(_m5_io_aw32001_TAG, "ENOP55 enabled for charge current > 456mA, IIN_LIM -> 550mA");
    }
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "set_iin_lim_value failed");
        return ret;
    }
    // step 范围 1~64, 寄存器值 0~63
    uint8_t step = (uint8_t)((ichg_value + 7) / 8);
    if (step == 0) step = 1;
    if (step > 64) step = 64;
    uint8_t ichg_bits = step - 1;
    
    ret = write_reg_bits(AWREG_CHARGE_CURRENT_CONTROL, 0x3F, ichg_bits);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write ICHG bits to AWREG_CHARGE_CURRENT_CONTROL");
        return ret;
    }
    float actual_current = (ichg_bits + 1) * 8.0f;
    ESP_LOGI(_m5_io_aw32001_TAG, "Charge current set to %.0f mA (step: %d, bits: 0b%s, ENOP55=%d)", actual_current, step, UINT8_TO_BINARY_STRING(ichg_bits,6), (ichg_value >= 456) ? 1 : 0);
    return ESP_OK;
}

// 配置电池放电电流阈值（IDSCHG）
// INPUT: uint16_t idschg_value: 放电电流值 (200-3200mA，步进200mA, 默认2000mA)
// RETURN: esp_err_t: 错误码
// REG: 03H[7:4]-(IDSCHG)
// 说明：当系统电压低于电池电压30mV，将进入电池补充模式，其补充电流为IDSCHG值
esp_err_t m5_ic_aw32001::set_discharge_current_value(uint16_t idschg_value)
{
    if (idschg_value < 200 || idschg_value > 3200) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid discharge current: %d mA (valid 200-3200mA)", idschg_value);
        return ESP_ERR_INVALID_ARG;
    }
    // 计算代码值（4位，步进200mA）
    uint8_t code = (uint8_t)round((idschg_value - 200) / 200.0f);
    if (code > 0x0F) code = 0x0F;

    // 直接用write_reg_bits写入高4位
    esp_err_t ret = write_reg_bits(AWREG_DISCHARGE_CURRENT_CONTROL, 0x0F, (code << 4));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write IDSCHG bits to AWREG_DISCHARGE_CURRENT_CONTROL");
        return ret;
    }

    // 计算实际设置值
    uint16_t actual_current = 200 + code * 200;
    ESP_LOGI(_m5_io_aw32001_TAG, "Discharge current set to %d mA (step: %d, bits: 0b%s)", actual_current, code, UINT8_TO_BINARY_STRING(code,4));

    return ESP_OK;
}

// 配置充电终止电流值（ITERM）
// INPUT: uint16_t iterm_value:终止电流值 (1-31mA，步进2mA，默认3mA)
// RETURN: esp_err_t: 错误码
// REG: 03H[3:0]-(VBAT_REG)
// 注明1：当充电电流小于ITERM值时，芯片将进入涓流充电模式，持续3.2S后，充电结束
// 注明2：当 0BH[5]-(EN_IPRE_SET) = 0 时，该值（ITERM）也是预充电电流值
// 注明3：当 0CH[6]-(ITERMDEG) = 1 时，持续时间由3秒改为1秒，默认3秒
esp_err_t m5_ic_aw32001::set_termination_current_value(uint16_t iterm_value)
{
    if (iterm_value < 1 || iterm_value > 31) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid termination current: %d mA (valid 1-31mA)", iterm_value);
        return ESP_ERR_INVALID_ARG;
    }

    // 计算代码值
    uint8_t code = (uint8_t)round((iterm_value - 1) / 2.0f);
    if (code > 0x0F) code = 0x0F; // 4位

    // 覆盖寄存器的指定位
    write_reg_bits(AWREG_DISCHARGE_CURRENT_CONTROL, 0xF0, (code << 0));

    // 计算实际设置值
    uint16_t actual_current = 1 + code * 2;
    ESP_LOGI(_m5_io_aw32001_TAG, "Termination current set to %d mA (step: %d, bits: 0b%s)", actual_current, code, UINT8_TO_BINARY_STRING(code,4));

    return ESP_OK;
}

// 配置电池充电电压值（VBAT_REG）
// INPUT: uint16_t vbat_value: 充电电压值 (3600-4545mV，步进15mV,默认4200mV)
// RETURN: esp_err_t: 错误码
// REG: 04H[7:2]-(VBAT_REG)
// 注明1：当实际电压大于设置值+130mV时，停止充电，直到电池电压低于设置值+50mV以下
esp_err_t m5_ic_aw32001::set_charge_voltage_value(uint16_t vbat_value)
{
    if (vbat_value < 3600 || vbat_value > 4545) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid charge voltage: %d mV (valid 3600-4950mV)", vbat_value);
        return ESP_ERR_INVALID_ARG;
    }

    // 计算代码值
    uint8_t step = (uint8_t)round((vbat_value - 3600) / 15.0f); // 6位，步进50mV
    if (step > 0x3F) step = 0x3F; // 限制在6位范围内

    // 覆盖寄存器的指定位
    write_reg_bits(AWREG_CHARGE_VOLTAGE, 0xFC, (step << 2));

    // 计算实际设置值
    uint16_t actual_voltage = 3600 + step * 15;
    ESP_LOGI(_m5_io_aw32001_TAG, "Charge voltage set to %d mV (step: %d, bits: 0b%s)", actual_voltage, step, UINT8_TO_BINARY_STRING(step,6));

    return ESP_OK;
}


// 配置电池预充电电压阈值（VBAT_PRE）
// INPUT: uint16_t vbat_pre_value: 预充电电压值 (2800，3000mV，默认3000mV)
// RETURN: esp_err_t: 错误码
// REG: 04H[1]-(VBAT_PRE)
// 注明1：当电池电压低于该值-200mV时，芯片将从快速充电进入预充电模式
esp_err_t m5_ic_aw32001::set_precharge_voltage_value(uint16_t vbat_pre_value)
{
    if (vbat_pre_value != 2800 && vbat_pre_value != 3000) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid precharge voltage: %d mV (valid 2800-3000mV)", vbat_pre_value);
        return ESP_ERR_INVALID_ARG;
    }

    // 计算寄存器代码值
    uint8_t step_code = (uint8_t)((vbat_pre_value == 2800) ? 0 : 1); // 1位

    // 覆盖寄存器的指定位
    write_reg_bits(AWREG_CHARGE_VOLTAGE, 0x02, (step_code << 1));

    // 计算实际设置值
    uint16_t actual_voltage = (step_code == 0) ? 2800 : 3000;
    ESP_LOGI(_m5_io_aw32001_TAG, "Precharge voltage set to %d mV (step: %d, bits: 0b%s)", actual_voltage, step_code, UINT8_TO_BINARY_STRING(step_code,1));

    return ESP_OK;
}

// 配置再充电电压阈值（VRECH）
// INPUT: uint16_t vrech_value: 再充电电压值 (100，200mV，默认200mV)
// RETURN: esp_err_t: 错误码
// REG: 04H[0]-(VRECH)
// 注明1：电池充电完成后，当自放电达到-VRECH值时，芯片将重新开始充电
esp_err_t m5_ic_aw32001::set_recharge_voltage_value(uint16_t vrech_value)
{
    if (vrech_value != 100 && vrech_value != 200) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid recharge voltage: %d mV (valid 100-200mV)", vrech_value);
        return ESP_ERR_INVALID_ARG;
    }

    // 计算寄存器代码值
    uint8_t step_code = (uint8_t)((vrech_value == 100) ? 0 : 1); // 1位

    // 覆盖寄存器的指定位
    write_reg_bits(AWREG_CHARGE_VOLTAGE, 0x01, step_code);

    // 计算实际设置值
    uint16_t actual_voltage = (step_code == 0) ? 100 : 200;
    ESP_LOGI(_m5_io_aw32001_TAG, "Recharge voltage set to %d mV (step: %d, bits: 0b%s)", actual_voltage, step_code, UINT8_TO_BINARY_STRING(step_code,1));

    return ESP_OK;
}

// 放电模式看门狗相关使能 (EN_WD_DISCHG)
// INPUT: bool enable: 是否启用看门狗 0: 禁用 (默认), 1: 启用
// RETURN: esp_err_t: 错误码
// REG: 05H[7]-(EN_WD_DISCHG)
// 注明1：该WDT指的是EN_WD_DISCHG所控制的放电模式看门狗（默认禁用）
// 注明2：当enable=0，将把看门狗超时时间设置为0，表示禁用全局看门狗
esp_err_t m5_ic_aw32001::set_dischg_watchdog_enable(bool enable) {
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_CHARGE_TERMINATION_TIMER_CONTROL, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read AWREG_CHARGE_TERMINATION_TIMER_CONTROL register");
        return ret;
    }
    
    if (enable) {
        // 设置位7 (1表示启用看门狗)
        data |= (1 << 7);
        // 写回寄存器
        ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_CHARGE_TERMINATION_TIMER_CONTROL, data);
        if (ret != ESP_OK) {
            ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write AWREG_CHARGE_TERMINATION_TIMER_CONTROL register");
            return ret;
        }
        else {
            ESP_LOGI(_m5_io_aw32001_TAG, "Enabling watchdog");
        }
        // 设置超时时间
        ret = set_watchdog_timeout(_aw_default_WATCHDOG);
        if (ret != ESP_OK) {
            ESP_LOGE(_m5_io_aw32001_TAG, "Failed to set watchdog timeout");
            return ret;
        }
        else {
            ESP_LOGI(_m5_io_aw32001_TAG, "Setting watchdog timeout to %d seconds", _aw_default_WATCHDOG);
        }

    } else {
        // 清除位7 (0表示禁用看门狗)
        data &= ~(1 << 7);
        // 写回寄存器
        ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_CHARGE_TERMINATION_TIMER_CONTROL, data);
        if (ret != ESP_OK) {
            ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write AWREG_CHARGE_TERMINATION_TIMER_CONTROL register");
            return ret;
        }
        else {
            ESP_LOGI(_m5_io_aw32001_TAG, "Disabling watchdog");
        }
        // 设置超时时间为0
        ret = set_watchdog_timeout(0);
        if (ret != ESP_OK) {
            ESP_LOGE(_m5_io_aw32001_TAG, "Failed to set watchdog timeout to 0");
            return ret;
        }
        else {
            ESP_LOGI(_m5_io_aw32001_TAG, "Setting watchdog timeout to 0 seconds");
        }
    }
    
    return ESP_OK;
}


// 设置看门狗超时时间 (WATCHDOG)
// INPUT: uint16_t timeout 超时时间(0,40,80,160s，默认160s)
// RETURN: esp_err_t: 错误码
// REG: 05H[6:5]-(WATCHDOG)
// 注明1：看门狗超时时间设置为0时，可当作禁用全局看门狗
esp_err_t m5_ic_aw32001::set_watchdog_timeout(uint16_t timeout) 
{
    uint8_t step_code = 0;
    switch (timeout) {
        case 0: step_code = 0; break; // 禁用看门狗
        case 40: step_code = 1; break;
        case 80: step_code = 2; break;
        case 160: step_code = 3; break;
        default:
            ESP_LOGE(_m5_io_aw32001_TAG, "Invalid watchdog timeout value, using default (160s)");
            step_code = 3; // 默认160s
            break;
    }
    
    esp_err_t ret = write_reg_bits(AWREG_CHARGE_TERMINATION_TIMER_CONTROL, 0x60, (step_code << 5));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write WATCHDOG bits to AWREG_CHARGE_TERMINATION_TIMER_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "Watchdog timeout set to %d seconds (step: %d, bits: 0b%s)", timeout, step_code, UINT8_TO_BINARY_STRING(step_code,2));
    return ESP_OK;
}

// 设置充电终止使能 (EN_TERM)
// INPUT: bool enable: 是否启用充电终止 0: 禁用 1: 启用（默认）
// RETURN: esp_err_t: 错误码
// REG: 05H[4]-(EN_TERM)
// 注明1：如果TERM_TMR=1,该值为1也将无效，即使充满也将继续充电
esp_err_t m5_ic_aw32001::set_enable_charge_termination(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_CHARGE_TERMINATION_TIMER_CONTROL, 0x10, (enable ? 0x00 : 0x10));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EN_TERM bit to AWREG_CHARGE_TERMINATION_TIMER_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s charge termination", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置安全充电终止计时器使能 (EN_TIMER)
// INPUT: bool enable: 是否启用充电终止计时器 0: 禁用 1: 启用（默认）
// RETURN: esp_err_t: 错误码
// REG: 05H[3]-(EN_TIMER)
esp_err_t m5_ic_aw32001::set_enable_charge_timer(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_CHARGE_TERMINATION_TIMER_CONTROL, 0x08, (enable ? 0x00 : 0x08));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EN_TIMER bit to AWREG_CHARGE_TERMINATION_TIMER_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s charge timer", enable ? "Enable" : "Disable");
    return ESP_OK;
}


// 设置最长安全充电时间时长 (CHG_TMR)
// INPUT: uint16_t chg_tmr_value: 充电时间值 (3, 5, 8, 12小时，默认5小时)
// RETURN: esp_err_t: 错误码
// REG: 05H[2:1]-(CHG_TMR)
// 注明1：如果EN_TIMER=0,则设置不生效，请随后设置EN_TIMER=1
esp_err_t m5_ic_aw32001::set_charge_timer_value(uint16_t chg_tmr_value) 
{
    uint8_t step_code = 0;
    switch (chg_tmr_value) {
        case 3: step_code = 0; break;
        case 5: step_code = 1; break;
        case 8: step_code = 2; break;
        case 12: step_code = 3; break;
        default:
            ESP_LOGE(_m5_io_aw32001_TAG, "Invalid charge timer value, using default (5 hours)");
            step_code = 1; // 默认5小时
            break;
    }
    
    esp_err_t ret = write_reg_bits(AWREG_CHARGE_TERMINATION_TIMER_CONTROL, 0x06, (step_code << 1));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write CHG_TMR bits to AWREG_CHARGE_TERMINATION_TIMER_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "Charge timer set to %d hours (step: %d, bits: 0b%s)", chg_tmr_value, step_code, UINT8_TO_BINARY_STRING(step_code,2));
    return ESP_OK;
}

// 设置充电终止后行为方式 (TERM_TMR)
// INPUT: bool enable: 0: 充电完成后停止（默认） 1: 保持充电
// RETURN: esp_err_t: 错误码
// REG: 05H[0]-(TERM_TMR)
// 注明1：该值一般用于电池测试，若无需要请勿设置。
esp_err_t m5_ic_aw32001::set_charge_termination_mode(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_CHARGE_TERMINATION_TIMER_CONTROL, 0x01, (enable ? 0x01 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write TERM_TMR bit to AWREG_CHARGE_TERMINATION_TIMER_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s charge termination mode", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置NTC温度传感器使能 (EN_NTC)
// INPUT: bool enable: 0: 禁用 1: 启用（默认）
// RETURN: esp_err_t: 错误码
// REG: 06H[7]-(EN_NTC)
// 注明1：若使用短接了NTC引脚,务必将DIS_PCB_OTP设置为0，以启用PCB温度保护功能
// 注明2：若使用了外部NTC电阻，务必将DIS_PCB_OTP设置为1，以禁用PCB温度保护功能，否则NTC功能不生效
esp_err_t m5_ic_aw32001::set_enable_ntc(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_MAIN_CONTROL, 0x80, (enable ? 0x80 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EN_NTC bit to AWREG_MAIN_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s NTC", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置电源路径管理功能（PPMF）的安全计时器双倍时间使能 (TMR2X_EN)
// INPUT: bool enable: 0: 禁用 1: 启用（默认）
// RETURN: esp_err_t: 错误码
// REG: 06H[6]-(TMR2X_EN)
// 注明1：退出DPM/温度调节状态或禁用TMR2X_EN时，计时器恢复正常
esp_err_t m5_ic_aw32001::set_enable_TMR2X(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_MAIN_CONTROL, 0x40, (enable ? 0x40 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write TMR2X_EN bit to AWREG_MAIN_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s DPM timer", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置 启用/关闭 电池路径（FET_DIS）
// INPUT: bool enable: 0: 启用（默认） 1: 关闭
// RETURN: esp_err_t: 错误码
// REG: 06H[5]-(FET_DIS)
// 注明1：该值主要应用在运输模式
esp_err_t m5_ic_aw32001::set_enable_fet_dis(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_MAIN_CONTROL, 0x20, (enable ? 0x20 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write FET_DIS bit to AWREG_MAIN_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s battery path", enable ? "Disable" : "Enable");
    return ESP_OK;
}

// 设置 输入电源从正常状态进入非正常状态时 中断的触发使能
// INPUT: bool enable: 0: 启用（默认） 1: 禁用
// RETURN: esp_err_t: 错误码
// REG: 06H[4]-(PG_INT_CONTROL)
esp_err_t m5_ic_aw32001::set_pg_int_control(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_MAIN_CONTROL, 0x10, (enable ? 0x00 : 0x10));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write PG_INT_CONTROL bit to AWREG_MAIN_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s power good interrupt", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置 充电从未完成到完成时（指周期结束） 中断的触发使能
// INPUT: bool enable: 0: 启用（默认） 1: 禁用
// RETURN: esp_err_t: 错误码
// REG: 06H[3]-(EOC_INT_CONTROL)
esp_err_t m5_ic_aw32001::set_eoc_int_control(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_MAIN_CONTROL, 0x08, (enable ? 0x00 : 0x08));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EOC_INT_CONTROL bit to AWREG_MAIN_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s end of charge interrupt", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置 充电状态变化时（指状态变化） 中断的触发使能
// INPUT: bool enable: 0: 启用（默认） 1: 禁用
// RETURN: esp_err_t: 错误码
// REG: 06H[2]-(CHGSTATUS_INT_CONTROL)
esp_err_t m5_ic_aw32001::set_chgstatus_int_control(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_MAIN_CONTROL, 0x04, (enable ? 0x00 : 0x04));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write CHGSTATUS_INT_CONTROL bit to AWREG_MAIN_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s charge status interrupt", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置 温度传感器异常时 中断的触发使能
// INPUT: bool enable: 0: 启用（默认） 1: 禁用
// RETURN: esp_err_t: 错误码
// REG: 06H[1]-(NTC_INT_CONTROL)
esp_err_t m5_ic_aw32001::set_ntc_int_control(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_MAIN_CONTROL, 0x02, (enable ? 0x00 : 0x02));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write NTC_INT_CONTROL bit to AWREG_MAIN_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s NTC interrupt", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置 电池过压保护时 中断的触发使能
// INPUT: bool enable: 0: 启用（默认） 1: 禁用
// RETURN: esp_err_t: 错误码
// REG: 06H[0]-(BATOVP_INT_CONTROL)
esp_err_t m5_ic_aw32001::set_batovp_int_control(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_MAIN_CONTROL, 0x01, (enable ? 0x00 : 0x01));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write BATOVP_INT_CONTROL bit to AWREG_MAIN_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s battery overvoltage interrupt", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置 启用/关闭 PCB温度保护（DIS_PCB_OTP）
// INPUT: bool enable: 0: 启用（默认） 1: 关闭
// RETURN: esp_err_t: 错误码
// REG: 07H[7]-(DIS_PCB_OTP)
// 注明1：该值与EN_NTC相排斥，若启用了PCB_OTP，EN_NTC将无效，该值优先度高于EN_NTC
esp_err_t m5_ic_aw32001::set_dis_pcb_otp(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_SYSTEM_VOLTAGE_CONTROL, 0x80, (enable ? 0x00 : 0x80));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write DIS_PCB_OTP bit to AWREG_SYSTEM_VOLTAGE_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s PCB temperature protection", enable ? "Disable" : "Enable");
    return ESP_OK;
}

// 设置 启用/禁用 输入电压的动态管理（VIM_DPM）功能（DIS_VINLOOP）
// INPUT: bool enable: 0: 启用（默认） 1: 禁用
// RETURN: esp_err_t: 错误码
// REG: 07H[6]-(DIS_VINLOOP)
// 注明1：该值意在输入适配器可靠且输入电流稳定的情况下避免电流变化所使用的
//       不建议在适配器混乱的情况下关闭该功能
esp_err_t m5_ic_aw32001::set_enable_vinloop(bool enable) 
{
    esp_err_t ret = write_reg_bits(AWREG_SYSTEM_VOLTAGE_CONTROL, 0x40, (enable ? 0x00 : 0x40));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write DIS_VINLOOP bit to AWREG_SYSTEM_VOLTAGE_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s VINLOOP", enable ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置芯片内部过热保护阈值 （TJ_REG）
// INPUT: uint16_t tj_reg_value: 芯片过热保护阈值 (60,80,100,120℃，默认120℃)
// RETURN: esp_err_t: 错误码
// REG: 07H[5:4]-(TJ_REG)
// 注明1：当芯片温度超过150℃时，芯片将过热关机，直到降低到120℃，超过阈值将降低充电电流
esp_err_t m5_ic_aw32001::set_chip_overheat_protection_value(uint16_t tj_reg_value) 
{
    uint8_t step_code = 0;
    switch (tj_reg_value) {
        case 60: step_code = 0; break;
        case 80: step_code = 1; break;
        case 100: step_code = 2; break;
        case 120: step_code = 3; break;
        default:
            ESP_LOGE(_m5_io_aw32001_TAG, "Invalid chip overheat protection value, using default (120℃)");
            step_code = 3; // 默认120℃
            break;
    }
    
    esp_err_t ret = write_reg_bits(AWREG_SYSTEM_VOLTAGE_CONTROL, 0x30, (step_code << 4));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write TJ_REG bits to AWREG_SYSTEM_VOLTAGE_CONTROL");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "Chip overheat protection set to %d℃ (step: %d, bits: 0b%s)", tj_reg_value, step_code, UINT8_TO_BINARY_STRING(step_code,2));
    return ESP_OK;
}

// 配置系统输出电压 (VSYS_REG)
// INPUT: uint16_t vbat_value: 充电电压值 (3600-4545mV，步进15mV)
// INPUT: uint16_t vsys_reg_value: 配置系统输出电压 (4200mV-4950mV，步进50mV，默认4600mV)
// RETURN: esp_err_t: 错误码
// REG: 07H[3:0]-(VSYS_REG)
esp_err_t m5_ic_aw32001::set_system_voltage_value(uint16_t vsys_reg_value) 
{
    if (vsys_reg_value < 4200 || vsys_reg_value > 4950) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid system voltage: %d mV (valid 4200-4950mV)", vsys_reg_value);
        return ESP_ERR_INVALID_ARG;
    }

    // 计算寄存器代码值
    uint8_t step_code = (uint8_t)round((vsys_reg_value - 4200) / 50.0f);
    if (step_code > 0x0F) step_code = 0x0F; // 4位

    // 覆盖寄存器的指定位
    write_reg_bits(AWREG_SYSTEM_VOLTAGE_CONTROL, 0x0F, step_code);

    // 计算实际设置值
    float actual_voltage = 4200.0f + step_code * 50.0f;
    ESP_LOGI(_m5_io_aw32001_TAG, "System voltage set to %.0f mV (step: %d, bits: 0b%s)", actual_voltage, step_code, UINT8_TO_BINARY_STRING(step_code,4));

    return ESP_OK;
}

// 设置运输模式进入延迟时间 (EN_SHIPPING_DG)
// INPUT: uint16_t shipping_delay_value: 运输模式延迟时间 (1，2，4，8秒，默认1秒)
// RETURN: esp_err_t: 错误码
// REG: 09H[7:6]-(EN_SHIPPING_DG)
// 注明1：设置该参数会导致同寄存器下的VIN_FAULT,THEM_SD,BAT_FAULT,STMR_FAULT清0，
// 若有需要先执行get_fault_statuss()函数获取状态后再设置该参数
esp_err_t m5_ic_aw32001::set_shipping_delay_value(uint16_t shipping_delay_value) 
{
    uint8_t step_code = 0;
    switch (shipping_delay_value) {
        case 1: step_code = 0; break;
        case 2: step_code = 1; break;
        case 4: step_code = 2; break;
        case 8: step_code = 3; break;
        default:
            ESP_LOGE(_m5_io_aw32001_TAG, "Invalid shipping delay value, using default (1 second)");
            step_code = 0; // 默认1秒
            break;
    }
    
    esp_err_t ret = write_reg_bits(AWREG_FAULT, 0xC0, (step_code << 6));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EN_SHIPPING_DG bits to AWREG_FAULT");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "Shipping delay set to %d seconds (step: %d, bits: 0b%s)", shipping_delay_value, step_code, UINT8_TO_BINARY_STRING(step_code,2));
    
    return ESP_OK;
}

// 设置充电电流值（ICHG）的缩放模式 (EN_ICHG_DIVD)
// INPUT: bool en_ichg_divd_value: 充电电流值缩放模式 (0: 不变, 1: 设置值的1/4，默认0)
// RETURN: esp_err_t: 错误码
// REG: 0BH[7]-(EN_ICHG_DIVD)
esp_err_t m5_ic_aw32001::set_ichg_divd_value(bool en_ichg_divd_value) 
{
    esp_err_t ret = write_reg_bits(AWREG_INDIVIDUAL_CHARGE, 0x80, (en_ichg_divd_value ? 0x80 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EN_ICHG_DIVD bit to AWREG_INDIVIDUAL_CHARGE");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s ICHG_DIVD", en_ichg_divd_value ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置预充电电流的配置方式 (EN_IPRE_SET)
// INPUT: bool en_ipre_set_value: 预充电电流配置方式 (0:由REG03H[3:0]-(ITERM)决定, 1:由REG0BH[4:1]-(IPRE)决定，默认0)
// RETURN: esp_err_t: 错误码
// REG: 0BH[5]-(EN_IPRE_SET)
// 注明1：简而言之，为0时，预充电电流与充电终止电流相同，
// 为1时，预充电电流由REG0BH[4:1]-(IPRE)决定，可以单独配置预充电电流
esp_err_t m5_ic_aw32001::set_ipre_set_value(bool en_ipre_set_value) 
{
    esp_err_t ret = write_reg_bits(AWREG_INDIVIDUAL_CHARGE, 0x20, (en_ipre_set_value ? 0x20 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EN_IPRE_SET bit to AWREG_INDIVIDUAL_CHARGE");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s IPRE_SET", en_ipre_set_value ? "Enable" : "Disable");
    return ESP_OK;
}

// 设置充电电流值（IPRE）
// INPUT: uint16_t ipre_value: 预充电电流值 (1-31A，步进2mA，默认3mA)
// RETURN: esp_err_t: 错误码
// REG: 0BH[4:1]-(IPRE)
// 注明1：该值仅在EN_IPRE_SET=1时有效
esp_err_t m5_ic_aw32001::set_ipre_value(uint16_t ipre_value) 
{
    if (ipre_value < 1 || ipre_value > 31) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Invalid precharge current: %d mA (valid 1-31mA)", ipre_value);
        return ESP_ERR_INVALID_ARG;
    }

    // 计算代码值
    uint8_t code = (uint8_t)round((ipre_value - 1) / 2.0f);
    if (code > 0x0F) code = 0x0F; // 4位

    // 覆盖寄存器的指定位
    write_reg_bits(AWREG_INDIVIDUAL_CHARGE, 0x1E, (code << 1));

    // 计算实际设置值
    uint16_t actual_current = 1 + code * 2;
    ESP_LOGI(_m5_io_aw32001_TAG, "Precharge current set to %d mA (step: %d, bits: 0b%s)", actual_current, code, UINT8_TO_BINARY_STRING(code,4));

    return ESP_OK;
}

// 设置充电电流值（EN_SHIPMD_0P1S）
// INPUT: bool en_shipmd_0p1s_value: 设备从运输模式退出的延迟时间 (0: 2000毫秒, 1: 100毫秒秒，默认0)
// RETURN: esp_err_t: 错误码
// REG: 0BH[0]-(EN_SHIPMD_0P1S)
esp_err_t m5_ic_aw32001::set_shipmd_0p1s_value(bool en_shipmd_0p1s_value) 
{
    esp_err_t ret = write_reg_bits(AWREG_INDIVIDUAL_CHARGE, 0x01, (en_shipmd_0p1s_value ? 0x01 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EN_SHIPMD_0P1S bit to AWREG_INDIVIDUAL_CHARGE");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s SHIPMD_0P1S", en_shipmd_0p1s_value ? "Enable" : "Disable");
    return ESP_OK;
}


// 设置充电电流值突破550mA使能 (EN0P55)
// INPUT: bool en_0p55_value: 充电电流值突破550mA使能 (0: 禁用, 1: 启用，默认0)
// RETURN: esp_err_t: 错误码
// REG: 0CH[0]-(EN0P55)
// 注明1：该值仅在 REG00[3:0]-(ICHG) = 0b1111 时有效
esp_err_t m5_ic_aw32001::set_en_0p55_value(bool en_0p55_value) 
{
    esp_err_t ret = write_reg_bits(AWREG_ADDITIONAL_FUNCTION_CONTROL1, 0x01, (en_0p55_value ? 0x01 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write EN0P55 bit to AWREG_ADDITIONAL_FUNCTION_CONTROL1");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s 0P55", en_0p55_value ? "Enable" : "Disable");
    return ESP_OK;
}

// 配置充电终止电流持续时间（ITERMDEG）
// INPUT: bool itermdeg_value: 充电终止电流持续时间 (0：3秒， 1：1秒，默认3秒)
// RETURN: esp_err_t: 错误码
// REG: 0CH[6]-(ITERMDEG)
esp_err_t m5_ic_aw32001::set_itermdeg_value(bool itermdeg_value) 
{
    esp_err_t ret = write_reg_bits(AWREG_ADDITIONAL_FUNCTION_CONTROL1, 0x40, (itermdeg_value ? 0x40 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write ITERMDEG bit to AWREG_ADDITIONAL_FUNCTION_CONTROL1");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s ITERMDEG", itermdeg_value ? "Enable" : "Disable");
    return ESP_OK;
}

// 配置预充电超时时间（PRETO）
// INPUT: bool preto_value: 预充电超时时间 (0：1小时， 1：2小时，默认1小时)
// RETURN: esp_err_t: 错误码
// REG: 0CH[3]-(PRETO)
// 注明1：若安全计时器启用，且超过预充电超时时间，则触发stmr_fault系统故障标志位
esp_err_t m5_ic_aw32001::set_preto_value(bool preto_value) 
{
    esp_err_t ret = write_reg_bits(AWREG_ADDITIONAL_FUNCTION_CONTROL1, 0x08, (preto_value ? 0x08 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write PRETO bit to AWREG_ADDITIONAL_FUNCTION_CONTROL1");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s PRETO", preto_value ? "Enable" : "Disable");
    return ESP_OK;
}

// 配置是否禁止运输模式使用INT引脚唤醒（DIS_SHIPINT）
// INPUT: bool dis_shipint_value: 禁止运输模式使用INT引脚唤醒 (0：启用， 1：禁用，默认0).
// RETURN: esp_err_t: 错误码
// REG: 0CH[2]-(DIS_SHIPINT)
esp_err_t m5_ic_aw32001::set_dis_shipint_value(bool dis_shipint_value) 
{
    esp_err_t ret = write_reg_bits(AWREG_ADDITIONAL_FUNCTION_CONTROL1, 0x04, (dis_shipint_value ? 0x04 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write DIS_SHIPINT bit to AWREG_ADDITIONAL_FUNCTION_CONTROL1");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s DIS_SHIPINT", dis_shipint_value ? "Enable" : "Disable");
    return ESP_OK;
}

// 配置芯片复位后的延迟驱动时间（RSTDLAY）
// INPUT: bool rst_delay_value: 芯片复位后的延迟驱动时间 (0：0秒， 1：2秒，默认0秒)
// RETURN: esp_err_t: 错误码
// REG: 0CH[1]-(RSTDLAY)
esp_err_t m5_ic_aw32001::set_rst_delay_value(bool rst_delay_value) 
{
    esp_err_t ret = write_reg_bits(AWREG_ADDITIONAL_FUNCTION_CONTROL1, 0x02, (rst_delay_value ? 0x02 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write RSTDLAY bit to AWREG_ADDITIONAL_FUNCTION_CONTROL1");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s RSTDLAY", rst_delay_value ? "Enable" : "Disable");
    return ESP_OK;
}

// 配置通过INT引脚退出运输模式的所需时间（INT100MS）
// INPUT: bool int100ms_value: 通过INT引脚退出运输模式的所需时间 (0：2s， 1：100ms，默认2s)
// RETURN: esp_err_t: 错误码
// REG: 22H[3]-(INT100MS)
esp_err_t m5_ic_aw32001::set_int100ms_value(bool int100ms_value) 
{
    esp_err_t ret = write_reg_bits(AWREG_ADDITIONAL_FUNCTION_CONTROL2, 0x08, (int100ms_value ? 0x08 : 0x00));
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write INT100MS bit to AWREG_ADDITIONAL_FUNCTION_CONTROL2");
        return ret;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "%s INT100MS", int100ms_value ? "Enable" : "Disable");
    return ESP_OK;
}