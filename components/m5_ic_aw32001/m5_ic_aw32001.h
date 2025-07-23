/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef M5_IC_AW32001_H
#define M5_IC_AW32001_H

#include <cstdint>
#include <cmath>

#include "i2c_bus.h"
#include "esp_log.h"


typedef struct {
    uint32_t command;
    const char *command_str;
} command_mapping_t;

extern command_mapping_t command_mappings[];

//返回寄存器的名称,如果不存在返回"UNKNOWN"
#define GET_REGISTER_NAME(reg) ({ \
    const char *name = "UNKNOWN"; \
    for (size_t i = 0; i < sizeof(command_mappings) / sizeof(command_mapping_t); i++) { \
        if (command_mappings[i].command == reg) { \
            name = command_mappings[i].command_str; \
            break; \
        } \
    } \
    name; \
})

#define MASK_TO_BITRANGE(mask) \
    (__builtin_ffs(mask) ? ( \
        ({ static char __mask2bit_buf[12]; \
           snprintf(__mask2bit_buf, sizeof(__mask2bit_buf), "%d:%d", \
           31 - __builtin_clz(mask), __builtin_ctz(mask)); \
           __mask2bit_buf; }) \
    ) : "NA")

#define UINT8_TO_BINARY_STRING(value, width) \
    ({ static char __uint8_to_binary_buf[9]; \
       for (int i = 0; i < (width); i++) { \
           __uint8_to_binary_buf[i] = ((value) & (1 << ((width) - 1 - i))) ? '1' : '0'; \
       } \
       __uint8_to_binary_buf[width] = '\0'; \
       __uint8_to_binary_buf; })

//  寄存器地址定义
#define AWREG_INPUT_SOURCE_CONTROL 0x00 // 输入源控制寄存器
#define AWREG_POWER_ON_CONFIGURATION 0x01 // 上电配置寄存器
#define AWREG_CHARGE_CURRENT_CONTROL 0x02 // 充电电流控制寄存器
#define AWREG_DISCHARGE_CURRENT_CONTROL 0x03 // 放电电流控制寄存器
#define AWREG_CHARGE_VOLTAGE 0x04 // 充电电压控制寄存器
#define AWREG_CHARGE_TERMINATION_TIMER_CONTROL 0x05 // 充电 终止/定时器 控制寄存器
#define AWREG_MAIN_CONTROL 0x06 // 主控制寄存器
#define AWREG_SYSTEM_VOLTAGE_CONTROL 0x07 // 系统电压控制寄存器
#define AWREG_SYSTEM_STATUS 0x08 // 系统状态寄存器
#define AWREG_FAULT 0x09 // 故障寄存器
#define AWREG_CHIP_ID 0x0A // 芯片ID寄存器
#define AWREG_INDIVIDUAL_CHARGE 0x0B // 单独充电寄存器
#define AWREG_ADDITIONAL_FUNCTION_CONTROL1 0x0C // 附加功能控制寄存器1
#define AWREG_ADDITIONAL_FUNCTION_CONTROL2 0x22 // 附加功能控制寄存器2

// 充电状态定义
#define AWCHG_NOT_CHARGING 0x00 // 不充电
#define AWCHG_PRE_CHARGE 0x01 // 预充电
#define AWCHG_CHARGE 0x02 // 充电中 
#define AWCHG_CHARGE_DONE 0x03 // 充电完成

// AW Chip 系统状态定义
typedef struct {
    uint8_t watchdog_fault; // 看门狗复位标志
    uint8_t rev;            // 保留位
    uint8_t chg_stat;       // 充电状态
    uint8_t ppm_stat;       // 电压路径管理状态
    uint8_t pg_stat;        // 输入电源状态
    uint8_t therm_stat;     // 温度调节状态
}m5_ic_aw32001_status_t;

// AW Chip 系统故障定义
typedef struct {
    uint8_t vin_fault;      //   [读后清零] 输入电压过压/欠压故障标志
    uint8_t them_sd;        //   [读后清零] 热关断状态标志
    uint8_t bat_fault;      //   [读后清零] 电池过压标志
    uint8_t stmr_fault;     //   [读后清零] 安全计时器过期（预充/快充）
    uint8_t ntc_fault_1;    // [读后不清零] NTC过热故障标志1
    uint8_t ntc_fault_0;    // [读后不清零] NTC过冷故障标志0
}m5_ic_aw32001_fault_t;

class m5_ic_aw32001 {
public:
    m5_ic_aw32001(i2c_port_t i2c_port,gpio_num_t i2c_sda_pin, gpio_num_t i2c_scl_pin, uint32_t i2c_freq_hz);
    ~m5_ic_aw32001() = default;
    void init(uint8_t i2c_addr);    //初始化
    void set_debug_level(esp_log_level_t level) { esp_log_level_set(_m5_io_aw32001_TAG, level); } // 设置调试级别

