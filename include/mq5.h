#ifndef _MQ5_H
#define _MQ5_H

#include "timTick.h"
#include "main.h"
#include "adc.h"
#include "e2prom.h"
#include "timerChecker.h"

void mq5_init(uint32_t ms);
uint16_t mq5_value(void);
void mq5_loop(void);

#endif //_MQ5_H
