#ifndef CST9217_DRIVER_H
#define CST9217_DRIVER_H

#include <stdint.h>
#include <string.h>
#include "i2c_bus.h"
#include "system_utils.h"

// CST9217设备地址
#define CST9217_ADDR 0x5A
#define MAX_POINTS_REPORT 5

// CST9217工作模式
enum work_mode {
    NOMAL_MODE = 0,
    GESTURE_MODE = 1,
    LP_MODE = 2,
    DEEPSLEEP = 3,
    DIFF_MODE = 4,
    RAWDATA_MODE = 5,
    BASELINE_MODE = 6,
    CALIBRATE_MODE = 7,
    FAC_TEST_MODE = 8,
    ENTER_BOOT_MODE = 0xCA,
};

// 触摸点信息结构体
typedef struct tp_info {
    uint8_t id;
    uint8_t switch_;
    uint16_t x;
    uint16_t y;
    uint16_t z;
} tp_info_t;

// 外部变量声明
extern tp_info_t tp_info[MAX_POINTS_REPORT];
extern volatile bool touch_irq_flag;

// 初始化CST9217
int cst9217_init(i2c_bus_handle_t i2c_bus);

// 更新触摸点信息
int cst9217_update();

// 进入引导程序模式
void cst9217_enter_bootloader();

// 读取芯片ID
void cst9217_read_chip_id();

// 读取触摸屏信息
int cst9217_read_tpinfo();

// 设置工作模式
void cst9217_set_workmode(enum work_mode mode, uint8_t enable);

// 从内存读取字
void cst9217_read_word_from_mem(uint8_t type, uint16_t addr, uint32_t *value);

// 读取数据
void cst9217_read_data(uint8_t *data, uint16_t len);

#endif // CST9217_DRIVER_H 