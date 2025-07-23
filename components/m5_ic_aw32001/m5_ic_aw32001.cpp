/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include "m5_ic_aw32001.h"


command_mapping_t command_mappings[] = {
    {AWREG_INPUT_SOURCE_CONTROL, "AWREG_INPUT_SOURCE_CONTROL"},
    {AWREG_POWER_ON_CONFIGURATION, "AWREG_POWER_ON_CONFIGURATION"},
    {AWREG_CHARGE_CURRENT_CONTROL, "AWREG_CHARGE_CURRENT_CONTROL"},
    {AWREG_DISCHARGE_CURRENT_CONTROL, "AWREG_DISCHARGE_CURRENT_CONTROL"},
    {AWREG_CHARGE_VOLTAGE, "AWREG_CHARGE_VOLTAGE"},
    {AWREG_CHARGE_TERMINATION_TIMER_CONTROL, "AWREG_CHARGE_TERMINATION_TIMER_CONTROL"},
    {AWREG_MAIN_CONTROL, "AWREG_MAIN_CONTROL"},
    {AWREG_SYSTEM_VOLTAGE_CONTROL, "AWREG_SYSTEM_VOLTAGE_CONTROL"},
    {AWREG_SYSTEM_STATUS, "AWREG_SYSTEM_STATUS"},
    {AWREG_FAULT, "AWREG_FAULT"},
    {AWREG_CHIP_ID, "AWREG_CHIP_ID"},
    {AWREG_INDIVIDUAL_CHARGE, "AWREG_INDIVIDUAL_CHARGE"},
    {AWREG_ADDITIONAL_FUNCTION_CONTROL1, "AWREG_ADDITIONAL_FUNCTION_CONTROL1"},
    {AWREG_ADDITIONAL_FUNCTION_CONTROL2, "AWREG_ADDITIONAL_FUNCTION_CONTROL2"}
};


m5_ic_aw32001::m5_ic_aw32001(i2c_port_t i2c_port,gpio_num_t i2c_sda_pin, gpio_num_t i2c_scl_pin, uint32_t i2c_freq_hz) {
    
    //save the parameters to the class members
    this->i2c_port = i2c_port;
    this->i2c_sda_pin = i2c_sda_pin;
    this->i2c_scl_pin = i2c_scl_pin;
    this->i2c_freq_hz = i2c_freq_hz;

    // Create I2C bus configuration
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = i2c_sda_pin,
        .scl_io_num = i2c_scl_pin,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master = {
            .clk_speed = i2c_freq_hz,
        },
        .clk_flags = 0,
    };
    // Create the I2C bus
    _i2c_bus_handle = i2c_bus_create(i2c_port, &conf);
    if (_i2c_bus_handle == NULL) {
        // Handle error: failed to create I2C bus
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to create I2C bus");
        return;
    }
}

// 初始化函数
// INPUT: i2c_addr: I2C地址
// RETURN: none
void m5_ic_aw32001::init(uint8_t i2c_addr) {

    ESP_LOGI(_m5_io_aw32001_TAG, "Initializing M5STAC IC Driver -> AW32001[0x%02X]", i2c_addr);

    // Initialize the I2C bus and any other necessary components
    if (_i2c_bus_handle == NULL) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to create I2C bus");
        return;
    }

    _AW32001_i2c_bus_device_handle = i2c_bus_device_create(_i2c_bus_handle, i2c_addr, i2c_freq_hz);
    if (_AW32001_i2c_bus_device_handle == NULL) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to create I2C bus device handle");
        return;
    }
    ESP_LOGI(_m5_io_aw32001_TAG, "I2C bus device handle created successfully");
    
    // 读取芯片ID
    uint8_t CHIPID = get_chip_id();
    ESP_LOGI(_m5_io_aw32001_TAG, "Chip: ID = 0x%02X", CHIPID);

    // 关闭看门狗
    set_watchdog_timeout(0);

    // 读取故障标志寄存器
    get_fault_status();
    // 读取系统状态寄存器
    get_system_status();


}

// 读取寄存器
// INPUT: reg_addr: 寄存器地址, data: 寄存器值的指针
// RETURN: esp_err_t: 错误码
esp_err_t m5_ic_aw32001::read_register(uint8_t reg_addr, uint8_t *data) {
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, reg_addr, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read register 0x%02X", reg_addr);
    } else {
        ESP_LOGI(_m5_io_aw32001_TAG, "[Reg:0x%02X] -> 0x%02X", reg_addr, *data);
    }
    return ret;
}

