#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t dht_pin;
    uint8_t dht_type;
    bool read_fahrenheit;
} dht_config_t;

void dhtSensorTask(void *pvParameters);


#ifdef __cplusplus
}
#endif

#endif
