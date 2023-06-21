#ifndef _TIM_TICK_H
#define _TIM_TICK_H

#include "main.h"
#include "key.h"
#include "relay.h"

//for system tick
uint32_t get_currentTick(void);
void tim1_init(void);
//for key and keyPad
void tim0_init(void);

#endif //_TIM_TICK_H
