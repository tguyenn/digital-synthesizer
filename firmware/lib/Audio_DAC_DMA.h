//Audio_DAC_DMA.h
#pragma once

#include <stdbool.h>

#define AUDIO_BUF_SIZE 256
#define AUDIO_TOTAL_SIZE (AUDIO_BUF_SIZE * 2)

extern volatile bool refillPing;
extern volatile bool refillPong;
extern volatile int16_t audioBuffer[AUDIO_TOTAL_SIZE];

void TimerG0_32kHz_EventArm(void);

void DAC0_Init(void);

void DMA_Init_CircularPingPong();

void DMA_IRQHandler(void);