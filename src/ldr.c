#include "ldr.h"

uint32_t ldr_ms = 450;

extern menuStat_t get_menuStat(void);

void ldr_init(uint32_t ms){
  //adc_init(200);//init alone
  ldr_ms = ms;
  adc_start(adc_ch5);
}
uint16_t ldr_value(void){
  uint16_t ldrVal = 0;
  ldrVal = get_adc_value(adc_ch5);
  return ldrVal; 
}
static uint32_t nextTick = 0;
static uint32_t currTick = 0;
void ldr_loop(void){
  currTick = get_currentTick();
  if(nextTick < currTick){
    // display_LCD[17];
    nextTick = currTick + ldr_ms;
    // LCD_Clear();
    if(get_menuStat() == menu_mainPage_Stat){
      LCD_String_xy(1, 12, "  ");
      sprintf(display_LCD, "%d", ldr_value());
      LCD_String_xy(1, 12, display_LCD);
    }
  }
}
