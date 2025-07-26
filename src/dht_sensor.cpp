/**
 * @file dht_sensor.cpp
 * 
 * @brief implemetation of DHT sensor function Task That measures and logs
 * the tempearature and humidity values.
 * 
 * The FreeRTOS task measures the Temperature and humidity reading of the DHT11
 * sensor and logs the value of the measured temperature and humidity value.
 * 
 * @param 'pvParameters' a pointer to the DHT sensor configurature
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <math.h>
#include <esp_log.h>
#include "dht_sensor.h"

#define TAG "DHT"
#define DHT_READ_INTERVAL_MS 2000
#define MAX_FAILURE_COUNT 10  //max number of fialing to read the sensors value before quiting


/**
 * @brief DHT function declaration
 * 
 * The function is used to create FreeRTOS task for the DHT sensor, it measures the Tempearture
 * and Humidity values and logs the readng
 * 
 * @param pvParameters is a pointer to the sensors configuration(pir_config_t)
 */
void dhtSensorTask(void *pvParameters)
{
    dht_config_t *dht_cfg = (dht_config_t *) pvParameters;
    if (!dht_cfg)
    {
        ESP_LOGE(TAG, "DHT config is NULL, task is exiting...");
        vTaskDelete(NULL);
    }
    DHT dht(dht_cfg->dht_pin, dht_cfg->dht_type);
    dht.begin();

    const char *unit = dht_cfg->read_fahrenheit? "°F": "°C";
    uint8_t count_failure = 0;
    float temperature_celsius = NAN;
    float humidity_percent = NAN;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    TickType_t xFrequency = pdMS_TO_TICKS(DHT_READ_INTERVAL_MS);

    while(1)
    {
        temperature_celsius = dht.readTemperature(dht_cfg->read_fahrenheit);
        humidity_percent = dht.readHumidity();
        if (isnan(temperature_celsius) || isnan(humidity_percent))
        {
            count_failure++;
            ESP_LOGE(TAG, "sensor failed %d/%d times", count_failure, MAX_FAILURE_COUNT);
            if (count_failure >= MAX_FAILURE_COUNT)
            {
               ESP_LOGE(TAG, "Failed to many times, terminating task...");
               break;
            }
        }
        else
        {
            count_failure = 0;
            ESP_LOGI(TAG, "Temperature: %.1f%s   Humidity: %.1f%%", temperature_celsius, unit, humidity_percent);
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
    free(dht_cfg);
    vTaskDelete(NULL);
}