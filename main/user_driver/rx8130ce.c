#include "rx8130ce.h"
#include <string.h>
#include "esp_log.h"

static const char *TAG = "rx8130ce";
static i2c_bus_device_handle_t rx8130_dev = NULL;
static uint8_t ctrl_reg = 0; // 保存控制寄存器值

// BCD转二进制
static inline uint8_t bcd2bin(uint8_t val)
{
    return (val & 0x0f) + ((val >> 4) * 10);
}

// 二进制转BCD
static inline uint8_t bin2bcd(uint8_t val)
{
    return ((val / 10) << 4) + (val % 10);
}

// 从RX8130读取寄存器
esp_err_t rx8130_read_reg(uint8_t reg_addr, uint8_t *data)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    esp_err_t ret = i2c_bus_read_byte(rx8130_dev, reg_addr, data);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取寄存器0x%02x失败: %d", reg_addr, ret);
    }
    
    return ret;
}

// 写入RX8130寄存器
esp_err_t rx8130_write_reg(uint8_t reg_addr, uint8_t data)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    esp_err_t ret = i2c_bus_write_byte(rx8130_dev, reg_addr, data);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "写入寄存器0x%02x值0x%02x失败: %d", reg_addr, data, ret);
    }
    
    return ret;
}

// 从RX8130读取多个寄存器
static esp_err_t rx8130_read_regs(uint8_t reg_addr, uint8_t *data, size_t len)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    esp_err_t ret = i2c_bus_read_bytes(rx8130_dev, reg_addr, len, data);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取多个寄存器从0x%02x开始失败: %d", reg_addr, ret);
    }
    
    return ret;
}

// 写入多个寄存器
static esp_err_t rx8130_write_regs(uint8_t reg_addr, const uint8_t *data, size_t len)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    esp_err_t ret = i2c_bus_write_bytes(rx8130_dev, reg_addr, len, data);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "写入多个寄存器从0x%02x开始失败: %d", reg_addr, ret);
    }
    
    return ret;
}

// 初始化RX8130
esp_err_t rx8130_init(i2c_bus_handle_t i2c_bus)
{
    esp_err_t ret;
    bool need_reset = false;
    uint8_t ctrl[3]; // 扩展、标志、控制寄存器
    
    rx8130_dev = i2c_bus_device_create(i2c_bus, RX8130_I2C_ADDR, 400000);
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "创建I2C设备失败");
        return ESP_FAIL;
    }
    
    // 读取扩展、标志、控制寄存器
    ret = rx8130_read_regs(RX8130_REG_EXT, ctrl, 3);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取配置寄存器失败");
        return ret;
    }
    
    // 设置扩展寄存器，TE=0，配置频率
    ctrl[0] &= ~RX8130_BIT_EXT_TE;      // 关闭计时器
    ctrl[0] &= ~RX8130_BIT_EXT_FSEL;    // 清除FSEL位
    ctrl[0] |= 0x02;                    // 设置TSEL为1Hz
    ret = rx8130_write_reg(RX8130_REG_EXT, ctrl[0]);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "写入扩展寄存器失败");
        return ret;
    }
    
    // 清除测试位
    ctrl_reg = (ctrl[2] & ~RX8130_BIT_CTRL_TEST);
    
    // 检查电压低标志（上电时设置）
    if (ctrl[1] & RX8130_BIT_FLAG_VLF) {
        ESP_LOGW(TAG, "检测到电压低，可能是供电电压下降");
        need_reset = true;
    }
    
    // 检查各种标志位
    bool need_clear = false;
    
    if (ctrl[1] & RX8130_BIT_FLAG_AF) {
        ESP_LOGW(TAG, "检测到闹钟标志");
        need_clear = true;
    }
    
    if (ctrl[1] & RX8130_BIT_FLAG_TF) {
        ESP_LOGW(TAG, "检测到定时器标志");
        need_clear = true;
    }
    
    if (ctrl[1] & RX8130_BIT_FLAG_UF) {
        ESP_LOGW(TAG, "检测到更新标志");
        need_clear = true;
    }
    
    // 需要重置或清除?
    if (need_reset || need_clear) {
        // 清除标志寄存器
        ret = rx8130_write_reg(RX8130_REG_FLAG, 0x00);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "清除标志寄存器失败");
            return ret;
        }
        
        // 清除控制寄存器
        ret = rx8130_write_reg(RX8130_REG_CTRL0, 0x00);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "清除控制寄存器失败");
            return ret;
        }
        
        ctrl_reg = 0;
    }
    
    ESP_LOGI(TAG, "RX8130初始化成功");
    return ESP_OK;
}

