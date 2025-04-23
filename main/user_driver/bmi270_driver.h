#ifndef BMI270_DRIVER_H
#define BMI270_DRIVER_H

#include <stdint.h>
#include "i2c_bus.h"
#include "bmi270.h"

// BMI270设备地址
#define BMI270_ADDR 0x68

// BMI270传感器类型
#define ACCEL UINT8_C(0x00)
#define GYRO UINT8_C(0x01)
#define AUX UINT8_C(0x02)

// 初始化BMI270
void bmi270_dev_init(i2c_bus_handle_t i2c_bus);

// 更新BMI270数据
void bmi270_dev_update();

// BMI270 I2C读取回调
int8_t bmi2_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

// BMI270 I2C写入回调
int8_t bmi2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);

// BMI270延时回调
void bmi2_delay_us(uint32_t period, void *intf_ptr);

// 使能BMI270唤醒功能
void bmi270_wakeup_enable(uint8_t enable);

// 进入睡眠模式
void bmi270_dev_sleep();

// 唤醒BMI270
void bmi270_dev_wakeup();

#endif // BMI270_DRIVER_H 