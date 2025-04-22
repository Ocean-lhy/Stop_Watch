#ifndef BQ27220_DRIVER_H
#define BQ27220_DRIVER_H

#include <stdint.h>
#include "i2c_bus.h"

// BQ27220设备地址
#define BQ27220_ADDR 0x55

// 初始化BQ27220
void bq27220_init(i2c_bus_handle_t i2c_bus);

// 退出密封模式
void bq27220_exit_sealed();

// 进入密封模式
void bq27220_enter_seal();

// 进入睡眠模式
void bq27220_enter_sleep_mode();

// 进入完全访问模式
void bq27220_full_access();

// 检查操作状态
bool bq27220_opration_status_check();

// 进入配置更新模式
void bq27220_enter_cfg_update();

// 配置A操作
void bq27220_opration_config_A();

// 配置B操作
void bq27220_opration_config_B();

// 读取设计容量
void bq27220_read_design_capacity();

// 读取电池电压
uint16_t bq27220_read_voltage();

// 读取电池电流
uint16_t bq27220_read_current();

// 读取设备编号
void bq27220_read_dev_number();

// I2C读取函数
esp_err_t bq27220_i2c_read(uint8_t reg_addr, uint16_t sub_reg, uint16_t *reg_data);

#endif // BQ27220_DRIVER_H 