#include "I2CADC.h"

uint16_t keyLastValue[TOTAL_KEYS]; // Stores previous ADC value
uint32_t keyStartTime[TOTAL_KEYS]; // Stores time stamp when pressed
uint8_t  keyIsPressed[TOTAL_KEYS]; // Boolean: is the key currently down?

uint8_t addresses[5] = {0x48, 0x49, 0x4A, 0x4C,0x4D};

typedef struct ADCoutput_t{
    uint16_t velocity[60];
    uint16_t position[60];
};

void initADC(void){
    initMux();
    
    
}

void initMux(void) {
  // LP PB24, PB20, PB4, PB3 -> S0, S1, S2, S3
  GPIOB->DOE31_0 |= (1 << SEL0) | (1 << SEL1) | (1 << SEL2) | (1 << SEL3);
  IOMUX->SECCFG.PINCM[PB24INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB20INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB4INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB3INDEX] = 0x00000081;

  // chip PA12, PA13, PA22, PA16
//   GPIOA->DOE31_0 |= (1 << SEL0) | (1 << SEL1) | (1 << SEL2) | (1 << SEL3);
//   IOMUX->SECCFG.PINCM[PA12INDEX] = 0x00000081;
//   IOMUX->SECCFG.PINCM[PA13INDEX] = 0x00000081;
//   IOMUX->SECCFG.PINCM[PA22INDEX] = 0x00000081;
//   IOMUX->SECCFG.PINCM[PA16INDEX] = 0x00000081;
}

//gets msb and lsb via I2C from whatever data passed by muxes
uint16_t readADC(int8_t address) {
    uint8_t msb
    uint8_t lsb;
    
    while((I2C1->MASTER.MSR & 0x20) == 0){}; 
    
    // Set address and direction (1 for Receive)
    I2C1->MASTER.MSA = (address << 1) | 0x01; 
    
    // MBLEN=2, ACK, STOP, START, BURSTRUN bits
    I2C1->MASTER.MCTR = 0x00020007; 
    
    // Wait for and read byte 1 (MSB)
    while((I2C1->MASTER.MFIFOSR & 0x000F) == 0){}; 
    msb = I2C1->MASTER.MRXDATA; 
    
    // Wait for and read byte 2 (LSB)
    while((I2C1->MASTER.MFIFOSR & 0x000F) == 0){}; 
    lsb = I2C1->MASTER.MRXDATA;

    // Combine for 12-bit result: (Upper 4 bits are 0) 
    return (((msb & 0x0F)) << 8) | lsb;


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

