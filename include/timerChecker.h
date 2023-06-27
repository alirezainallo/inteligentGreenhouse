#ifndef _TIMER_CHECKER_H
#define _TIMER_CHECKER_H

#include "main.h"
#include "e2prom.h"
#include "RTC.h"

#define TIMER_CHECKER_NEED 7

typedef void (*timerAlarmCallBack)(void);


void timerChecker_loop(void);
bool timerChecker_isEnable(dataBaseSec_t section);
void timerChecker_freeTimer (dataBaseSec_t section);
void timerChecker_addTimer (dataBaseSec_t section, timer_t timer, timerAlarmCallBack callBack);
void timerChecker_addTimerAfterNow (dataBaseSec_t section, timer_t _time, timerAlarmCallBack callBack);

//---------------------------callBacks-----------------------------
void AlarmToTernOffFan(void);
void AlarmToTernOffHeater(void);
void AlarmToTernOffLight(void);
void AlarmToTernOffWatering(void);
void AlarmToTernOffFertilizing(void);

void setAlarmForStartFertilizing(void);
void setAlarmForStartWatering(void);
#endif //_TIMER_CHECKER_H
