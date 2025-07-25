#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t pir_data_pin;
} pir_config_t;
void pirSensorTask(void *pvParameters);

#ifdef __cplusplus
}
#endif
#endif