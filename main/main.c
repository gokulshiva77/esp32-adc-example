/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "adc_wrapper.h"

void adc_task(void *pvParameter)
{
    adc_unit_t unit = ADC_UNIT_1;
    adc_channel_t channel = ADC_CHANNEL_0;

    adc_init(unit, channel);
    while (1) {
        int value = adc_read_channel(unit, channel);
        printf("ADC Unit - %d, Channel [%d] : %d\n", unit,channel, value);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(adc_task, "adc_task", 2048, NULL, 5, NULL);
}