// 写入寄存器
// INPUT: reg_addr: 寄存器地址, data: 寄存器值
// RETURN: esp_err_t: 错误码
esp_err_t m5_ic_aw32001::write_register(uint8_t reg_addr, uint8_t data) {
    return i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, reg_addr, data);
}

// 通用寄存器位域写入函数
esp_err_t m5_ic_aw32001::write_reg_bits(uint8_t reg_addr, uint8_t mask, uint8_t value) {
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, reg_addr, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed", reg_addr,MASK_TO_BITRANGE(mask), GET_REGISTER_NAME(reg_addr));
        return ret;
    }
    data = (data & ~mask) | (value & mask);
    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, reg_addr, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register write failed", reg_addr,MASK_TO_BITRANGE(mask), GET_REGISTER_NAME(reg_addr));
    } else {
        ESP_LOGD(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register write success", reg_addr,MASK_TO_BITRANGE(mask), GET_REGISTER_NAME(reg_addr));
    }
    return ret;
}

// 带信息的寄存器位域写入函数
esp_err_t m5_ic_aw32001::write_reg_bits_with_info(uint8_t reg_addr, uint8_t mask, uint8_t value, char* err_info, char* ok_info) {  
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, reg_addr, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed,err_info:%s", reg_addr,MASK_TO_BITRANGE(mask), GET_REGISTER_NAME(reg_addr), err_info);
        return ret;
    }
    data = (data & ~mask) | (value & mask);
    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, reg_addr, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register write failed,err_info:%s", reg_addr,MASK_TO_BITRANGE(mask), GET_REGISTER_NAME(reg_addr), err_info);
    } else {
        ESP_LOGD(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register write success,ok_info:%s", reg_addr,MASK_TO_BITRANGE(mask), GET_REGISTER_NAME(reg_addr), ok_info);
    }
    return ret;
}


// 获取看门狗复位标志
// INPUT: none
// RETURN: uint8_t Watchdog_Fault: 看门狗复位标志，0：正常，1：看门狗复位，0xFF: 读取错误码
// REG: 08H[7]-(WD_TMR_RST)
uint8_t m5_ic_aw32001::get_watchdog_fault_flag(void)
{
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_SYSTEM_STATUS, &data);
    
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed,return 0xFF", AWREG_SYSTEM_STATUS,MASK_TO_BITRANGE(0x80), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS));
        m5_ic_aw32001_status.watchdog_fault = 0xFF; // 错误码
        return 0xFF; // 错误码
    }

    // 提取位7的看门狗复位标志 (B7)
    uint8_t watchdog_reset_flag = (data & 0b10000000) >> 7;
    m5_ic_aw32001_status.watchdog_fault = watchdog_reset_flag; // 更新状态结构体

    ESP_LOGI(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read success,return 0x%02X->%s", AWREG_SYSTEM_STATUS,
             MASK_TO_BITRANGE(0x80), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS), watchdog_reset_flag,
             watchdog_reset_flag == 0 ? "Normal" : "Watchdog Reset");

    return watchdog_reset_flag;
}

// 预留 REG: 08H[6:5]-(REV) :保留位，默认0x00


// 获取充电状态
// INPUT: none
// RETURN: uint8_t charge_state: 充电状态, 0xFF: 读取错误码
// REG: 08H[4:3]-(WD_TMR_RST)
// 注明1：充电状态: 0b00: NOT CHARGING, 0b01: PRE CHARGING, 0b10: CHARGING, 0b11: CHARGING DONE
uint8_t m5_ic_aw32001::get_charge_status(void)
{
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_SYSTEM_STATUS, &data);
    
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed,return 0xFF", AWREG_SYSTEM_STATUS,MASK_TO_BITRANGE(0x18), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS));
        m5_ic_aw32001_status.chg_stat = 0xFF; // 错误码
        return 0xFF; // 错误码
    }

    // 提取位4和位3的充电状态 (B4-B3)
    uint8_t charge_state = (data & 0b00011000) >> 3;
    m5_ic_aw32001_status.chg_stat = charge_state; // 更新状态结构体

    ESP_LOGI(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read success,return 0x%02X > %s", AWREG_SYSTEM_STATUS,
             MASK_TO_BITRANGE(0x18), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS), charge_state,
             charge_state == 0 ? "NOT CHARGING" : (charge_state == 1 ? "PRE CHARGING" : (charge_state == 2 ? "CHARGING" : "CHARGING DONE")));

    return charge_state;
}

