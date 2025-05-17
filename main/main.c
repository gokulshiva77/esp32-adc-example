/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "adc_wrapper.h"

#define TAG "main"

void adc_task(void *pvParameter)
{
    adc_unit_t unit = ADC_UNIT_1;
    adc_channel_t channel = ADC_CHANNEL_0;

    adc_init(unit, channel);
    while (1) {
        int value = adc_read_channel(unit, channel);
        if (value < 0) {
            ESP_LOGE(TAG, "%s Failed to read ADC value for Unit - %d, Channel - %d", __func__, unit, channel);
        } else {
            ESP_LOGI(TAG, "%s ADC Unit - %d, Channel [%d] : %d", __func__, unit, channel, value);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "%s Starting ADC Example", __func__);
    ESP_LOGI(TAG, "%s Starting ADC Task with FreeRTOS", __func__);
    xTaskCreate(adc_task, "adc_task", 2048, NULL, 5, NULL);
}
