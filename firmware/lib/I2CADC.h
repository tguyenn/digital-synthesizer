#ifndef I2CADC_H
#define I2CADC_H

#include <stdint.h>

#define TOTAL_KEYS 60

typedef struct {
    uint16_t velocity[TOTAL_KEYS];
    uint16_t position[TOTAL_KEYS];
} ADCoutput_t;

extern int16_t prev_displacement[TOTAL_KEYS];

void initADC(void);
void initMux(void);
void updateSingleKeyVal(void);
void TIMA1_IRQHandler();

#endif