// 获取电压路径管理状态（PPM）
// INPUT: none
// RETURN: uint8_t PPM_STAT = 0:无PPM调控, 1-输入动态功率管理生效 ,默认0
// REG: 08H[2]-(PPM_STAT)
uint8_t m5_ic_aw32001::get_ppm_stat_flag(void)
{
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_SYSTEM_STATUS, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed,return 0xFF", AWREG_SYSTEM_STATUS, MASK_TO_BITRANGE(0x04), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS));
        m5_ic_aw32001_status.ppm_stat = 0xFF; // 错误码
        return 0xFF; // 错误码
    }

    // 提取位2的PPM状态 (B2)
    uint8_t ppm_stat = (data & 0b00000100) >> 2;
    m5_ic_aw32001_status.ppm_stat = ppm_stat; // 更新状态结构体

    ESP_LOGI(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read success,return 0x%02X > %s", AWREG_SYSTEM_STATUS,
             MASK_TO_BITRANGE(0x04), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS), ppm_stat,
             ppm_stat == 0 ? "No PPM" : "PPM Active");

    return ppm_stat;
}

// 获取输入电压链路状态（PG_STAT）
// INPUT: none
// RETURN: uint8_t PG_STAT = 0:输入电源异常, 1-输入电压正常 ,默认1
// REG: 08H[1]-(PG_STAT)
// 注明1：PG_STAT 主要是电压链路方面的状态是否满足要求，而VIN_FAULT则是 过压或欠压（更为严重）
uint8_t m5_ic_aw32001::get_pg_stat_flag(void)
{
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_SYSTEM_STATUS, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed,return 0xFF", AWREG_SYSTEM_STATUS, MASK_TO_BITRANGE(0x02), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS));
        m5_ic_aw32001_status.pg_stat = 0xFF; // 错误码
        return 0xFF; // 错误码
    }

    // 提取位1的PG状态 (B1)
    uint8_t pg_stat = (data & 0b00000010) >> 1;
    m5_ic_aw32001_status.pg_stat = pg_stat; // 更新状态结构体

    ESP_LOGI(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read success,return 0x%02X > %s", AWREG_SYSTEM_STATUS,
             MASK_TO_BITRANGE(0x02), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS), pg_stat,
             pg_stat == 0 ? "Power Good" : "Power Not Good");

    return pg_stat;
}

// 获取温度调节状态（THERM_STAT）
// INPUT: none
// RETURN: uint8_t THERM_STAT = 0:未触发温度保护, 1-触发温度保护 ,默认0
// REG: 08H[0]-(THERM_STAT)
uint8_t m5_ic_aw32001::get_therm_stat_flag(void)
{
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_SYSTEM_STATUS, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed,return 0xFF", AWREG_SYSTEM_STATUS, MASK_TO_BITRANGE(0x01), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS));
        m5_ic_aw32001_status.therm_stat = 0xFF; // 错误码
        return 0xFF; // 错误码
    }

    // 提取位0的THERM状态 (B0)
    uint8_t therm_stat = (data & 0b00000001);
    m5_ic_aw32001_status.therm_stat = therm_stat; // 更新状态结构体

    ESP_LOGI(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read success,return 0x%02X > %s", AWREG_SYSTEM_STATUS,
             MASK_TO_BITRANGE(0x01), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS), therm_stat,
             therm_stat == 0 ? "Thermal Protection Not Triggered" : "Thermal Protection Triggered");

    return therm_stat;
}

