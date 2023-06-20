/*
for initialize use this function:
	"keypad_init(keypad_key_state_t state);"

and use "keypad_process();" in the while(1).
	
and notice that you must define this func for use keypad:
	void keypad_kp_0_9_func (void);
	void keypad_kp_10_func  (void);
	void keypad_kp_11_func  (void);
	void keypad_kp_12_func  (void);
	void keypad_kp_13_func  (void);
	void keypad_kp_14_func  (void);
	void keypad_kp_15_func  (void);

and this example recommended(with use "LCD.h"):
	void keypad_kp_0_9_func (void)
	{
		char lcd_buff[17] = {0};
		
		number = (number * 10) + get_keypad_value();  //for exampel :)
		sprintf(lcd_buff, "%d", number);
		LCD_Puts(0, 0, lcd_buff);
	}
	void keypad_kp_10_func (void)
	{
		number = 0;
		LCD_Clear();
	}

*/


#ifndef __KEYPAD_4X4_H
#define __KEYPAD_4X4_H

#include "main.h"
#include "LCD.h"
#include "menu.h"
#include "e2prom.h"

#define MAX_KEYPAD_ROW	4
#define MAX_KEYPAD_COL	4

#define KEYPAD_R0_DIR  DDRC
#define KEYPAD_R0_PORT PORTC
#define KEYPAD_R0_PIN  PINC
#define KEYPAD_R0_Pin  PC7

#define KEYPAD_R1_DIR  DDRC
#define KEYPAD_R1_PORT PORTC
#define KEYPAD_R1_PIN  PINC
#define KEYPAD_R1_Pin  PC6

#define KEYPAD_R2_DIR  DDRC
#define KEYPAD_R2_PORT PORTC
#define KEYPAD_R2_PIN  PINC
#define KEYPAD_R2_Pin  PC5

#define KEYPAD_R3_DIR  DDRC
#define KEYPAD_R3_PORT PORTC
#define KEYPAD_R3_PIN  PINC
#define KEYPAD_R3_Pin  PC4

#define KEYPAD_C0_DIR  DDRD
#define KEYPAD_C0_PORT PORTD
#define KEYPAD_C0_PIN  PIND
#define KEYPAD_C0_Pin  PD3

#define KEYPAD_C1_DIR  DDRD
#define KEYPAD_C1_PORT PORTD
#define KEYPAD_C1_PIN  PIND
#define KEYPAD_C1_Pin  PD4

#define KEYPAD_C2_DIR  DDRD
#define KEYPAD_C2_PORT PORTD
#define KEYPAD_C2_PIN  PIND
#define KEYPAD_C2_Pin  PD5

#define KEYPAD_C3_DIR  DDRD
#define KEYPAD_C3_PORT PORTD
#define KEYPAD_C3_PIN  PIND
#define KEYPAD_C3_Pin  PD6



#define KEYPAD_TIMEOUT 0 //ms


// extern osMessageQueueId_t lcdQueueHandle; //from "freertos.c"

typedef enum
{
	LOW_LEVEL,
	HIGH_LEVEL,
	FALLING_EDGE,
	RISING_EDGE
}keypad_key_state_t;


void keypad_process (void);
uint8_t get_keypad_value (void);
void keypad_init (keypad_key_state_t state);
keypad_key_state_t keypad_state_detect (void);

extern timer_t timer;

#endif //__KEYPAD_4X4_H