    //———————————————
    //通用i2c读写函数 m5_ic_aw32001.cpp
    
    esp_err_t read_register(uint8_t reg_addr, uint8_t *data); // 读取寄存器
    esp_err_t write_register(uint8_t reg_addr, uint8_t data); // 写入寄存器
    esp_err_t write_reg_bits(uint8_t reg_addr, uint8_t mask, uint8_t value); // 通用寄存器位域写入函数
    esp_err_t write_reg_bits_with_info(uint8_t reg_addr, uint8_t mask, uint8_t value, char* err_info, char* ok_info); // 带信息的寄存器位域写入函数
    
    //———————————————
    //系统状态获取 寄存器自动更新

    uint8_t get_watchdog_fault_flag(void); // 获取看门狗复位标志
    uint8_t get_charge_status(void); // 获取充电状态
    uint8_t get_ppm_stat_flag(void); // 获取电压路径管理状态
    uint8_t get_pg_stat_flag(void); // 获取输入电压链路状态
    uint8_t get_therm_stat_flag(void); // 获取温度调节状态
    esp_err_t get_system_status(void); // 刷新芯片状态函数

    //———————————————
    //系统故障获取 寄存器读后清除

    esp_err_t get_fault_status(void); // 获取故障标志寄存器（Fault Register）[读后部分清零]

    //———————————————
    //芯片ID获取

    uint8_t get_chip_id(void); // 获取芯片ID
    
    //———————————————
    //模式切换类

    esp_err_t enter_shipping_mode(bool enable, bool dis_ship, uint16_t enter_delay, uint16_t vin_plug_wake_time, uint16_t int_down_wake_time); // 进入运输模式
    esp_err_t enter_battery_discharge_mode(bool enable, bool en_hiz);   // 进入仅电池供电模式
    esp_err_t enter_only_power_system_mode(bool enable);    // 进入仅电源供电模式
    esp_err_t enter_charge_mode(bool enable);   // 进入充电模式

    //———————————————
    //寄存器操作类 m5_ic_aw32001_regset.cpp

