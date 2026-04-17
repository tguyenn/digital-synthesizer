// Lab7Main.c
// Runs on MSPM0G3507
// Lab 7 
// Last Modified: January 12, 2026

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>

#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/ST7735.h"

#include "../inc/UART.h"
#include "../lib/myUART.h"
#include "../inc/DAC.h"

// launchpad pins
// #define SEL0 20 // PB20
// #define SEL1 24 // PB24
// #define SEL2 3 // PB3
// #define SEL3 4 // PB4
// #define RUN_LED 16 // PA16

// chip pins
#define SEL0 12 // PA12
#define SEL1 22 // PA13
#define SEL2 13 // PA22
#define SEL3 16 // PA16
#define RUN_LED 18 // PA18

const uint16_t Wave16[16] = {
  2048, 2441, 2772, 3004, 3072, 3004, 2772, 2441, 
  2048, 1655, 1324, 1092, 1024, 1092, 1324, 1655
};

void PLL_Init(void) { // set phase lock loop (PLL)
  // Clock_Init80MHz(0); 
  Clock_Init80MHz_Internal(); //MSP chip only
}

void initHeart(void){
  // PA16, LP RUN LED
  // IOMUX->SECCFG.PINCM[PA16INDEX] = 0x00000081;
  // GPIOA->DOE31_0 |= (1 << 16);
  // TimerG7_IntArm(UINT16_MAX, 0, 0);
  
  // PA18, CHIP RUN LED
  IOMUX->SECCFG.PINCM[PA18INDEX] = 0x00000081;
  GPIOA->DOE31_0 |= (1 << 18);

  // test todo :delete
  IOMUX->SECCFG.PINCM[PA22INDEX] = 0x00000081;
  GPIOA->DOE31_0 |= (1 << 22);
}

void initMux(void) {
  // LP PB24, PB20, PB4, PB3 -> S0, S1, S2, S3
  // GPIOB->DOE31_0 |= (1 << SEL0) | (1 << SEL1) | (1 << SEL2) | (1 << SEL3);
  // IOMUX->SECCFG.PINCM[PB24INDEX] = 0x00000081;
  // IOMUX->SECCFG.PINCM[PB20INDEX] = 0x00000081;
  // IOMUX->SECCFG.PINCM[PB4INDEX] = 0x00000081;
  // IOMUX->SECCFG.PINCM[PB3INDEX] = 0x00000081;

  // chip PA12, PA13, PA22, PA16
  GPIOA->DOE31_0 |= (1 << SEL0) | (1 << SEL1) | (1 << SEL2) | (1 << SEL3);
  IOMUX->SECCFG.PINCM[PA12INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PA13INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PA22INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PA16INDEX] = 0x00000081;
}

void initLCD(void) {
  ST7735_InitR(INITR_REDTAB);
}

void incrementMux(void) {
  // cycle through hall sensor with mux selection lines
  static uint8_t count = 0;
  if(count > 12) { // we only need 12 out of the 16 mux inputs
    count = 0;
  }
  uint8_t count0 = count & 1;
  uint8_t count1 = (count & (1 << 1)) >> 1;
  uint8_t count2 = (count & (1 << 2)) >> 2;
  uint8_t count3 = (count & (1 << 3)) >> 3;

  // LPAD
  // GPIOB->DOUTCLR31_0 = (1 << SEL0) | (1 << SEL1) | (1 << SEL2) | (1 << SEL3);
  // GPIOB->DOUTSET31_0 = (count0 << SEL0) | (count1 << SEL1) | (count2 << SEL2) | (count3 << SEL3);

  // CHIP
  GPIOA->DOUTCLR31_0 = (1 << SEL0) | (1 << SEL1) | (1 << SEL2) | (1 << SEL3);
  GPIOA->DOUTSET31_0 = (count0 << SEL0) | (count1 << SEL1) | (count2 << SEL2) | (count3 << SEL3);
  count++;
}

void toggleHeart(void) {
  // GPIOA->DOUTTGL31_0 ^= (1 << RUN_LED); //heartbeat
  GPIOA->DOUTTGL31_0 ^= (1 << 22); //heartbeat
}

void TIMG6_IRQHandler() {
  static uint16_t i = 0;
  DAC0->DATA0 = Wave16[i++ % 16];
} 

void TIMG7_IRQHandler() {
  incrementMux();
  toggleHeart();
}

int main(void){ // main1
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  // initHeart();
  // initMux();
  // initLCD();
  initUART();
  // DAC_Init();
  TimerG6_IntArm(10, 0, 0); // sound test
  // TimerG7_IntArm(UINT16_MAX, 0, 0); // blinky
  
  __enable_irq();
  while(1){
    // readUART0();
    UART_OutChar('a');

    char lol = UART_InChar();
    lol++;
    lol++;
    lol++;
    lol++;
    
    // ST7735_FillScreen(0);
    // DAC_Out(2048);
  }
}