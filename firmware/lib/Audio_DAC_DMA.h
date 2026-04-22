#pragma once

#define AUDIO_BUF_SIZE 256
#define FULL_BUFFER_SIZE (AUDIO_BUF_SIZE * 2)

void setupPingPongDMA();

void DMA_IRQHandler(void);