    esp_err_t set_vin_dpm_value(uint16_t vin_dpm_value);    // 设置输入电压阈值（VIN_DPM） 3880mV ~ 4680mV
    esp_err_t set_iin_lim_value(uint16_t current_ma);   // 设置输入电流限制（IIN_LIM） 50mA ~ 2000mA
    esp_err_t set_rst_dgl_time(uint16_t rst_dgl_time)   ; // 配置INT长时间拉低以复位系统的所需拉低时间（RST_DGL) 8-20s
    esp_err_t set_rst_dur_time(uint16_t int_down_time); // 设置INT长时间拉低以复位系统的持续时间（或看门狗复位）(INT_DOWN_TIME) 2s or 4s
    esp_err_t set_enable_hiz(bool enable); // 启用高阻态（EN_HIZ）
    esp_err_t set_enable_charge(bool enable); // 启用充电（CEB）
    esp_err_t set_vbat_uvlo_value(uint16_t vbat_uvlo); // 设置电池电压阈值（VBAT_UVLO） 2430mV ~ 3030mV
    esp_err_t set_register_reset(void); // 芯片寄存器复位（REG_RST）
    esp_err_t set_reset_watchdog(void); // 重置看门狗（WD_TMR_RST）
    esp_err_t set_charge_current_value(uint16_t ichg_value); // 设置充电电流（ICHG） 8mA ~ 512mA
    esp_err_t set_discharge_current_value(uint16_t idschg_value); // 设置电池放电电流(IDSCHG) 200mA ~ 3200mA
    esp_err_t set_termination_current_value(uint16_t iterm_value); // 设置充电终止电流（ITERM） 1mA ~ 31mA
    esp_err_t set_charge_voltage_value(uint16_t vbat_value); // 设置充电电压(VBAT_REG) 3600mV ~ 4545mV
    esp_err_t set_precharge_voltage_value(uint16_t vbat_pre_value); // 设置预充电电压(VBAT_PRE) 2800mV or 3000mV
    esp_err_t set_recharge_voltage_value(uint16_t vrech_value); // 设置再充电电压（VRECH） 100mV or 200mV
    esp_err_t set_dischg_watchdog_enable(bool enable); // 启用看门狗 (EN_WD_DISCHG)
    esp_err_t set_watchdog_timeout(uint16_t timeout); // 设置默认看门狗超时时间 (WATCHDOG) 0,40,80,160s
    esp_err_t set_enable_charge_termination(bool enable); // 设置充电终止使能 (EN_TERM)
    esp_err_t set_enable_charge_timer(bool enable); // 设置充电定时器使能 (TERM_TMR_EN)
    esp_err_t set_charge_timer_value(uint16_t chg_tmr_value); // 设置最长安全充电时间时长 (CHG_TMR) 3, 5, 8, 12h
    esp_err_t set_charge_termination_mode(bool enable); // 设置充电终止模式 (TERM_TMR_EN)
    esp_err_t set_enable_ntc(bool enable); // 设置NTC温度传感器使能 (EN_NTC)
    esp_err_t set_enable_TMR2X(bool enable); // 设置电源路径管理功能（PPMF）的安全计时器双倍时间使能 (TMR2X_EN)
    esp_err_t set_enable_fet_dis(bool enable); // 启用FET_DIS（FET_DIS）
    esp_err_t set_pg_int_control(bool enable); // 设置 输入电源从正常状态进入非正常状态时 中断的触发使能
    esp_err_t set_eoc_int_control(bool enable); // 设置 充电从未完成到完成时（指周期结束） 中断的触发使能
    esp_err_t set_chgstatus_int_control(bool enable); // 设置 充电状态变化时（指状态变化） 中断的触发使能
    esp_err_t set_ntc_int_control(bool enable); // 设置 温度传感器异常时 中断的触发使能
    esp_err_t set_batovp_int_control(bool enable); // 设置 电池过压保护时 中断的触发使能
    esp_err_t set_dis_pcb_otp(bool enable); // 设置PCB温度保护功能使能 (DIS_PCB_OTP)
    esp_err_t set_enable_vinloop(bool enable); // 输入电压的动态管理使能 (VINLOOP_EN)
    esp_err_t set_chip_overheat_protection_value(uint16_t tj_reg_value); // 设置芯片内部过热保护阈值 （TJ_REG）60,80,100,120℃
    esp_err_t set_system_voltage_value(uint16_t vsys_reg_value);     // 设置系统输出电压 (VSYS_REG) 4200mV ~ 4950mV
    esp_err_t set_shipping_delay_value(uint16_t shipping_delay_value); // 设置运输模式延迟时间 (EN_SHIPPING_DG) 1,2,4,8s
    esp_err_t set_ichg_divd_value(bool en_ichg_divd_value); // 设置充电电流值的缩放模式 (EN_I_CHG_DIVD) 0: 不变 1: 原来的1/4
    esp_err_t set_ipre_set_value(bool en_ipre_set_value); // 设置预充电电流的配置方式 (EN_IPRE_SET)
    esp_err_t set_ipre_value(uint16_t ipre_value); // 设置预充电电流值 (IPRE_VALUE) 1-31mA
    esp_err_t set_shipmd_0p1s_value(bool en_shipmd_0p1s_value); // 设置运输模式延迟时间 (EN_SHIPMD_0P1S) 0: 100ms 1: 2000ms
    esp_err_t set_en_0p55_value(bool en_0p55_value); // 设置充电电流值突破550mA使能 (EN0P55)
    esp_err_t set_itermdeg_value(bool itermdeg_value); // 配置充电终止电流持续时间（ITERMDEG） // 0: 3s 1: 1s
    esp_err_t set_preto_value(bool preto_value); // 配置预充电超时时间（PRETO） // 0: 1h 1: 2h
    esp_err_t set_dis_shipint_value(bool dis_shipint_value); // 配置是否禁止运输模式使用INT引脚唤醒（DIS_SHIPINT） // 0: 启用 1: 禁用
    esp_err_t set_rst_delay_value(bool rst_delay_value); // 配置芯片复位后的延迟驱动时间（RSTDLAY） // 0: 0s 1: 2s
    esp_err_t set_int100ms_value(bool int100ms_value); // 配置INT引脚的唤醒时间（INT100MS） // 0: 2000ms 1: 100ms
    
    // i2c配置参数
    i2c_port_t i2c_port = I2C_NUM_0;
    gpio_num_t i2c_sda_pin = GPIO_NUM_NC;
    gpio_num_t i2c_scl_pin = GPIO_NUM_NC;
    uint32_t i2c_freq_hz = 400000;  // 400kHz

    // aw chip 状态结构体
    m5_ic_aw32001_status_t m5_ic_aw32001_status = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    // aw chip 故障结构体
    m5_ic_aw32001_fault_t m5_ic_aw32001_fault = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

protected:
    const char *_m5_io_aw32001_TAG = "m5_io_aw32001";
    i2c_bus_handle_t _i2c_bus_handle = NULL;
    i2c_bus_device_handle_t _AW32001_i2c_bus_device_handle = NULL;
    uint8_t _aw_default_WATCHDOG = 160; // 默认看门狗超时时间/s
};

#endif // M5_IC_AW32001_H