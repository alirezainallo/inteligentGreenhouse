#ifndef _RTC_H
#define _RTC_H

#define Device_Write_address	0xD0	/* Define RTC DS1307 slave write address */
#define Device_Read_address	0xD1	/* Make LSB bit high of slave address for read */
#define TimeFormat12		0x40	/* Define 12 hour format */
#define AMPM			0x20

// int main(void)
// {
// 	char buffer[20];
// 	char* days[7]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
// 	I2C_Init();			/* Initialize I2C */
// 	lcdinit();			/* Initialize LCD16x2 */
//     while(1)
//     {
// 		RTC_Read_Clock(0);	/* Read clock with second add. i.e location is 0 */
// 		if (hour & TimeFormat12)	
// 		{
// 			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
// 			if(IsItPM(hour))
// 			strcat(buffer, "PM");
// 			else
// 			strcat(buffer, "AM");
// 			lcd_print_xy(0,0,buffer);
// 		}	
// 		else
// 		{
// 			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
// 			lcd_print_xy(0,0,buffer);
// 		}
// 		RTC_Read_Calendar(3);	/* Read calendar with day address i.e location is 3 */
// 		sprintf(buffer, "%02x/%02x/%02x %3s ", date, month, year,days[day-1]);
// 		lcd_print_xy(1,0,buffer);
//     }
// }


#include "main.h"
#include "i2c_master.h"
#include "timTick.h"
#define  RTC_TIME_OUT 1000

extern char second,minute,hour,day,date,month;
extern uint16_t year;

void RTC_Init(void);
void RTC_loop(void);
void RTC_Clock_Write(char _hour, char _minute, char _second);
void RTC_Calendar_Write(char _day, char _date, char _month, uint16_t _year);
bool IsItPM(char hour_);
void RTC_Read_Clock(char read_clock_address);
void RTC_Read_Calendar(char read_calendar_address);

#endif //_RTC_H
