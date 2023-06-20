#include "heart_beat.h"

static uint16_t heart_beat_ms = 500; 

void togglePin(void){
	static bool nextLevel = true;

	if(nextLevel){
		HEART_BEAT_Port |=  (1 << HEART_BEAT_Pin);
	}
	else{
		HEART_BEAT_Port &= ~(1 << HEART_BEAT_Pin);
	}

	nextLevel = !nextLevel;
}

void heart_beat_init (uint16_t ms){
	HEART_BEAT_Dir  |=  (1 << HEART_BEAT_Pin);
	HEART_BEAT_Port &= ~(1 << HEART_BEAT_Pin);
	heart_beat_ms = ms;
	heart_beat();
}

void heart_beat (void){
	if(timeout_is_ok(heart_beat_ms, HEART_BEAT)){
		togglePin();
	}
}
