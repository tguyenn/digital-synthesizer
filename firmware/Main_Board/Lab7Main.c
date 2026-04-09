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

void PLL_Init(void) { // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

void TIMG7_IRQHandler() {
  GPIOA->DOUTTGL = (1 << 16);
  // GPIOA->DOUTTGL = (1 << 18);  
}

void initLED(void){

  // PA16, LP
  IOMUX->SECCFG.PINCM[PA16INDEX] = 0x00000081; // regular output
  GPIOB->DOE31_0 |= 0x10000;
  // PA18, CHIP
  // IOMUX->SECCFG.PINCM[PA18INDEX] = 0x00000081; // regular output
  // GPIOB->DOE31_0 |= 0x40000;

  TimerG7_IntArm(UINT16_MAX, 0, 0);
}



int main(void){ // main1
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  initLED();
  __enable_irq();
  while(1){
    
  }
}

// // use main4 to test OutFix functions
// // connect slidepot pin 2 to PB18
// // Data should go from 0 to 4095
// // Position should go from 0 to 2000
// // LCD should show 0.000cm to 2.000 cm
// // OutFixtime is the time to execute OutFix in bus cycles
// int main4(void){ // main4
//   __disable_irq();
//   PLL_Init(); // set bus speed
//   LaunchPad_Init();
//   ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
//   ST7735_FillScreen(ST7735_BLACK);
//   SysTick->LOAD = 0xFFFFFF;    // max
//   SysTick->VAL = 0;            // any write to current clears it
//   SysTick->CTRL = 0x00000005;  // enable SysTick with core clock
//   startTime = SysTick->VAL;
//   stopTime = SysTick->VAL;
//   Offset = (startTime-stopTime)&0x0FFFFFF; // in bus cycles to perform time measurement
//   ADCinit(); //PB18 = ADC0 channel 5, slidepot
//   while(1){
//     ST7735_SetCursor(0,0); // top left
//     Data = ADCin();  // sample 12-bit ADC0 channel 5, slidepot
//     Position = Convert(Data);
//     FloatPosition = FloatConvert(Data);
//     startTime = SysTick->VAL;
//     OutFix(Position);
//     stopTime = SysTick->VAL;
//     OutFixtime = ((startTime-stopTime)&0x0FFFFFF)-Offset; // in bus cycles
//     ST7735_SetCursor(0,1); // second row
//     startTime = SysTick->VAL;
//     FloatOutFix(FloatPosition);
//     stopTime = SysTick->VAL;
//     FloatOutFixtime = ((startTime-stopTime)&0x0FFFFFF)-Offset; // in bus cycles
//     Clock_Delay1ms(100);
//   }
// }
// // sampling frequency is 30 Hz
// void TIMG12_IRQHandler(void){
//   if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
//     GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
//     GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
//     Time++;
//     // sample 12-bit ADC0 channel 5, slidepot
//     // store data into mailbox
//     // set the semaphore
//     GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
//   }
// }
// uint8_t TExaS_LaunchPadLogicPB27PB26(void){
//   return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
// }
// // use main5 for final system
// // use scope or logic analyzer to verify real time samples
// // option 1) remove call to TExaS_Init and use a real scope on PB27
// // option 2) use TExaS logic analyzer
// int main5(void){ // main5
//   __disable_irq();
//   PLL_Init(); // set bus speed
//   LaunchPad_Init();
//   ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
//   ST7735_FillScreen(ST7735_BLACK);
//   ADCinit(); //PB18 = ADC1 channel 5, slidepot
//   TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
//   ST7735_PlotClear(0,2000);
//     // initialize interrupts on TimerG12 at 30 Hz

//   // initialize semaphore

//   Time = 0;
//   __enable_irq();
//   while(1){
//       // write this

//     // wait for semaphore
//     // clear the semaphore
//     GPIOB->DOUTTGL31_0 = RED; // toggle PB26 (minimally intrusive debugging)
//     // toggle red LED2 on Port B, PB26
//      // convert Data to Position
//      // move cursor to top
//     // display distance in top row OutFix

//     Time++;
//     if((Time%15)==0){
//       ST7735_PlotPoint(Position);
//       ST7735_PlotNextErase(); // data plotted at about 2 Hz
//     }
//   }
// }

// // use main6 to study Central Limit Theorem
// uint32_t Histogram[64]; // probability mass function
// uint32_t Center,SAC;
// #define SCALE 2000
// int main6(void){ // main6
//   __disable_irq();
//   PLL_Init(); // set bus speed
//   LaunchPad_Init();
//   ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
//   ST7735_FillScreen(ST7735_BLACK);
//   ADCinit(); //PB18 = ADC1 channel 5, slidepot
//   SAC = 1;
//   while(1){int i; uint32_t d,sum;
//     sum = 0;
//     for(int j=0; j<100; j++){
//       sum += ADCin();  // sample 12-bit ADC0 channel 5, slidepot
//     }
//     Center = sum/100; // averaging
//     for(i=0; i<64; i++) Histogram[i] = 0; // clear
//     for(i=0; i<200; i++){
//       sum = 0;
//       for(int j=0; j<SAC; j++){
//         sum += ADCin();  // sample 12-bit ADC0 channel 5, slidepot
//       }
//       Data = sum/SAC; // averaging
//       if(Data<Center-32){
//          Histogram[0]++;
//       }else if(Data>=Center+32){
//          Histogram[63]++;
//       }else{
//         d = Data-Center+32;
//         Histogram[d]++;
//       }
//     }
//     ST7735_PlotClear(0,100);
//     ST7735_SetCursor(0,0);
//     printf("SAC=%3u,Center=%4u",SAC,Center);
//     for(i=0; i<63; i++){
//       if(Histogram[i]>99) Histogram[i]=99;
//       ST7735_PlotBar(Histogram[i]);
//       ST7735_PlotNext();
//       ST7735_PlotBar(Histogram[i]);
//       ST7735_PlotNext();
//     }
//     while(LaunchPad_InS2()==0x00040000){}; // wait for release
//     while(LaunchPad_InS2()==0){};          // wait for touch
//     SAC = SAC<<1;
//     if(SAC >= 256) SAC = 1;
//   }
// }

