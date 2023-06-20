#include "relay.h"


typedef enum{
	PIN_LOW_LEVEL  = 0,
	PIN_HIGH_LEVEL = 1,
}PinLevel;

void writePin(volatile uint8_t *reg, uint8_t pin, PinLevel level){
    if(level){
        *reg |=  (1 << pin);
    }
    else{
        *reg &= ~(1 << pin);
    }
}

void relay_init(void){
    //set as output
    writePin(&RELAY_FAN_DIR, RELAY_FAN_Pin, PIN_HIGH_LEVEL);
    writePin(&RELAY_FERTILIZING_DIR, RELAY_FERTILIZING_Pin, PIN_HIGH_LEVEL);
    writePin(&RELAY_HEATER_DIR, RELAY_HEATER_Pin, PIN_HIGH_LEVEL);
    writePin(&RELAY_LIGHT_DIR, RELAY_LIGHT_Pin, PIN_HIGH_LEVEL);
    writePin(&RELAY_WATERING_DIR, RELAY_WATERING_Pin, PIN_HIGH_LEVEL);
    
    writePin(&RELAY_FAN_PORT, RELAY_FAN_Pin, PIN_LOW_LEVEL);
    writePin(&RELAY_FERTILIZING_PORT, RELAY_FERTILIZING_Pin, PIN_LOW_LEVEL);
    writePin(&RELAY_HEATER_PORT, RELAY_HEATER_Pin, PIN_LOW_LEVEL);
    writePin(&RELAY_LIGHT_PORT, RELAY_LIGHT_Pin, PIN_LOW_LEVEL);
    writePin(&RELAY_WATERING_PORT, RELAY_WATERING_Pin, PIN_LOW_LEVEL); 
}
void turnOff(relay_t relay){
    switch (relay)
    {
        case RELAY_FAN:
            writePin(&RELAY_FAN_PORT, RELAY_FAN_Pin, PIN_LOW_LEVEL);
            break;
        case RELAY_FERTILIZING:
            writePin(&RELAY_FERTILIZING_PORT, RELAY_FERTILIZING_Pin, PIN_LOW_LEVEL);
            break;
        case RELAY_HEATER:
            writePin(&RELAY_HEATER_PORT, RELAY_HEATER_Pin, PIN_LOW_LEVEL);
            break;
        case RELAY_LIGHT:
            writePin(&RELAY_LIGHT_PORT, RELAY_LIGHT_Pin, PIN_LOW_LEVEL);
            break;
        case RELAY_WATERING:
            writePin(&RELAY_WATERING_PORT, RELAY_WATERING_Pin, PIN_LOW_LEVEL);
            break;
        
        default:
            break;
    }
}
void turnOn(relay_t relay){
    switch (relay)
    {
        case RELAY_FAN:
            writePin(&RELAY_FAN_PORT, RELAY_FAN_Pin, PIN_HIGH_LEVEL);
            break;
        case RELAY_FERTILIZING:
            writePin(&RELAY_FERTILIZING_PORT, RELAY_FERTILIZING_Pin, PIN_HIGH_LEVEL);
            break;
        case RELAY_HEATER:
            writePin(&RELAY_HEATER_PORT, RELAY_HEATER_Pin, PIN_HIGH_LEVEL);
            break;
        case RELAY_LIGHT:
            writePin(&RELAY_LIGHT_PORT, RELAY_LIGHT_Pin, PIN_HIGH_LEVEL);
            break;
        case RELAY_WATERING:
            writePin(&RELAY_WATERING_PORT, RELAY_WATERING_Pin, PIN_HIGH_LEVEL);
            break;
        
        default:
            break;
    }
}