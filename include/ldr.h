#ifndef _LDR_H
#define _LDR_H

#include "timTick.h"
#include "main.h"
#include "adc.h"

void ldr_init(uint32_t ms);
uint16_t ldr_value(void);
void ldr_loop(void);

#endif //_LDR_H
