#include "timerChecker.h"

bool timerChecker_RTC_update = false;


typedef struct timerChecker
{
    timer_t alarmTime;
    timerAlarmCallBack callBack;
}timerChecker_t;

timerChecker_t timChecker[TIMER_CHECKER_NEED] = {0};


void timerChecker_addTimer (dataBaseSec_t section, timer_t timer, timerAlarmCallBack callBack){
    timChecker[section].alarmTime = timer;
    timChecker[section].callBack  = callBack;
}
void timerChecker_freeTimer (dataBaseSec_t section){
    memset(&timChecker[section].alarmTime, 0, sizeof(timer_t));
    timChecker[section].callBack  = 0;
}
void timerChecker_loop(void){
    if(timerChecker_RTC_update){
        timerChecker_RTC_update = false;
        timer_t now;
        now.hour = hour;
        now.min  = minute;
        now.sec  = second;

        for (dataBaseSec_t section = 0; section < TIMER_CHECKER_NEED; section++)
        {
            if(timChecker[section].callBack != 0){
                if(now.hour >= timChecker[section].alarmTime.hour){
                    if(now.min >= timChecker[section].alarmTime.min){
                        if(now.sec >= timChecker[section].alarmTime.sec){
                            timChecker[section].callBack();
                            timerChecker_freeTimer(section);
                        }
                    }
                }
            }
        }
        
    }
}
void timerChecker_addTimerAfterNow (dataBaseSec_t section, timer_t _time, timerAlarmCallBack callBack){
    //set alarm
    timer_t calTime;

    calTime.hour = (hour + _time.hour);
    calTime.min  = (minute + _time.min);
    calTime.sec  = (second + _time.sec);

    if (calTime.sec >= 60){
        calTime.sec = (calTime.sec % 60);
        calTime.min++;
    }
    if (calTime.min >= 60){
        calTime.min = (calTime.min % 60);
        calTime.hour++;
    }
    if (calTime.hour >= 24){
        calTime.hour = (calTime.hour % 24);
    }

    timerChecker_addTimer(section, calTime, callBack);
}

bool timerChecker_isEnable(dataBaseSec_t section){
    return (bool)(timChecker[section].callBack != 0);
}

//---------------------------callBacks-----------------------------
void AlarmToTernOffFan(void){
	turnOff(RELAY_FAN);
}
void AlarmToTernOffHeater(void){
	turnOff(RELAY_HEATER);
}
void AlarmToTernOffLight(void){
    turnOff(RELAY_LIGHT);
}
void AlarmToTernOffWatering(void){
    turnOff(RELAY_WATERING);
}
void AlarmToTernOffFertilizing(void){
    turnOff(RELAY_FERTILIZING);
}
void setAlarmForStartWatering(void){
    timerChecker_freeTimer(SEC_WATERING);
    timer_t timTmp;
    dataBase_get_alarm(SEC_WATERING, &timTmp.hour,
                                    &timTmp.min,
                                    &timTmp.sec);
    turnOn(RELAY_WATERING);
    timerChecker_addTimerAfterNow(SEC_WATERING, timTmp, AlarmToTernOffWatering);
}