/**
 * @file pir_sensor.h
 * 
 * @brief PIR sensor driver interface for motion detection using FreeRTOS and Arduino APIs.
 * 
 * This file provides the initialization, configuration definitions and function declarations
 * for monitoring PIR(passive infrared sensor).
 */

#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for PIR sensor configuration.
 */
typedef struct {
    uint8_t pir_data_pin;   /**< GPIO pin connected to the PIR sensor */
} pir_config_t;

/**
 * @brief Enumeration representing the motion state of the PIR sensor.
 */
typedef enum {     
    PIR_STATE_NO_MOTION = 0,      /**< No motion detected (LOW level logic) */
    PIR_STATE_MOTION,             /**< Motion detected (HIGH level logic) */
    PIR_STATE_INVALID             /**< invalid or uninitialized state */  
} pir_state_t;

/**
 * @brief Task sensor function that reads PIR sensor status and logs motion changes.
 * 
 * a pointer to 'pir_config_t' passed as a parameter.
 * 
 * @param pvParameters pointer to 'pir_config_t' instance.
 */
void pirSensorTask(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif //PIR_SENSOR_H