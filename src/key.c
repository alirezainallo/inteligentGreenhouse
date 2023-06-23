#include "key.h"

#include "timerChecker.h"

void keyWatering_onPressed(bool state);
void keyFan_onPressed(bool state);
void keyHeater_onPressed(bool state);
void keyLight_onPressed(bool state);
void keyFertilizing_onPressed(bool state);

//-------------------------------------------------------
void keyWatering_onPressed(bool state) {
  //key process...

  if(timerChecker_isEnable(SEC_WATERING)){
    turnOff(RELAY_WATERING);
    timerChecker_freeTimer(SEC_WATERING);
  }
  else{
    timer_t time;
    turnOn(RELAY_WATERING);
    dataBase_get_alarm(SEC_WATERING, &time.hour, &time.min, &time.sec);
    timerChecker_addTimerAfterNow(SEC_WATERING, time, AlarmToTernOffWatering);
  }

  // static bool nextLevel = true;
  // if(nextLevel){
  //   turnOn(RELAY_WATERING);
  // }
  // else{
  //   turnOff(RELAY_WATERING);
  // }
  // nextLevel = !nextLevel;
}
void keyFan_onPressed(bool state) {
  //key process...

  // if(timerChecker_isEnable(SEC_)){
  //   turnOff(RELAY_WATERING);
  //   timerChecker_freeTimer(SEC_WATERING);
  // }
  // else{
  //   timer_t time;
  //   turnOff(RELAY_WATERING);
  //   dataBase_get_alarm(SEC_WATERING, &time.hour, &time.min, &time.sec);
  //   timerChecker_addTimerAfterNow(SEC_WATERING, time, AlarmToTernOffWatering);
  // }

  // static bool nextLevel = true;
  // if(nextLevel){
  //   turnOn(RELAY_FAN);
  // }
  // else{
  //   turnOff(RELAY_FAN);
  // }
  // nextLevel = !nextLevel;
    // _delay_ms(2000);
}
void keyHeater_onPressed(bool state) {
  //key process...
  
  // if(timerChecker_isEnable(SEC_TEMP) && ){
  //   turnOff(RELAY_WATERING);
  //   timerChecker_freeTimer(SEC_WATERING);
  // }
  // else{
  //   timer_t time;
  //   turnOff(RELAY_WATERING);
  //   dataBase_get_alarm(SEC_WATERING, &time.hour, &time.min, &time.sec);
  //   timerChecker_addTimerAfterNow(SEC_WATERING, time, AlarmToTernOffWatering);
  // }

  // static bool nextLevel = true;
  // if(nextLevel){
  //   turnOn(RELAY_HEATER);
  // }
  // else{
  //   turnOff(RELAY_HEATER);
  // }
  // nextLevel = !nextLevel;
}
void keyLight_onPressed(bool state) {
  //key process...

  if(timerChecker_isEnable(SEC_LIGHT)){
    turnOff(RELAY_LIGHT);
    timerChecker_freeTimer(SEC_LIGHT);
  }
  else{
    timer_t time;
    turnOn(RELAY_LIGHT);
    dataBase_get_alarm(SEC_LIGHT, &time.hour, &time.min, &time.sec);
    timerChecker_addTimerAfterNow(SEC_LIGHT, time, AlarmToTernOffLight);
  }

  // static bool nextLevel = true;
  // if(nextLevel){
  //   turnOn(RELAY_LIGHT);
  // }
  // else{
  //   turnOff(RELAY_LIGHT);
  // }
  // nextLevel = !nextLevel;
}
void keyFertilizing_onPressed(bool state) {
  //key process...

  if(timerChecker_isEnable(SEC_FERTILIZING)){
    turnOff(RELAY_FERTILIZING);
    timerChecker_freeTimer(SEC_FERTILIZING);
  }
  else{
    timer_t time;
    turnOn(RELAY_WATERING);
    dataBase_get_alarm(SEC_WATERING, &time.hour, &time.min, &time.sec);
    timerChecker_addTimerAfterNow(SEC_WATERING, time, AlarmToTernOffFertilizing);
  }

  // static bool nextLevel = true;
  // if(nextLevel){
  //   turnOn(RELAY_FERTILIZING);
  // }
  // else{
  //   turnOff(RELAY_FERTILIZING);
  // }
  // nextLevel = !nextLevel;
}
//-------------------------------------------------------


bool keyWatering_preLevel = true;
bool keyFan_preLevel = true;
bool keyHeater_preLevel = true;
bool keyLight_preLevel = true;
bool keyFertilizing_preLevel = true;

void keys_init(void){
    keyWatering_DDR  &= ~(1 << keyWatering_pin);
    keyWatering_PORT |=  (1 << keyWatering_pin);
    
    keyFan_DDR  &= ~(1 << keyFan_pin);
    keyFan_PORT |=  (1 << keyFan_pin);
    
    keyHeater_DDR  &= ~(1 << keyHeater_pin);
    keyHeater_PORT |=  (1 << keyHeater_pin);
    
    keyLight_DDR  &= ~(1 << keyLight_pin);
    keyLight_PORT |=  (1 << keyLight_pin);
    
    keyFertilizing_DDR  &= ~(1 << keyFertilizing_pin);
    keyFertilizing_PORT |=  (1 << keyFertilizing_pin);
}
void keys_loop(void){
    bool curLevel = ((keyWatering_PIN & (1 << keyWatering_pin)) != 0);
    if(keyWatering_preLevel != curLevel){
        keyWatering_preLevel = curLevel;
        if(curLevel){
            //rising
        }
        else{
            //falling
            keyWatering_onPressed(curLevel);
        }
    }

    curLevel = ((keyFan_PIN & (1 << keyFan_pin)) != 0);
    if(keyFan_preLevel != curLevel){
        keyFan_preLevel = curLevel;
        if(curLevel){
            //rising
        }
        else{
            //falling
            keyFan_onPressed(curLevel);
        }
    }

    curLevel = ((keyHeater_PIN & (1 << keyHeater_pin)) != 0);
    if(keyHeater_preLevel != curLevel){
        keyHeater_preLevel = curLevel;
        if(curLevel){
            //rising
        }
        else{
            //falling
            keyHeater_onPressed(curLevel);
        }
    }

    curLevel = ((keyLight_PIN & (1 << keyLight_pin)) != 0);
    if(keyLight_preLevel != curLevel){
        keyLight_preLevel = curLevel;
        if(curLevel){
            //rising
        }
        else{
            //falling
            keyLight_onPressed(curLevel);
        }
    }

    curLevel = ((keyFertilizing_PIN & (1 << keyFertilizing_pin)) != 0);
    if(keyFertilizing_preLevel != curLevel){
        keyFertilizing_preLevel = curLevel;
        if(curLevel){
            //rising
        }
        else{
            //falling
            keyFertilizing_onPressed(curLevel);
        }
    }
}
