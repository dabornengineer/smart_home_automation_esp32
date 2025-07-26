/**
 * @file smart_home_automation_esp32.cpp
 * 
 * @brief configures sensors and create task for the different sensors
 * 
 * Uses FreeRTOS to create sensors task with the sensors configuration as argument
 */
#include <Arduino.h>
#include <stdlib.h>
#include <DHT.h>
#include <esp_log.h>
#include "dht_sensor.h"
#include "pir_sensor.h"

/**
 * @brief function that handles the configuration and sensors task creation
 */
void setup() {
  Serial.begin(115200);
  dht_config_t *dht_cfg = (dht_config_t *) calloc(1, sizeof(dht_config_t));
  pir_config_t *pir_cfg = (pir_config_t *) calloc(1, sizeof(pir_config_t));

  if (!dht_cfg)
  {
    ESP_LOGE("DHT", "Memory allocation failed");
    return;
  }
  dht_cfg->dht_pin = 4;               //DHT sensor GPIO pin
  dht_cfg->dht_type= DHT11;           //DHT sensor type
  dht_cfg->read_fahrenheit = false;   //read celsuis value(false) or fahrenheit(true)

  if (!pir_cfg)
  {
    ESP_LOGE("PIR_SENSOR", "Memory allocation failed");
    return;
  }
  pir_cfg->pir_data_pin = 13;        //PIR sensor GPIO pin

  xTaskCreate(dhtSensorTask, "DHT task", 4096, dht_cfg, 1, NULL);
  xTaskCreate(pirSensorTask, "PIR SENSOR TASK", 4096, pir_cfg, 3, NULL);
}

void loop() {
  vTaskDelete(NULL);
}
