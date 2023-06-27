#ifndef _E2PROM_H
#define _E2PROM_H

#include "main.h"
#include "avr/eeprom.h"

#define DATA_BASE_KEY 0X04
#define DATA_BASE_STRUCT_COUNT 6

typedef enum dataBaseSec_tag{
    SEC_HUMIDITY = 0,
    SEC_TEMP,
    SEC_CO2,
    SEC_LIGHT,
    SEC_WATERING,
    SEC_FERTILIZING,
    SEC_AlarmForTimerChecker,
    SEC_AlarmForTimerChecker2,
}dataBaseSec_t;

typedef struct clock_time_tag
{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
}clock_time_t;

typedef struct setUp_tag
{
    uint16_t max;
    uint16_t min;
    clock_time_t alarm;
}setUp_t;

typedef struct dataBase_tag
{
    setUp_t setUp[DATA_BASE_STRUCT_COUNT];
    uint8_t key;
}dataBase_t;

void dataBase_init(void);
void dataBase_update(void);
bool dataBase_wasFirstTime(void);
void dataBase_set_max(dataBaseSec_t section, uint16_t max);
void dataBase_set_min(dataBaseSec_t section, uint16_t min);
void dataBase_set_alarm(dataBaseSec_t section, uint8_t hour, uint8_t min, uint8_t sec);
void dataBase_get_max(dataBaseSec_t section, uint16_t *max);
void dataBase_get_min(dataBaseSec_t section, uint16_t *min);
void dataBase_get_alarm(dataBaseSec_t section, uint8_t *hour, uint8_t *min, uint8_t *sec);


#endif //_E2PROM_H