// 获取RTC时间
esp_err_t rx8130_get_time(rx8130_datetime_t *datetime)
{
    if (datetime == NULL) {
        ESP_LOGE(TAG, "datetime参数为NULL");
        return ESP_ERR_INVALID_ARG;
    }
    
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    uint8_t data[7];
    esp_err_t ret = rx8130_read_regs(RX8130_REG_SEC, data, 7);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取时间失败");
        return ret;
    }
    
    datetime->second = bcd2bin(data[0] & 0x7f);
    datetime->minute = bcd2bin(data[1] & 0x7f);
    datetime->hour = bcd2bin(data[2] & 0x3f);  // 仅24小时制
    datetime->day = bcd2bin(data[3] & 0x7f);
    datetime->date = bcd2bin(data[4] & 0x3f);
    datetime->month = bcd2bin(data[5] & 0x1f);
    datetime->year = bcd2bin(data[6]);
    
    // 注意：RX8130只存储年份的后两位，例如"23"表示2023年
    // 因此，对于大于50的值，我们假定是20世纪（1950-1999）
    // 对于小于50的值，我们假定是21世纪（2000-2049）
    // 这样处理是为了兼容那些使用不同世纪假设的软件
    
    ESP_LOGD(TAG, "获取时间: %02d/%02d/%02d %02d:%02d:%02d 星期%d", 
             datetime->year, datetime->month, datetime->date,
             datetime->hour, datetime->minute, datetime->second,
             datetime->day);
             
    return ESP_OK;
}

// 设置RTC时间
esp_err_t rx8130_set_time(const rx8130_datetime_t *datetime)
{
    if (datetime == NULL) {
        ESP_LOGE(TAG, "datetime参数为NULL");
        return ESP_ERR_INVALID_ARG;
    }
    
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    // 检查年份范围，RX8130只能存储0-99的年份值
    if (datetime->year > 99) {
        ESP_LOGE(TAG, "年份超出范围(0-99): %d", datetime->year);
        return ESP_ERR_INVALID_ARG;
    }
    
    uint8_t data[7];
    uint8_t ctrl;
    esp_err_t ret;
    
    // 设置STOP位
    ret = rx8130_read_reg(RX8130_REG_CTRL0, &ctrl);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取控制寄存器失败");
        return ret;
    }
    
    ctrl_reg = ctrl | RX8130_BIT_CTRL_STOP;
    ret = rx8130_write_reg(RX8130_REG_CTRL0, ctrl_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "写入控制寄存器失败");
        return ret;
    }
    
    // 准备时间数据
    data[0] = bin2bcd(datetime->second);
    data[1] = bin2bcd(datetime->minute);
    data[2] = bin2bcd(datetime->hour);
    data[3] = bin2bcd(datetime->day);
    data[4] = bin2bcd(datetime->date);
    data[5] = bin2bcd(datetime->month);
    data[6] = bin2bcd(datetime->year);
    
    // 写入时间
    ret = rx8130_write_regs(RX8130_REG_SEC, data, 7);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "写入时间失败");
        return ret;
    }
    
    // 清除STOP位
    ret = rx8130_read_reg(RX8130_REG_CTRL0, &ctrl);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取控制寄存器失败");
        return ret;
    }
    
    ctrl_reg = ctrl & ~RX8130_BIT_CTRL_STOP;
    ret = rx8130_write_reg(RX8130_REG_CTRL0, ctrl_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "写入控制寄存器失败");
        return ret;
    }
    
    ESP_LOGI(TAG, "设置时间: %02d/%02d/%02d %02d:%02d:%02d 星期%d", 
             datetime->year, datetime->month, datetime->date,
             datetime->hour, datetime->minute, datetime->second,
             datetime->day);
             
    return ESP_OK;
}

// 检查电压低标志
esp_err_t rx8130_check_voltage_low(bool *vl_flag)
{
    if (vl_flag == NULL) {
        ESP_LOGE(TAG, "vl_flag参数为NULL");
        return ESP_ERR_INVALID_ARG;
    }
    
    uint8_t flag;
    esp_err_t ret = rx8130_read_reg(RX8130_REG_FLAG, &flag);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取标志寄存器失败");
        return ret;
    }
    
    *vl_flag = (flag & RX8130_BIT_FLAG_VLF) ? true : false;
    ESP_LOGD(TAG, "电压低标志: %d", *vl_flag);
    
    return ESP_OK;
}

