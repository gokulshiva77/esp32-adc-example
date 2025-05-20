#ifndef __I2C_SENSOR_H__
#define __I2C_SENSOR_H__

#include <esp_err.h>

// Initialize I2C sensor
void i2c_sensor_init(void);
// Read data from I2C sensor
int i2c_sensor_read(void);
// Deinitialize I2C sensor
void i2c_sensor_deinit(void);

#endif // __I2C_SENSOR_H__
