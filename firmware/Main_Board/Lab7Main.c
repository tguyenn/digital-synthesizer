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

void initLCD(void) {
  ST7735_InitR(INITR_REDTAB);
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
  I2C_Init();
  //initUART();
  // DAC_Init();
  //TimerG6_IntArm(10, 0, 0); // sound test
  // TimerG7_IntArm(UINT16_MAX, 0, 0); // blinky
  
  __enable_irq();
  while(1){
    // readUART0();
   // UART_OutChar('a');

    // char lol = UART_InChar();
    // lol++;
    // lol++;
    // lol++;
    // lol++;
    
    // ST7735_FillScreen(0);
    // DAC_Out(2048);
  }
}