// 清除电压低标志
esp_err_t rx8130_clear_voltage_low(void)
{
    uint8_t flag;
    esp_err_t ret = rx8130_read_reg(RX8130_REG_FLAG, &flag);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取标志寄存器失败");
        return ret;
    }
    
    flag &= ~RX8130_BIT_FLAG_VLF;
    ret = rx8130_write_reg(RX8130_REG_FLAG, flag);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "清除电压低标志失败");
        return ret;
    }
    
    ESP_LOGI(TAG, "清除电压低标志成功");
    return ESP_OK;
}

/**
 * 关闭RTC所有中断，避免nIRQ引脚异常触发
 */
esp_err_t rx8130_disable_all_interrupts(void)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    uint8_t ctrlreg;
    esp_err_t ret;
    
    // 读取控制寄存器
    ret = rx8130_read_reg(RX8130_REG_CTRL0, &ctrlreg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取控制寄存器0失败");
        return ret;
    }
    
    // 禁用所有中断位 (AIE, TIE, UIE)
    ctrlreg &= ~(RX8130_BIT_CTRL_AIE | RX8130_BIT_CTRL_TIE | RX8130_BIT_CTRL_UIE);
    
    ret = rx8130_write_reg(RX8130_REG_CTRL0, ctrlreg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "禁用所有中断失败");
        return ret;
    }
    
    // 更新全局控制寄存器变量
    ctrl_reg = ctrlreg;
    
    ESP_LOGI(TAG, "已禁用所有RTC中断");
    return ESP_OK;
}

void print_time(rx8130_datetime_t *datetime)
{
    ESP_LOGI(TAG, "时间: %02d/%02d/%02d %02d:%02d:%02d 星期%d",
            datetime->year, datetime->month, datetime->date,
            datetime->hour, datetime->minute, datetime->second,
            datetime->day);
}

/**
 * 设置定时器
 * @param seconds 秒数，有效范围1-4095秒
 * @return esp_err_t
 */
esp_err_t rx8130_set_timer(uint16_t seconds)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    if (seconds == 0 || seconds > 4095) {
        ESP_LOGE(TAG, "定时器范围无效(1-4095): %d", seconds);
        return ESP_ERR_INVALID_ARG;
    }
    
    uint8_t ext_reg;
    uint8_t flag_reg;
    uint8_t ctrl_reg_val;
    esp_err_t ret;
    
    // 1. 首先禁用定时器
    ret = rx8130_read_reg(RX8130_REG_CTRL0, &ctrl_reg_val);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取控制寄存器失败");
        return ret;
    }
    
    // 禁用定时器中断
    ctrl_reg_val &= ~RX8130_BIT_CTRL_TIE;
    ret = rx8130_write_reg(RX8130_REG_CTRL0, ctrl_reg_val);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "禁用定时器中断失败");
        return ret;
    }
    
    // 2. 设置定时器模式和频率
    ret = rx8130_read_reg(RX8130_REG_EXT, &ext_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取扩展寄存器失败");
        return ret;
    }
    
    // 设置定时器模式为1Hz (TSEL = 0b010)
    ext_reg &= ~RX8130_BIT_EXT_TSEL; // 清除TSEL位
    ext_reg |= 0x02;                 // 设置为1Hz (0b010)
    
    // 禁用定时器(先关闭定时器)
    ext_reg &= ~RX8130_BIT_EXT_TE;
    
    ret = rx8130_write_reg(RX8130_REG_EXT, ext_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "设置扩展寄存器失败");
        return ret;
    }
    
    // 3. 清除定时器标志
    ret = rx8130_read_reg(RX8130_REG_FLAG, &flag_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取标志寄存器失败");
        return ret;
    }
    
    flag_reg &= ~RX8130_BIT_FLAG_TF;
    ret = rx8130_write_reg(RX8130_REG_FLAG, flag_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "清除定时器标志失败");
        return ret;
    }
    
    // 4. 设置定时器计数值 (TCOUNT1:TCOUNT0)
    uint8_t tcount[2];
    tcount[0] = seconds & 0xFF;        // 低8位
    tcount[1] = (seconds >> 8) & 0x0F;  // 高4位
    
    ret = rx8130_write_regs(RX8130_REG_TCOUNT0, tcount, 2);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "设置定时器计数值失败");
        return ret;
    }
    
    ESP_LOGI(TAG, "定时器计数值设置为: %d秒", seconds);
    
    return ESP_OK;
}

