#ifndef AW32001_DRIVER_H
#define AW32001_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "i2c_bus.h"

// AW32001设备地址
#define AW32001_ADDR 0x49

// AW32001寄存器定义
#define AW32001_REG_PWR_CFG 0x01
#define AW32001_REG_CHR_CUR 0x02
#define AW32001_REG_CHR_VOL 0x04
#define AW32001_REG_SYS_STA 0x08

// 初始化AW32001
void aw32001_init(i2c_bus_handle_t i2c_bus);

// 检查充电状态
uint8_t aw32001_check_status();

// 启用/禁用充电
void aw32001_charge_set(bool en);

#endif // AW32001_DRIVER_H 