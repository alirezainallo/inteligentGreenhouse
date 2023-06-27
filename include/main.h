#ifndef _MAIN_H
#define _MAIN_H

#include "LCD.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <avr/interrupt.h>

extern char display_LCD[17];
extern const char freeLine[17];

typedef enum menuStat_tag{
    menu_starting = 0,
    menu_getSetUpForFirst,
    menu_mainPage,
    menu_mainPage_Stat,
    menu_mainPage_Timer,
    menu_mainPage_TimerWatering,
    menu_mainPage_TimerFertilizing,
    menu_mainPage_SetUp,
    menu_processGsm,
    menu_displayTime,
    menu_debugKeypad_displaySensor,
    menu_changeClock,
    menu_changeSensorSetting,
    menu_setRtcAlarm,
}menuStat_t;

typedef struct timer_tag{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
}timer_t;

#endif //_MAIN_H
