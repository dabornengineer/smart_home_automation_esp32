/**
 * @file dht_sensor.h
 * 
 * @brief header file for Structure and function declaration for the DHT sensor
 */

#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure that holds the configuration for the DHT sensor
 * 
 * This Structure is used to create the instance of the DHT sensor, set the GPIO pin,
 * DHT type and measuring either fahrenheit or celsuis
 */
typedef struct {
    uint8_t dht_pin;            /**< GPIO pin for the DHT pin configuration */
    uint8_t dht_type;           /**< The type of the DHT sensor(DH11, DHT22) or more */
    bool read_fahrenheit;       /**< configure the Tempearature to read °F(true) or °C(false). */
} dht_config_t;

/**
 * @brief DHT function declaration
 * 
 * The function is used to create FreeRTOS task for the DHT sensor, it measures the Tempearture
 * and Humidity values and logs the readng
 * 
 * @param pvParameters is a pointer to the sensors configuration 
 */
void dhtSensorTask(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif //DHT_SENSOR_H
