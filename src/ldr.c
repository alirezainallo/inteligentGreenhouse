#include "ldr.h"

uint32_t ldr_ms = 450;

extern menuStat_t get_menuStat(void);

extern uint8_t menu_mainPage_Stat_page;

void ldr_init(uint32_t ms){
  //adc_init(200);//init alone
  ldr_ms = ms;
  adc_start(adc_ch5);
}
uint16_t ldr_value(void){
  uint16_t ldrVal = 1023;
  ldrVal -= get_adc_value(adc_ch5);
  ldrVal  = (uint16_t)(((uint32_t)ldrVal*100)/1023);
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
    if((get_menuStat() == menu_mainPage_Stat) && (menu_mainPage_Stat_page == 0)){
      LCD_String_xy(1, 13, "  ");
      sprintf(display_LCD, "%d", ldr_value());
      LCD_String_xy(1, 13, display_LCD);
    }

    uint16_t ldrMax, ldrMin;
    dataBase_get_max(SEC_LIGHT, &ldrMax);
    dataBase_get_min(SEC_LIGHT, &ldrMin);
    if(ldr_value() < ldrMin){
      if(timerChecker_isEnable(SEC_LIGHT)){
        // turnOff(RELAY_LIGHT);
        // timerChecker_freeTimer(SEC_LIGHT);
      }
      else{
        timer_t time;
        turnOn(RELAY_LIGHT);
        dataBase_get_alarm(SEC_LIGHT, &time.hour, &time.min, &time.sec);
        timerChecker_addTimerAfterNow(SEC_LIGHT, time, AlarmToTernOffLight);
      }
    }

    // if(ldrMax < ldr_value()){
    //   // timer_t time;
    //   // turnOn(RELAY_FAN);
    //   // dataBase_get_alarm(SEC_CO2, &time.hour, &time.min, &time.sec);
    //   // timerChecker_addTimerAfterNow(SEC_TEMP, time, AlarmToTernOffFan);
    // }
    // else if((ldr_value() < ldrMin) && !timerChecker_isEnable(SEC_LIGHT)){
    //   timer_t time;
    //   turnOn(RELAY_LIGHT);
    //   dataBase_get_alarm(SEC_LIGHT, &time.hour, &time.min, &time.sec);
    //   timerChecker_addTimerAfterNow(SEC_LIGHT, time, AlarmToTernOffLight);
    // }
    // else{
    // }

  }
}
