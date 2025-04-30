#include "es8311_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "soc/soc_caps.h"
#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"
#include "esp_littlefs.h"
#include <string.h>
#include <errno.h>
#include "esp_timer.h"
#include "lcd_driver.h"

static const char *TAG = "es8311_driver";
i2c_bus_device_handle_t es8311_dev = NULL;
uint8_t play_flag = 2;
bool is_recording = false;
bool is_playing = false;
bool is_loop_test = false;

#define RECORD_FILE "/littlefs/record.pcm"
#define RECORD_BUFFER_SIZE (1024 * 4)

extern const uint8_t test_pcm_start[] asm("_binary_test_pcm_start");
extern const uint8_t test_pcm_end[]   asm("_binary_test_pcm_end");

void es8311_driver_init(i2c_bus_handle_t i2c_bus)
{
    ESP_LOGI(TAG, "es8311_init");
    // i2c
    es8311_dev = i2c_bus_device_create(i2c_bus, ES8311_ADDR, 400000);
    if (es8311_dev == NULL)
    {
        ESP_LOGE(TAG, "es8311_dev i2c create failed");
    }
    else
    {
        ESP_LOGI(TAG, "es8311_dev i2c create success");
    }

    // i2s
    i2s_config_t i2s_cfg = {0};
    i2s_cfg.mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX);
    i2s_cfg.sample_rate          = 44100;
    i2s_cfg.bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT;
    i2s_cfg.channel_format       = I2S_CHANNEL_FMT_RIGHT_LEFT;
    i2s_cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    i2s_cfg.dma_buf_count        = 3;
    i2s_cfg.dma_buf_len          = 300;
    i2s_cfg.use_apll             = 1;
    i2s_cfg.intr_alloc_flags     = ESP_INTR_FLAG_LEVEL2;

    i2s_driver_install(I2S_NUM_0, &i2s_cfg, 0, NULL);
    i2s_pin_config_t i2s_pin_cfg = {0};
    i2s_pin_cfg.mck_io_num   = I2S_MCLK_PIN;
    i2s_pin_cfg.bck_io_num   = I2S_BCLK_PIN;
    i2s_pin_cfg.ws_io_num    = I2S_LRCK_PIN;
    i2s_pin_cfg.data_out_num = I2S_DDAC_OUT_PIN;
    i2s_pin_cfg.data_in_num  = I2S_DADC_IN_PIN;
    i2s_set_pin(I2S_NUM_0, &i2s_pin_cfg);
    // i2s_zero_dma_buffer(I2S_NUM_0);
    
    // es8311
    ESP_LOGI(TAG, "Start es8311 codec chip");
    audio_hal_codec_config_t es8311_cfg = {0};
    es8311_cfg.adc_input = AUDIO_HAL_ADC_INPUT_LINE1;
    es8311_cfg.dac_output = AUDIO_HAL_DAC_OUTPUT_ALL;
    es8311_cfg.codec_mode = AUDIO_HAL_CODEC_MODE_BOTH;
    es8311_cfg.i2s_iface.mode = AUDIO_HAL_MODE_SLAVE;
    es8311_cfg.i2s_iface.fmt = AUDIO_HAL_I2S_NORMAL;
    es8311_cfg.i2s_iface.samples = AUDIO_HAL_44K_SAMPLES;
    es8311_cfg.i2s_iface.bits = AUDIO_HAL_BIT_LENGTH_16BITS;
    ESP_LOGI(TAG, "init es8311");
    es8311_codec_init(&es8311_cfg);
    es8311_codec_config_i2s(es8311_cfg.codec_mode, &es8311_cfg.i2s_iface);
    es8311_codec_ctrl_state(AUDIO_HAL_CODEC_MODE_BOTH, AUDIO_HAL_CTRL_START);
    es8311_set_mic_gain(ES8311_MIC_GAIN_0DB);
    // 0xC0: -96 dB, 0x64: -50 dB, 0x00: 0 dB
    es8311_codec_set_voice_volume(0xBD);
    
    es8311_read_all();

    es8311_test(0);
    
    xTaskCreate(record_and_play_task, "record_and_play_task", 1024 * 8, NULL, (configMAX_PRIORITIES - 1), NULL);
}

void send_event(uint8_t key)
{
    if (example_lvgl_lock(-1))
    {
        lv_obj_t *current = lv_scr_act();
        lv_event_send(current, LV_EVENT_KEY, &key);
        example_lvgl_unlock();
    }
}

