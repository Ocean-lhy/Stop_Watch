idf_component_register(
    SRCS "i2c_expander.c"
    INCLUDE_DIRS "include"
    REQUIRES driver esp_timer freertos
) 