#include <Arduino.h>
#include <stdlib.h>
#include <DHT.h>
#include <esp_log.h>
#include "dht_sensor.h"
#include "pir_sensor.h"

void setup() {
  Serial.begin(115200);
  dht_config_t *dht_cfg = (dht_config_t *) calloc(1, sizeof(dht_config_t));
  pir_config_t *pir_cfg = (pir_config_t *) calloc(1, sizeof(pir_config_t));

  if (!dht_cfg)
  {
    ESP_LOGE("DHT", "Memory allocation failed");
    return;
  }
  dht_cfg->dht_pin = 4;
  dht_cfg->dht_type= DHT11;
  dht_cfg->read_fahrenheit = false;

  if (!pir_cfg)
  {
    ESP_LOGE("PIR_SENSOR", "Memory allocation failed");
    return;
  }
  pir_cfg->pir_data_pin = 13;

  xTaskCreate(dhtSensorTask, "DHT task", 4096, dht_cfg, 1, NULL);
  xTaskCreate(pirSensorTask, "PIR SENSOR TASK", 4096, pir_cfg, 3, NULL);
}

void loop() {
  vTaskDelete(NULL);
}
