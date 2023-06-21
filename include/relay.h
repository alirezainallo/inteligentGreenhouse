#ifndef _RELAY_H
#define _RELAY_H

#include "main.h"

typedef enum{
    RELAY_FAN = 0,
    RELAY_FERTILIZING,
    RELAY_HEATER,
    RELAY_LIGHT,
    RELAY_WATERING,
}relay_t;

#define RELAY_WATERING_DIR  DDRA
#define RELAY_WATERING_PORT PORTA
#define RELAY_WATERING_PIN  PINA
#define RELAY_WATERING_Pin  PA0

#define RELAY_FERTILIZING_DIR  DDRA
#define RELAY_FERTILIZING_PORT PORTA
#define RELAY_FERTILIZING_PIN  PINA
#define RELAY_FERTILIZING_Pin  PA6

#define RELAY_FAN_DIR  DDRA
#define RELAY_FAN_PORT PORTA
#define RELAY_FAN_PIN  PINA
#define RELAY_FAN_Pin  PA1

#define RELAY_HEATER_DIR  DDRA
#define RELAY_HEATER_PORT PORTA
#define RELAY_HEATER_PIN  PINA
#define RELAY_HEATER_Pin  PA2

#define RELAY_LIGHT_DIR  DDRA
#define RELAY_LIGHT_PORT PORTA
#define RELAY_LIGHT_PIN  PINA
#define RELAY_LIGHT_Pin  PA3



void relay_init(void);
void turnOff(relay_t relay);
void turnOn(relay_t relay);

#endif //_RELAY_H
