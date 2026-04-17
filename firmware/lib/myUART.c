#include "../inc/UART.h"
#include "../inc/UART1.h"
#include "../lib/myUART.h"

#define NUM_KEYS 60

void initUART() {
    UART_Init(); // chip -> LP comms
    UART1_Init(); // to laptop via USB to UART bridge
}

void testUART0() {
    UART1_OutChar('L');
    UART1_OutChar('b');
    UART1_OutChar('o');
    UART1_OutChar('z');
    UART1_OutChar('o');
}

void pushVelData() {
    for(int i = 0; i < NUM_KEYS; i++) {
        // UART_OutChar(velData[i]);
    }
}

// sample 2 sets of key data
    // keypos1, keypos2 uint16_t arrs of len 60
    // keyval res array of len 60

// filtering???

// calcSpeed
    // keyvel[i] = (keypos1[i] - keypos2[i]) / SAMPLE_INTERVAL;