// 刷新芯片状态函数
// INPUT: none
// RETURN: esp_err_t: 错误码
// REG: 08H[7:0]-(SYSTEM_STATUS)
// 注明1：该寄存器数值动态刷新，init时会自动优先执行一次该函数。
esp_err_t m5_ic_aw32001::get_system_status(void)
{
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_SYSTEM_STATUS, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed,return ESP_FAIL", AWREG_SYSTEM_STATUS, MASK_TO_BITRANGE(0xFF), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS));
        return ret;
    }

    // 提取各个状态位
    m5_ic_aw32001_status.watchdog_fault = (data & 0b10000000) >> 7; // 看门狗复位标志
    m5_ic_aw32001_status.rev = (data & 0b01100000) >> 5; // 保留位
    m5_ic_aw32001_status.chg_stat = (data & 0b00011000) >> 3; // 充电状态
    m5_ic_aw32001_status.ppm_stat = (data & 0b00000100) >> 2; // 电压路径管理状态
    m5_ic_aw32001_status.pg_stat = (data & 0b00000010) >> 1; // 输入电源状态
    m5_ic_aw32001_status.therm_stat = (data & 0b00000001); // 温度调节状态

    // 打印状态信息
    ESP_LOGI(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read success,return 0x%02X > Watchdog Fault:%d,REV:%d,Charge State:%d,PPM State:%d,PG State:%d,Thermal State:%d",
             AWREG_SYSTEM_STATUS, MASK_TO_BITRANGE(0xFF), GET_REGISTER_NAME(AWREG_SYSTEM_STATUS),
             data, m5_ic_aw32001_status.watchdog_fault, m5_ic_aw32001_status.rev,
             m5_ic_aw32001_status.chg_stat, m5_ic_aw32001_status.ppm_stat,
             m5_ic_aw32001_status.pg_stat, m5_ic_aw32001_status.therm_stat);

    return ESP_OK;
}

// 获取故障标志寄存器（Fault Register）
// INPUT: none
// RETURN: esp_err_t: 错误码
// REG: 09H[7-0]-(Fault Register)
// 注明1：该寄存器用于存储故障信息，其中VIN_FAULT,THEM_SD,BAT_FAULT,STMR_FAULT读后清0，init时会自动优先执行该函数。
esp_err_t m5_ic_aw32001::get_fault_status(void)
{
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_FAULT, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed,return ESP_FAIL", AWREG_FAULT, MASK_TO_BITRANGE(0xFF), GET_REGISTER_NAME(AWREG_FAULT));
        return ret;
    }

    // 提取故障状态
    m5_ic_aw32001_fault.vin_fault = (data & 0b00100000) >> 5; // 输入电源异常标志
    m5_ic_aw32001_fault.them_sd = (data & 0b00010000) >> 4; // 热关断状态标志
    m5_ic_aw32001_fault.bat_fault = (data & 0b00001000) >> 3; // 电池故障标志
    m5_ic_aw32001_fault.stmr_fault = (data & 0b00000100) >> 2; // STMR故障标志
    m5_ic_aw32001_fault.ntc_fault_1 = (data & 0b00000010) >> 1; // NTC故障标志1
    m5_ic_aw32001_fault.ntc_fault_0 = (data & 0b00000001); // NTC故障标志0

    ESP_LOGI(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read success,return 0x%02X > VIN Fault:%d,THERM SD:%d,BAT Fault:%d,STMR Fault:%d,NTC Fault1:%d,NTC Fault0:%d",
             AWREG_FAULT, MASK_TO_BITRANGE(0xFF), GET_REGISTER_NAME(AWREG_FAULT),
             data, m5_ic_aw32001_fault.vin_fault, m5_ic_aw32001_fault.them_sd,
             m5_ic_aw32001_fault.bat_fault, m5_ic_aw32001_fault.stmr_fault,
             m5_ic_aw32001_fault.ntc_fault_1, m5_ic_aw32001_fault.ntc_fault_0);
    
    return ESP_OK;
}

// 获取芯片ID
// INPUT: none
// RETURN: uint8_t chip_id: 芯片ID, 0xFF: 读取错误码
// REG: 0AH[7:0]-(CHIP_ID)
uint8_t m5_ic_aw32001::get_chip_id(void)
{
    uint8_t data = 0;
    esp_err_t ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_CHIP_ID, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read failed,return 0xFF", AWREG_CHIP_ID, MASK_TO_BITRANGE(0xFF), GET_REGISTER_NAME(AWREG_CHIP_ID));
        return 0xFF; // 错误码
    }

    ESP_LOGD(_m5_io_aw32001_TAG, "REG_%02XH[%s]-%s > Register read success,return 0x%02X", AWREG_CHIP_ID,
             MASK_TO_BITRANGE(0xFF), GET_REGISTER_NAME(AWREG_CHIP_ID), data);

    return data;
}

