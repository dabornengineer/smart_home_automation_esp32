/**
 * @file ldr_sensor.h
 * @brief LDR sensor configurations and function declaration
 */
#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A Structure that holds the configuration parameters of the LDR sensor
 */
typedef struct {
    uint8_t ldr_gpio_pin;     /**< The GPIO pin the LDR sensor is connected to */
} ldr_config_t;

/**
 * @brief Task for reading LDR sensors value
 * @param 'pvParameters' Pointer that takes the sensor configuration(ldr_config_t)
 * as argument
 */
void ldrSensorTask(void *pvParameters);

/**
 * 
 */
float getFilteredLDR(uint16_t ldr_raw, float previous_fil_value, float alpha);

#ifdef __cplusplus
}
#endif

#endif //LDR_SENSOR_H