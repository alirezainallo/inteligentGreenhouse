#include "key.h"



//-------------------------------------------------------

void keyWatering_onPressed(bool state) {
  //key process...
  static bool nextLevel = true;
  if(nextLevel){
    turnOn(RELAY_WATERING);
  }
  else{
    turnOff(RELAY_WATERING);
  }
  nextLevel = !nextLevel;
}
void keyFan_onPressed(bool state) {
  //key process...
  static bool nextLevel = true;
  if(nextLevel){
    turnOn(RELAY_FAN);
  }
  else{
    turnOff(RELAY_FAN);
  }
  nextLevel = !nextLevel;
    // _delay_ms(2000);
}
void keyHeater_onPressed(bool state) {
  //key process...
  static bool nextLevel = true;
  if(nextLevel){
    turnOn(RELAY_HEATER);
  }
  else{
    turnOff(RELAY_HEATER);
  }
//   if(nextLevel){
//     turnOn(RELAY_LIGHT);
//   }
//   else{
//     turnOff(RELAY_LIGHT);
//   }
  nextLevel = !nextLevel;
}
void keyLight_onPressed(bool state) {
  //key process...
  static bool nextLevel = true;
  if(nextLevel){
    turnOn(RELAY_LIGHT);
  }
  else{
    turnOff(RELAY_LIGHT);
  }
  nextLevel = !nextLevel;
}
void keyFertilizing_onPressed(bool state) {
  //key process...
  static bool nextLevel = true;
  if(nextLevel){
    turnOn(RELAY_FERTILIZING);
  }
  else{
    turnOff(RELAY_FERTILIZING);
  }
  nextLevel = !nextLevel;
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
