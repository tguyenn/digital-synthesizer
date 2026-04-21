#include "encoder.h"
#include <ti/devices/msp/msp.h>
#include <ti/driverlib/dl_gpio.h>


// IOMUX Indices for MSPM0G3507
#define PB13INDEX 27
#define PB15INDEX 31
#define PB16INDEX 32

void encoderInit(void){
// 1. Configure Pin Muxing (Same as before)
    IOMUX->SECCFG.PINCM[PB16INDEX] = 0x00060081; // DT (PB16)
    IOMUX->SECCFG.PINCM[PB15INDEX] = 0x00060081; // CLK (PB15)
    IOMUX->SECCFG.PINCM[PB13INDEX] = 0x00060081; // SW (PB13)

    // 2. Set Directions to Input
    GPIOB->DOE31_0 &= ~((1 << 16) | (1 << 15) | (1 << 13));

    // 3. Configure Polarity (Falling Edge = 0x2 for each pin)
    // PB15 is bits 31:30 -> (2 << 30) = 0x80000000
    // PB13 is bits 27:26 -> (2 << 26) = 0x08000000
    GPIOB->POLARITY15_0 = 0x88000000; 

    // 4. Clear and Arm (Mask) interrupts
    GPIOB->CPU_INT.ICLR = (1 << 15) | (1 << 13);  
    GPIOB->CPU_INT.IMASK = (1 << 15) | (1 << 13); 

    // 5. NVIC Configuration
    // Set priority for IRQ 1 (Group1/Port B)
    NVIC->IP[0] = (NVIC->IP[0] & (~0x0000FF00)) | (2 << 14); 
    // Enable Group1 interrupt (Port B)
    NVIC->ISER[0] = (1 << 1);
}