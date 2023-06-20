
#ifndef __TIME_OUT_H
#define __TIME_OUT_H

#include "main.h"
#include "timTick.h"

#define MAX_TIMEOUT_NEED 1


typedef enum time_out_enum_tag
{
	HEART_BEAT = 0,
}time_out_enum_t;

uint8_t timeout_is_ok (uint32_t ms, time_out_enum_t func);


#endif //__TIME_OUT_H