void record_and_play_task(void *arg)
{
    uint8_t *buffer = NULL;
    FILE *file = NULL;
    size_t bytes_read;
    size_t bytes_written;
    int64_t recording_start_time = 0;  // 记录录音开始时间
    
    while (1) 
    {
        // 处理录音
        if (is_recording) {
            if (file == NULL) {
                // 首次开始录音时打开文件
                file = fopen(RECORD_FILE, "wb");
                if (file == NULL) {
                    ESP_LOGE(TAG, "无法打开录音文件: %s", strerror(errno));
                    is_recording = false;
                    send_event(4);
                    continue;
                }
                
                // 分配缓冲区
                if (buffer == NULL) {
                    buffer = (uint8_t *)malloc(RECORD_BUFFER_SIZE);
                    if (buffer == NULL) {
                        ESP_LOGE(TAG, "无法分配录音缓冲区");
                        fclose(file);
                        file = NULL;
                        is_recording = false;
                        send_event(4);
                        continue;
                    }
                }
                
                // 记录录音开始时间
                recording_start_time = esp_timer_get_time();
                ESP_LOGI(TAG, "开始录音，最多持续10秒");
            }

            while (is_recording) 
            {
                // 检查是否已录音超过10秒
                if ((esp_timer_get_time() - recording_start_time) > 10000000) 
                { // 10秒 = 10,000,000微秒
                    ESP_LOGI(TAG, "录音已达到10秒上限，自动停止");
                    fclose(file);
                    file = NULL;
                    is_recording = false;
                    send_event(3);
                    continue;
                }
                
                if (i2s_read(I2S_NUM_0, buffer, RECORD_BUFFER_SIZE, &bytes_read, 20 / portTICK_PERIOD_MS) == ESP_OK) 
                {
                    if (bytes_read > 0) 
                    {
                        bytes_written = fwrite(buffer, 1, bytes_read, file);
                        if (bytes_written != bytes_read) 
                        {
                            ESP_LOGE(TAG, "写入文件失败: %s", strerror(errno));
                        }
                    }
                }
            }

            if (file != NULL && !is_recording) 
            {
                // 录音停止，关闭文件
                fclose(file);
                file = NULL;
                ESP_LOGI(TAG, "录音已停止");
                is_recording = false;
                send_event(3);
            }
        } 
        
        // 处理播放
        if (is_playing) {
            if (file == NULL) {
                // 首次开始播放时打开文件
                file = fopen(RECORD_FILE, "rb");
                if (file == NULL) {
                    ESP_LOGE(TAG, "无法打开播放文件: %s", strerror(errno));
                    is_playing = false;
                    send_event(4);
                    continue;
                }
                
                // 分配缓冲区
                if (buffer == NULL) {
                    buffer = (uint8_t *)malloc(RECORD_BUFFER_SIZE);
                    if (buffer == NULL) {
                        ESP_LOGE(TAG, "无法分配播放缓冲区");
                        fclose(file);
                        file = NULL;
                        is_playing = false;
                        send_event(4);
                        continue;
                    }
                }
                
                ESP_LOGI(TAG, "开始播放");
            }
            
            while (is_playing) 
            {
                size_t chunk_size = RECORD_BUFFER_SIZE;
                bytes_read = fread(buffer, 1, chunk_size, file);
                if (bytes_read > 0 && is_playing) 
                { // 再次检查是否仍在播放
                    if (i2s_write(I2S_NUM_0, buffer, bytes_read, &bytes_written, 20 / portTICK_PERIOD_MS) != ESP_OK) 
                    {
                        ESP_LOGE(TAG, "I2S写入失败");
                    }
                } 
                else 
                {
                    // 文件读取完毕或出错
                    if (feof(file)) {
                        ESP_LOGI(TAG, "播放完成");
                        fclose(file);
                        file = NULL;
                        is_playing = false;
                        send_event(4);
                    } 
                    else 
                    if (bytes_read <= 0 && !is_playing) 
                    {
                        // 播放被停止
                        fclose(file);
                        file = NULL;
                        is_playing = false;
                        send_event(4);
                        ESP_LOGI(TAG, "播放已停止");
                    } 
                    else
                    {
                        ESP_LOGE(TAG, "读取文件错误: %s", strerror(errno));
                    }
                }
            }

            if (file != NULL && !is_playing) 
            {
                // 播放停止，关闭文件
                fclose(file);
                file = NULL;
                ESP_LOGI(TAG, "播放已停止");
                send_event(4);
            }
        } 
        
        // 如果既不录音也不播放，释放缓冲区
        if (!is_recording && !is_playing && buffer != NULL) 
        {
            free(buffer);
            buffer = NULL;
        }
        
        // 减少延时，更快地响应停止命令
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}

void start_recording(void)
{
    if (is_recording) {
        ESP_LOGI(TAG, "已经在录音中");
        return;
    }
    
    is_recording = true;
    is_playing = false;
}

void play_recording(void)
{
    if (is_playing) 
    {
        ESP_LOGI(TAG, "已经在播放中");
        return;
    }
    
    is_playing = true;
    is_recording = false;
}

void stop_recording(void)
{
    is_recording = false;
}

void stop_playing(void)
{
    is_playing = false;
}