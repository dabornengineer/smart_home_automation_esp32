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
    TickType_t xFrequency = pdMS_TO_TICKS(1000);

    pinMode(pir_cfg->pir_data_pin, INPUT);

    while (1)
    {
        pir_pin_state = (pir_state_t) digitalRead(pir_cfg->pir_data_pin);
        if(pir_pin_state != PIR_STATE_NO_MOTION && pir_pin_state != PIR_STATE_MOTION)
        {
            ESP_LOGE(TAG, "Invalid pin state: %d", pir_pin_state);
        }
        else
        {
            //log only if state have changed, to prevent continues logging
            if (pir_pin_state != latest_reading)
            {
                latest_reading = pir_pin_state;
                if (pir_pin_state == PIR_STATE_NO_MOTION)
                    ESP_LOGI(TAG, "[pin %d] Motion not detected", pir_cfg->pir_data_pin);
                else
                    ESP_LOGI(TAG, "[pin %d] Motion detected", pir_cfg->pir_data_pin);
            }
        }
        vTaskDelayUntil(&xPreviousWakeTime, xFrequency);
    }
} 