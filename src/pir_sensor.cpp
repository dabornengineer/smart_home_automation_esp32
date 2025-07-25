#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Arduino.h>
#include <esp_log.h>
#include "pir_sensor.h"

#define PIN_MODE INPUT
void pirSensorTask(void *pvParameters)
{
    pir_config_t *pir_cfg = (pir_config_t *) pvParameters;
    uint8_t pir_pin_state;

    pinMode(pir_cfg->pir_data_pin, PIN_MODE);
} 