// 配置运输模式(Shipping Mode,SHIP)
// INPUT: bool enable: 是否启用运输模式
//        bool dis_ship : 是否禁用运输模式中断引脚
//        uint16_t enter_delay : 符合条件后，进入运输模式的延迟时间(1000,2000,4000,8000ms)
//        uint16_t vin_plug_wake_time : 插入USB后，退出运输模式的唤醒时间（100，2000ms）
//        uint16_t int_down_wake_time : 拉低INT后，退出运输模式的唤醒时间（100，2000ms）
// 注明：Vin_UVLO = 3.6V（手册），当启用运输模式时，
//      输入电压小于3.6V时 或 拔掉USB供电时，AW32001会在设定延迟后自动进入运输模式。
// RETURN: esp_err_t: 错误码
esp_err_t m5_ic_aw32001::enter_shipping_mode(bool enable, bool dis_ship, uint16_t enter_delay, uint16_t vin_plug_wake_time, uint16_t int_down_wake_time)
{
    esp_err_t ret = ESP_OK;
    uint8_t data  = 0;

    // 1. 设置FET_DIS位 (REG06H[5])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_MAIN_CONTROL, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read FET control register");
        return ret;
    }

    if (enable) {
        // 设置位5为1，启用FET_DIS
        data |= (1 << 5);
    } else {
        // 清除位5，禁用FET_DIS
        data &= ~(1 << 5);
    }

    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_MAIN_CONTROL, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write FET control register");
        return ret;
    }

    // 2. 设置运输模式延迟时间 (REG09H[7:6])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_FAULT, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read shipping delay register");
        return ret;
    }

    // 清除位7:6
    data &= ~(0b11 << 6);

    // 设置延迟时间
    switch (enter_delay) {
        case 1000:  // 00: 1000ms (默认)
            // 位7:6 = 00，不需要操作，已清除
            break;
        case 2000:  // 01: 2000ms
            data |= (0b01 << 6);
            break;
        case 4000:  // 10: 4000ms
            data |= (0b10 << 6);
            break;
        case 8000:  // 11: 8000ms
            data |= (0b11 << 6);
            break;
        default:
            ESP_LOGW(_m5_io_aw32001_TAG, "Invalid enter_delay value, using default (1000ms)");
            break;
    }

    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_FAULT, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write shipping delay register");
        return ret;
    }

    // 3. 设置插入适配器唤醒时间 (REG0BH[0])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_INDIVIDUAL_CHARGE, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read shipping wake register");
        return ret;
    }

    if (vin_plug_wake_time == 100) {
        // 设置为0.1秒 (默认)
        data |= 0x01;
    } else {
        // 设置为2秒
        data &= ~0x01;
    }

    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_INDIVIDUAL_CHARGE, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write shipping wake register");
        return ret;
    }

    // 4. 设置INT引脚唤醒时间 (REG22H[3])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_ADDITIONAL_FUNCTION_CONTROL2, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read INT config register");
        return ret;
    }

    if (int_down_wake_time == 100) {
        // 设置为100ms，位3=1 
        data |= (1 << 3);
    } else {
        // 设置为2000ms，位3=0 (默认)
        data &= ~(1 << 3);
    }

    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_ADDITIONAL_FUNCTION_CONTROL2, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write INT config register");
        return ret;
    }

    // 5. 设置INT引脚异常处理 (REG0CH[2])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_ADDITIONAL_FUNCTION_CONTROL1, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read shipping INT register");
        return ret;
    }

    if (dis_ship) {
        // 禁用INT引脚唤醒，位2=1
        data |= (1 << 2);
        ESP_LOGW(_m5_io_aw32001_TAG, "Disabling INT pin for shipping mode wake-up");
    } else {
        // 启用INT引脚唤醒，位2=0
        data &= ~(1 << 2);
    }

    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_ADDITIONAL_FUNCTION_CONTROL1, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write shipping INT register");
        return ret;
    }

    if (enable) {
        ESP_LOGI(_m5_io_aw32001_TAG, "Shipping mode enabled with delay: %d ms", enter_delay);
    } else {
        ESP_LOGI(_m5_io_aw32001_TAG, "Shipping mode disabled");
    }

    return ESP_OK;
}

