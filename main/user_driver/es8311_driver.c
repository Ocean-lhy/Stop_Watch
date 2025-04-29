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

static const char *TAG = "es8311_driver";
i2c_bus_device_handle_t es8311_dev = NULL;
uint8_t play_flag = 2;
bool is_recording = false;
bool is_playing = false;

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
    
    // xTaskCreate(record_and_play_task, "record_and_play_task", 1024 * 8, NULL, 5, NULL);
}

void record_and_play_task(void *arg)
{
    size_t bytes_read;
    uint8_t *record_cache = (uint8_t *)malloc(1024 * 4);    // heap_caps_malloc
    while (1) 
    {
        if (play_flag == 0)
        {
            if (i2s_read(I2S_NUM_0, (void *)record_cache, 1024 * 4, &bytes_read, portMAX_DELAY) == ESP_OK)
            {
                if(i2s_write(I2S_NUM_0, (void *)record_cache, bytes_read, &bytes_read, portMAX_DELAY) != ESP_OK)
                {
                    ESP_LOGE(TAG, "i2s_write failed:bytes=%d", bytes_read);
                }
                for(int i=0; i<100; i++) 
                {
                    ESP_LOGI(TAG, "%d,", ((int16_t*)record_cache)[i]);
                }
                ESP_LOGI(TAG, "\n");
            }
            else
            {
                ESP_LOGE(TAG, "i2s_read failed:bytes=%d", bytes_read);
            }
        }
        else
        {
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
    free(record_cache);
}

void start_recording(void)
{
    if (is_recording) {
        ESP_LOGI(TAG, "Already recording");
        return;
    }
    
    is_recording = true;
    is_playing = false;
    
    // 打开文件准备写入
    FILE *f = fopen(RECORD_FILE, "wb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for recording: %s", strerror(errno));
        is_recording = false;
        return;
    }
    
    uint8_t *record_buffer = (uint8_t *)malloc(RECORD_BUFFER_SIZE);
    if (record_buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate record buffer");
        fclose(f);
        is_recording = false;
        return;
    }
    
    size_t bytes_read;
    while (is_recording) {
        if (i2s_read(I2S_NUM_0, record_buffer, RECORD_BUFFER_SIZE, &bytes_read, portMAX_DELAY) == ESP_OK) {
            size_t bytes_written = fwrite(record_buffer, 1, bytes_read, f);
            if (bytes_written != bytes_read) {
                ESP_LOGE(TAG, "Failed to write to file: %s", strerror(errno));
                break;
            }
            
        }
    }
    
    fclose(f);
    free(record_buffer);
    ESP_LOGI(TAG, "Recording stopped");
}

void play_recording(void)
{
    if (is_playing) {
        ESP_LOGI(TAG, "Already playing");
        return;
    }
    
    is_playing = true;
    is_recording = false;
    
    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for playing: %s", strerror(errno));
        is_playing = false;
        return;
    }
    
    uint8_t *play_buffer = (uint8_t *)malloc(RECORD_BUFFER_SIZE);
    if (play_buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate play buffer");
        fclose(f);
        is_playing = false;
        return;
    }
    
    size_t bytes_read;
    while (is_playing) {
        bytes_read = fread(play_buffer, 1, RECORD_BUFFER_SIZE, f);
        if (bytes_read == 0) {
            if (ferror(f)) {
                ESP_LOGE(TAG, "Error reading file: %s", strerror(errno));
            }
            break;
        }
        
        size_t bytes_written;
        if (i2s_write(I2S_NUM_0, play_buffer, bytes_read, &bytes_written, portMAX_DELAY) != ESP_OK) {
            ESP_LOGE(TAG, "i2s_write failed");
            break;
        }
    }
    
    fclose(f);
    free(play_buffer);
    is_playing = false;
    ESP_LOGI(TAG, "Playback finished");
}

void stop_recording(void)
{
    is_recording = false;
}

void stop_playing(void)
{
    is_playing = false;
}