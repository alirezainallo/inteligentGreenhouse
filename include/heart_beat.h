//this pin must be lable and set gpio output mode : HEART_BEAT

#ifndef __HEART_BEAT_H
#define __HEART_BEAT_H

#include "main.h"
#include "time_out.h"

#define HEART_BEAT_Port PORTA
#define HEART_BEAT_Dir  DDRA
#define HEART_BEAT_Pin  PA0


void heart_beat (void);  //by default 500ms
void heart_beat_init (uint16_t ms);

#endif //__HEART_BEAT_H
