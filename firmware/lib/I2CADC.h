#ifndef I2CADC_H
#define I2CADC_H

#include <stdint.h>

#define TOTAL_KEYS 60

typedef struct {
    uint16_t velocity[TOTAL_KEYS];
    uint16_t position[TOTAL_KEYS];
} ADCoutput_t;

void initADC(void);
void initMux(void);
uint16_t readADC(uint8_t address);
void incrementMux(void);
ADCoutput_t updateKeyVals(void);


#endif