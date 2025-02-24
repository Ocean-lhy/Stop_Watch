#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/rmt_tx.h"
#include "driver/rmt_rx.h"
#include "ir_nec_encoder.h"

#define TAG "ir_test"

#define IR_TX_GPIO_NUM (gpio_num_t)9

#define IR_RESOLUTION_HZ 1000000 // 1MHz resolution, 1 tick = 1us
static rmt_channel_handle_t tx_channel = NULL;
static rmt_transmit_config_t transmit_config;
static rmt_encoder_handle_t nec_encoder = NULL;

void ir_tx_init()
{
    ESP_LOGI(TAG, "create RMT TX channel");
    rmt_tx_channel_config_t tx_channel_cfg = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = IR_RESOLUTION_HZ,
        .mem_block_symbols = 64, // amount of RMT symbols that the channel can store at a time
        .trans_queue_depth = 4,  // number of transactions that allowed to pending in the background, this example won't queue multiple transactions, so queue depth > 1 is sufficient
        .gpio_num = IR_TX_GPIO_NUM,
    };
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_channel_cfg, &tx_channel));

    ESP_LOGI(TAG, "modulate carrier to TX channel");
    rmt_carrier_config_t carrier_cfg = {
        .duty_cycle = 0.33,
        .frequency_hz = 38000, // 38KHz
    };
    ESP_ERROR_CHECK(rmt_apply_carrier(tx_channel, &carrier_cfg));

    // this example won't send NEC frames in a loop
    transmit_config.loop_count = 0; // no loop

    ESP_LOGI(TAG, "install IR NEC encoder");
    ir_nec_encoder_config_t nec_encoder_cfg = {
        .resolution = IR_RESOLUTION_HZ,
    };
    ESP_ERROR_CHECK(rmt_new_ir_nec_encoder(&nec_encoder_cfg, &nec_encoder));

    ESP_LOGI(TAG, "enable RMT TX channels");
    ESP_ERROR_CHECK(rmt_enable(tx_channel));
}

void ir_tx_trans(uint16_t addr, uint16_t cmd)
{
    const ir_nec_scan_code_t scan_code = {
        .address = addr,
        .command = cmd,
    };
    ESP_ERROR_CHECK(rmt_transmit(tx_channel, nec_encoder, &scan_code, sizeof(scan_code), &transmit_config));
}
