idf_component_register(SRCS "main.c" "adc_wrapper.c"
                    PRIV_REQUIRES spi_flash esp_adc
                    INCLUDE_DIRS "./")
