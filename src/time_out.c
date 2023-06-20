#include "time_out.h"

uint8_t timeout_is_ok (uint32_t ms, time_out_enum_t func){
	static uint32_t next_time[MAX_TIMEOUT_NEED] = {0};
	uint32_t currTick = get_currentTick();

	if(next_time[func] < currTick){
		next_time[func] = currTick + ms;
		return 1;
	}
	else{
		return 0;
	}
}