// 进入仅电池供电模式（Battery Discharge Mode，DISCHG）
// INPUT: bool enable: 是否进入仅电池供电模式
//        bool en_hiz: 是否启用高阻模式（EN_HIZ=1）,主动断开外部供电
// RETURN: esp_err_t: 错误码
// 注明1：前置条件 1. [断开电源 或 电源低于Vin_UVLO（3.6V）] 或 启用高阻模式（EN_HIZ=1）-> 不推荐
// 注明2：执行该函数将导致FET_DIS=0，运输模式将禁止进入
// 注明3：该函数不建议主动使用，当外部供电断开或电源低于Vin_UVLO（3.6V）时，会自动进入该模式，除非测试目的
esp_err_t m5_ic_aw32001::enter_battery_discharge_mode(bool enable, bool en_hiz) {
    esp_err_t ret = ESP_OK;
    uint8_t data = 0;

    if(enable == 0 )
    {
        ESP_LOGI(_m5_io_aw32001_TAG, "unsupported set enter_battery_discharge_mode:enable=0,return");
        return ESP_FAIL;
    }

    // 1. 设置FET_DIS位 (REG06H[5])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_MAIN_CONTROL, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read FET control register");
        return ret;
    }

    if (enable) {
        // 清除位5，禁用FET_DIS
        data |= (1 << 5);
    }

    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_MAIN_CONTROL, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write FET control register");
        return ret;
    }

    // 2. 设置高阻模式（EN_HIZ） (REG01H[4])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read high impedance register");
        return ret;
    }

    if (en_hiz) {
        // 设置位4为1，启用高阻模式
        data |= (1 << 4);
        ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, data);
        if (ret != ESP_OK) {
            ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write high impedance register");
            return ret;
        }
    }

    if (enable) {
        ESP_LOGI(_m5_io_aw32001_TAG, "Battery discharge mode enabled with EN_HIZ: %d", en_hiz);
    } else {
        ESP_LOGI(_m5_io_aw32001_TAG, "Battery discharge mode disabled");
    }

    return ESP_OK;
}

// 进入仅电源供电模式（Only Power System Mode,OPSM）
// INPUT: bool enable: 是否进入仅电源供电模式
// RETURN: esp_err_t: 错误码
// 注明1：进入该模式将禁用充电（CEB=1）
// 注明2：进入该模式将关闭高阻态（EN_HIZ=0）
// 注明3: 该函数不影响运输模式参数
esp_err_t m5_ic_aw32001::enter_only_power_system_mode(bool enable) {
    esp_err_t ret = ESP_OK;
    uint8_t data = 0;

    if(enable == 0 )
    {
        ESP_LOGI(_m5_io_aw32001_TAG, "unsupported set enter_only_power_system_mode:enable=0,return");
        return ESP_FAIL;
    }

    // 1. 设置EN_HIZ位 (REG01H[4])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read high impedance register");
        return ret;
    }
    // 清除位4，禁用高阻模式
    data &= ~(1 << 4);
    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write high impedance register");
        return ret;
    }

    // 2. 设置充电使能位 (REG01H[3])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read charge enable register");
        return ret;
    }
    // 设置位3为1，禁用充电
    data |= (1 << 3);
    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write charge enable register");
        return ret;
    }
    if (enable) {
        ESP_LOGI(_m5_io_aw32001_TAG, "Only power system mode enabled");
    } 

    return ESP_OK;
}

// 进入充电模式（Charge Mode,CHG）
// INPUT: bool enable: 是否进入充电模式
// RETURN: esp_err_t: 错误码
// 注明1：进入该模式将启用充电（CEB=0）
// 注明2：进入该模式将禁用高阻态（EN_HIZ=0）
// 注明3：该函数不影响运输模式参数
esp_err_t m5_ic_aw32001::enter_charge_mode(bool enable) {
    esp_err_t ret = ESP_OK;
    uint8_t data = 0;

    if(enable == 0 )
    {
        ESP_LOGI(_m5_io_aw32001_TAG, "unsupported set enter_charge_mode:enable=0,return");
        return ESP_FAIL;
    }

    // 1. 设置EN_HIZ位 (REG01H[4])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read high impedance register");
        return ret;
    }
    // 清除位4，禁用高阻模式
    data &= ~(1 << 4);
    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write high impedance register");
        return ret;
    }

    // 2. 设置充电使能位 (REG01H[3])
    ret = i2c_bus_read_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to read charge enable register");
        return ret;
    }
    // 设置位3为0，启用充电
    data &= ~(1 << 3);
    ret = i2c_bus_write_byte(_AW32001_i2c_bus_device_handle, AWREG_POWER_ON_CONFIGURATION, data);
    if (ret != ESP_OK) {
        ESP_LOGE(_m5_io_aw32001_TAG, "Failed to write charge enable register");
        return ret;
    }
    
    if (enable) {
        ESP_LOGI(_m5_io_aw32001_TAG, "Charge mode enabled");
    } 

    return ESP_OK;
}