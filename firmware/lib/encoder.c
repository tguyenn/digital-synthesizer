#include <encoder.h>
#include <ti/devices/msp/msp.h>

///make a struct with all of the next states
void encoderInit(void){
   //ENC 1 DT- PB16
  IOMUX->SECCFG.PINCM[PB16INDEX] = 0x00060081;
  GPIOB->DOE31_0 &= ~(1 << 16); // input

   //CLK- PB15
  IOMUX->SECCFG.PINCM[PB15INDEX] = 0x00060081;
  GPIOA->DOE31_0 &= ~(1 << 15); // input

  //SW- PB13
  IOMUX->SECCFG.PINCM[PB13INDEX] = 0x00060081;
  GPIOA->DOE31_0 &= ~(1 << 13); // input

  //Falling edge triggered interrupt on CLK
  GPIOB->CPU_INT.IBE31_0 &= ~(1 << 15);   // single edge
  GPIOB->CPU_INT.IEV31_0 &= ~(1 << 15);   // falling edge
  GPIOB->CPU_INT.ICLR31_0 =  (1 << 15);   // clear flag
  GPIOB->CPU_INT.IMASK31_0 |= (1 << 15);  // unmask

  //Falling edge triggered interrupt on SW
  GPIOB->CPU_INT.IBE31_0 &= ~(1 << 13);
  GPIOB->CPU_INT.IEV31_0 &= ~(1 << 13);
  GPIOB->CPU_INT.ICLR31_0 =  (1 << 13);
  GPIOB->CPU_INT.IMASK31_0 |= (1 << 13);

  // Enable interrupt for port B
  NVIC->ISER[0] = (1 << 1);
}

void 