/**
 * 启用定时器中断
 * 在设置好定时器后调用此函数启动定时器并使其能触发中断
 * @param enable 是否启用
 * @return esp_err_t
 */
esp_err_t rx8130_enable_timer(bool enable)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    uint8_t ext_reg;
    uint8_t ctrl_reg_val;
    esp_err_t ret;
    
    // 1. 读取扩展寄存器
    ret = rx8130_read_reg(RX8130_REG_EXT, &ext_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取扩展寄存器失败");
        return ret;
    }
    
    // 2. 读取控制寄存器
    ret = rx8130_read_reg(RX8130_REG_CTRL0, &ctrl_reg_val);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取控制寄存器失败");
        return ret;
    }
    
    if (enable) {
        // 启用定时器(TE位)
        ext_reg |= RX8130_BIT_EXT_TE;
        
        // 启用定时器中断(TIE位)
        ctrl_reg_val |= RX8130_BIT_CTRL_TIE;
    } else {
        // 禁用定时器(TE位)
        ext_reg &= ~RX8130_BIT_EXT_TE;
        
        // 禁用定时器中断(TIE位)
        ctrl_reg_val &= ~RX8130_BIT_CTRL_TIE;
    }
    
    // 3. 写回扩展寄存器
    ret = rx8130_write_reg(RX8130_REG_EXT, ext_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "设置扩展寄存器失败");
        return ret;
    }
    
    // 4. 写回控制寄存器
    ret = rx8130_write_reg(RX8130_REG_CTRL0, ctrl_reg_val);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "设置控制寄存器失败");
        return ret;
    }
    
    // 更新全局控制寄存器变量
    ctrl_reg = ctrl_reg_val;
    
    ESP_LOGI(TAG, "定时器 %s", enable ? "已启用" : "已禁用");
    return ESP_OK;
}

/**
 * 检查定时器是否触发
 * @param triggered 输出参数，指示定时器是否已触发
 * @return esp_err_t
 */
esp_err_t rx8130_is_timer_triggered(bool *triggered)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    if (triggered == NULL) {
        ESP_LOGE(TAG, "triggered参数为NULL");
        return ESP_ERR_INVALID_ARG;
    }
    
    uint8_t flag_reg;
    esp_err_t ret = rx8130_read_reg(RX8130_REG_FLAG, &flag_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取标志寄存器失败");
        return ret;
    }
    
    *triggered = (flag_reg & RX8130_BIT_FLAG_TF) ? true : false;
    
    if (*triggered) {
        ESP_LOGI(TAG, "检测到定时器触发");
    }
    
    return ESP_OK;
}

/**
 * 清除定时器触发标志
 * @return esp_err_t
 */
esp_err_t rx8130_clear_timer_flag(void)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    uint8_t flag_reg;
    esp_err_t ret = rx8130_read_reg(RX8130_REG_FLAG, &flag_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取标志寄存器失败");
        return ret;
    }
    
    flag_reg &= ~RX8130_BIT_FLAG_TF;
    ret = rx8130_write_reg(RX8130_REG_FLAG, flag_reg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "清除定时器标志失败");
        return ret;
    }
    
    ESP_LOGI(TAG, "已清除定时器标志");
    return ESP_OK;
}

/**
 * 设置关机定时器模式
 * 此模式下，只有定时器会激活nIRQ引脚，其他事件不会触发
 * @param seconds 定时器秒数，1-4095秒
 * @return esp_err_t
 */
esp_err_t rx8130_set_shutdown_timer_mode(uint16_t seconds)
{
    if (rx8130_dev == NULL) {
        ESP_LOGE(TAG, "设备未初始化");
        return ESP_ERR_INVALID_STATE;
    }
    
    esp_err_t ret;
    
    // 1. 首先禁用所有中断
    ret = rx8130_disable_all_interrupts();
    if (ret != ESP_OK) {
        return ret;
    }
    
    // 2. 清除所有标志位
    ret = rx8130_write_reg(RX8130_REG_FLAG, 0x00);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "清除标志寄存器失败");
        return ret;
    }
    
    // 3. 设置定时器
    ret = rx8130_set_timer(seconds);
    if (ret != ESP_OK) {
        return ret;
    }
    
    // 4. 启用定时器和定时器中断
    ret = rx8130_enable_timer(true);
    if (ret != ESP_OK) {
        return ret;
    }
    
    ESP_LOGI(TAG, "已设置关机定时器模式，%d秒后触发", seconds);
    return ESP_OK;
}