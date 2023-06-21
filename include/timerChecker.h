#ifndef _TIMER_CHECKER_H
#define _TIMER_CHECKER_H

#include "main.h"
#include "e2prom.h"
#include "RTC.h"

#define TIMER_CHECKER_NEED 6

typedef void (*timerAlarmCallBack)(void);


void timerChecker_loop(void);
void timerChecker_freeTimer (dataBaseSec_t section);
void timerChecker_addTimer (dataBaseSec_t section, timer_t timer, timerAlarmCallBack callBack);
void timerChecker_addTimerAfterNow (dataBaseSec_t section, timer_t _time, timerAlarmCallBack callBack);

#endif //_TIMER_CHECKER_H
