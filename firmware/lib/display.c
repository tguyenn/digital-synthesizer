#include "display.h"
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "encoder.h"

#define NUM_MENU_ITEMS 4
#define CURSOR_X 6    
#define START_Y 5

extern volatile int32_t menu_pos;
static char* instrument_name;

void instrumentSelection(void){
    if (menu_pos == 0){
        instrument_name= "Piano";
    }
    if (menu_pos == 1){
        instrument_name= "Trumpet";
    }
    if (menu_pos == 2 ){
        instrument_name= "Flute";
    }
    if (menu_pos == 3 ){
        instrument_name= "Oboe";
    }
}

void drawSelectedInstrument(void){
    instrumentSelection();
    ST7735_FillScreen(ST7735_BLACK);

    ST7735_DrawString(2, START_Y , "You have selected: ", ST7735_WHITE);
    ST7735_DrawString(8, START_Y + 2, (char *)instrument_name, ST7735_WHITE);
    ST7735_DrawString(1, START_Y + 6, "Press Switch to Exit", ST7735_WHITE);
}

void drawMenu(void){
    static int32_t prev_menu_pos;
    
    if (menu_pos < 0){
        menu_pos = NUM_MENU_ITEMS - 1;        
    } 
    
    if (menu_pos >= NUM_MENU_ITEMS){
        menu_pos = 0; 
    }
    
    if (menu_pos != prev_menu_pos){
        ST7735_DrawString(CURSOR_X, START_Y + prev_menu_pos, ">", ST7735_BLACK);
        ST7735_DrawString(CURSOR_X, START_Y + menu_pos, ">", ST7735_WHITE);

        prev_menu_pos = menu_pos;
    }
}

void resetMenu(void){
    menu_pos=0;
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_DrawString(8, START_Y, "Piano", ST7735_WHITE);
    ST7735_DrawString(8, START_Y + 1, "Trumpet", ST7735_WHITE);
    ST7735_DrawString(8, START_Y + 2, "Flute", ST7735_WHITE);
    ST7735_DrawString(8, START_Y + 3, "Oboe", ST7735_WHITE);

    ST7735_DrawString(CURSOR_X, START_Y, ">", ST7735_WHITE);
    ST7735_DrawString(6, START_Y + 6, "Press Switch", ST7735_WHITE);
    ST7735_DrawString(7, START_Y + 7, "to Select", ST7735_WHITE);
}

void initLCD(void) {
    ST7735_InitR(INITR_REDTAB);
    resetMenu();
}
