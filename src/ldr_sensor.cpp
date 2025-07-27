/**
 * @file ldr_sensor.cpp
 * @brief defines the task that handles the redaing of the ldr sensors analogue values
 */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <Arduino.h>
#include "ldr_sensor.h"

#define ALPHA 0.2 //co-efficient for exponential smoothing

static const char *TAG = "LDR_SENSOR";
/**
 * @brief ldr sensor task 
 * 
 * @param pvParameters pointer to the sensors configurations
 */
void ldrSensorTask(void *pvParameters)
{
    ldr_config_t *ldr_cfg = (ldr_config_t *) pvParameters;
    uint16_t ldr_raw;
    float filteredValue = 0;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    TickType_t xFrequency = pdMS_TO_TICKS(1000);

    pinMode(ldr_cfg->ldr_gpio_pin, INPUT);
    while (1)
    {
        ldr_raw = analogRead(ldr_cfg->ldr_gpio_pin);
        filteredValue = getFilteredLDR(ldr_raw, filteredValue, ALPHA);
        ESP_LOGI(TAG, "LDR sensor filtered value: %.1f", filteredValue);
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
    free(ldr_cfg);
    vTaskDelete(NULL);
}

/**
 * @brief filters the ADC value using moving average
 * 
 * @param ldr_raw the raw ADC value
 * @param previous_fil_value the previous filter reading
 * @param alpha coefficient for filter value sensitivity
 */
float getFilteredLDR(uint16_t ldr_raw, float previous_fil_value, float alpha)
{
    return ((ldr_raw * alpha) +((1 - alpha) * previous_fil_value));
}