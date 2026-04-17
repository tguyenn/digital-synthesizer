


// run through velocity array
// if velocity > some threshold, then trigger led pulse
// TODO write function that scans 

// TODO write DMA code that outputs the data buffer ledArr

struct {
    uint8_t r,
    uint8_t g,
    uint8_t b,
} typedef stripLed;

stripLed ledArr[60];

void writeLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
    ledArr[index].r = r;
    ledArr[index].g = g;
    ledArr[index].b = b;
}

void initLedStrip() {
    
}
// big buffer version
// expects 0 indexed input
void writeLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
    ledArr[index * 24]
}


// 60 LEDs, 24 bits each -> 60 * 24 = 1440 bits
uint16_t ledArr[1440]; // each element represents one bit, which will be output by a DMA timer to bit bang the WS2812B protocol
void outputColors() {
    
}

