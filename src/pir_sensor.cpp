/**
 * @file pir_sensor.cpp
 * 
 * @brief PIR sensor implementation using FreeRTOS and arduino framework
 * 
 * It implements the use of PIR sensor in reading the state of enviroment(MOTION OR NO MOTION)
 * and carries out it task depending on the state of the system
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Arduino.h>
#include <esp_log.h>
#include "pir_sensor.h"

#define PIR_SENSOR_TIMEOUT_MS pdMS_TO_TICKS(5000)
static const char *TAG = "PIR_SENSOR";

/**
 * @brief PIR sensor that that checks for the state of the system
 * 
 * The task checks weather 'MOTION' is detected or 'NO MOTION' is detected through the digital
 * pin 'pin_cfg->pir_data_pin' of the MCU, it performs specific task according to the read by
 * the MCU
 * 
 * @param 'pvParameters' a pointer to the instance of the pir sensor configuration 'pir_config_t'
 * 
 */
void pirSensorTask(void *pvParameters)
{
    pir_config_t *pir_cfg = (pir_config_t *) pvParameters;
    if (!pir_cfg)
    {
        ESP_LOGE(TAG, "Configuration failed");
        vTaskDelete(NULL);
    }
    pir_state_t pir_pin_state = PIR_STATE_INVALID;
    pir_state_t latest_reading = PIR_STATE_INVALID;
    TickType_t xPreviousWakeTime = xTaskGetTickCount();
    TickType_t xFrequency = pdMS_TO_TICKS(500);
    TickType_t last_motion_tick = 0;
    TickType_t current_tick = 0;

    pinMode(pir_cfg->pir_data_pin, INPUT);

    while (1)
    {
        pir_pin_state = (pir_state_t) digitalRead(pir_cfg->pir_data_pin);
        current_tick = xTaskGetTickCount();

        if (latest_reading == PIR_STATE_INVALID)
        {
            if (pir_pin_state == HIGH)
            {
                ESP_LOGI(TAG, "[pin %d] Motion detected", pir_cfg->pir_data_pin);
                last_motion_tick = current_tick;
                latest_reading = PIR_STATE_MOTION;
            }
            else
            {
                ESP_LOGI(TAG, "[pin %d] No motion detected", pir_cfg->pir_data_pin);
                latest_reading = PIR_STATE_NO_MOTION;
            }
        }
        else
        {
            if (pir_pin_state == HIGH)
            {
                last_motion_tick = current_tick;
                // log only if state chnages to avoid multiple loggind
                if (latest_reading != PIR_STATE_MOTION)
                {
                    ESP_LOGI(TAG, "[pin %d] Motion detected", pir_cfg->pir_data_pin);
                    latest_reading = PIR_STATE_MOTION;
                }
            }
            else if (latest_reading == PIR_STATE_MOTION && (current_tick - last_motion_tick > PIR_SENSOR_TIMEOUT_MS))
            {
                //ESP_LOGI(TAG, "[pin %d] Motion ended...", pir_cfg->pir_data_pin);
                latest_reading = PIR_STATE_INVALID;
            }
        }
        vTaskDelayUntil(&xPreviousWakeTime, xFrequency);
    }
    free(pir_cfg);
    vTaskDelete(NULL);
} 