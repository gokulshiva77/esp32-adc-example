#include "sensor_handler.h"


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_log.h>
#include <esp_err.h>

#include "adc_sensor.h"

#define TAG "SENSOR_HANDLER"
#define MAX_SENSORS 10  // Maximum number of sensors we can register

// Array to store multiple sensor read functions
sensor_read_func_t sensor_read_funcs[MAX_SENSORS];
// Keep track of how many sensor functions we've registered
uint8_t num_sensors = 0;

static TaskHandle_t sensor_task_handle = NULL;

void sensor_register_func(sensor_read_func_t func);
void sensor_deregister_func(sensor_read_func_t func);
void sensor_read_all(void);

static void sensor_task(void *pvParameters);
void sensor_start_task(void);
void sensor_stop_task(void);

static void sensor_task(void *pvParameters)
{
    while (1) {
        sensor_read_all();
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1 second delay
    }
}

void sensor_start_task(void)
{
    if (sensor_task_handle == NULL) {
        xTaskCreate(sensor_task, "sensor_task", 2048, NULL, 5, &sensor_task_handle);
    }
}

void sensor_stop_task(void)
{
    if (sensor_task_handle != NULL) {
        vTaskDelete(sensor_task_handle);
        sensor_task_handle = NULL;
    }
}

void sensor_init(void)
{
    // Initialize the array
    for (int i = 0; i < MAX_SENSORS; i++) {
        sensor_read_funcs[i] = NULL;
    }
    
    // Init ADC Sensor
    adc_unit_t unit = ADC_UNIT_1;
    adc_channel_t channel = ADC_CHANNEL_0; // GPIO 36
    adc_init(unit, channel);
    ESP_LOGI(TAG, "ADC Sensor initialized on Unit %d, Channel %d", unit, channel);
    // Register the ADC sensor read function
    sensor_register_func(&get_adc_sensor_data);
    ESP_LOGI(TAG, "ADC Sensor read function registered");

    // Start the sensor task
    sensor_start_task();
    ESP_LOGI(TAG, "Sensor task started");
}

void sensor_register_func(sensor_read_func_t func)
{
    if (num_sensors >= MAX_SENSORS) {
        ESP_LOGE(TAG, "%s Failed to register sensor function: maximum reached", __func__);
        return;
    }
    
    if (func == NULL) {
        ESP_LOGE(TAG, "%s Attempted to register NULL function", __func__);
        return;
    }
    
    sensor_read_funcs[num_sensors++] = func;
    ESP_LOGI(TAG, "%s Registered sensor function #%d", __func__, num_sensors);
}

void sensor_deregister_func(sensor_read_func_t func)
{
    if (num_sensors == 0) {
        ESP_LOGE(TAG, "%s Empty sensor functions", __func__);
        return;
    }
    if (func == NULL) {
        ESP_LOGE(TAG, "%s Attempted to Deregister NULL function", __func__);
        return;
    }
    for (int i = 0; i < num_sensors; i++) {
        if (sensor_read_funcs[i] == func) {
            // Shift remaining functions down
            for (int j = i; j < num_sensors - 1; j++) {
                sensor_read_funcs[j] = sensor_read_funcs[j + 1];
            }
            sensor_read_funcs[--num_sensors] = NULL; // Clear the last entry
            ESP_LOGI(TAG, "%s Deregistered sensor function #%d", __func__, i + 1);
            return;
        }
    }
}

void sensor_read_all(void)
{
    ESP_LOGI(TAG, "Reading data from %d sensors", num_sensors);
    
    for (int i = 0; i < num_sensors; i++) {
        if (sensor_read_funcs[i] != NULL) {
            ESP_LOGI(TAG, "Reading from sensor #%d", i + 1);
            sensor_read_funcs[i]();  // Call the function
        }
    }
}

void sensor_deinit(void)
{
    // Reset the array and counter
    for (int i = 0; i < MAX_SENSORS; i++) {
        sensor_read_funcs[i] = NULL;
    }
    num_sensors = 0;
    ESP_LOGI(TAG, "Sensor handler deinitialized");
}
