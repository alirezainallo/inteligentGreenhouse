#include "RTC.h"

extern uint8_t menu_mainPage_Stat_page;

extern bool timerChecker_RTC_update;

char second,minute,hour,day,date,month;
uint16_t year;

extern menuStat_t get_menuStat(void);

static uint8_t bcd2bin(uint8_t val){
	return val - 6 * (val >> 4); 
}

static uint8_t bin2bcd(uint8_t val){
	return val + 6 * (val / 10); 
}

uint8_t isRunning(void){
	I2C_Start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_Write(0);	/* Write address to read */
	I2C_Repeated_Start(Device_Read_address);/* Repeated start with device read address */
	second = bcd2bin((uint8_t)I2C_Read_Nack());
	I2C_Stop();			/* Stop i2C communication */

	return !(second >> 7);
}


/*init function*/
void RTC_Init(void)
{
    I2C_Init();
	if(!isRunning()){
		RTC_Clock_Write(22,25,0);
		RTC_Calendar_Write(1, 18, 6, 2023);
	}
}

/* function for clock */
void RTC_Clock_Write(char _hour, char _minute, char _second)
{
// 	// _hour |= AMPM;

	I2C_Start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_Write(0);			/* Write 0 address for second */
	I2C_Write(bin2bcd(_second));		/* Write second on 00 location */
	I2C_Write(bin2bcd(_minute));		/* Write minute on 01(auto increment) location */
	I2C_Write(bin2bcd(_hour));		/* Write hour on 02 location */
	I2C_Stop();			/* Stop I2C communication */
}

/* function for calendar */
void RTC_Calendar_Write(char _day, char _date, char _month, uint16_t _year)
{
	I2C_Start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_Write(3);			/* Write 3 address for day */
	I2C_Write(bin2bcd(_day));		/* Write day on 03 location */
	I2C_Write(bin2bcd(_date));		/* Write date on 04 location */
	I2C_Write(bin2bcd(_month));		/* Write month on 05 location */
	I2C_Write(bin2bcd(_year - 2000));		/* Write year on 06 location */
	I2C_Stop();			/* Stop I2C communication */
}

bool IsItPM(char hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}

void RTC_Read_Clock(char read_clock_address)
{
	I2C_Start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);	/* Write address to read */
	I2C_Repeated_Start(Device_Read_address);/* Repeated start with device read address */

	second = bcd2bin((uint8_t)I2C_Read_Ack() & 0x7F);	/* Read second */
	minute = bcd2bin((uint8_t)I2C_Read_Ack());	/* Read minute */
	hour = bcd2bin((uint8_t)I2C_Read_Nack());		/* Read hour with Nack */
	I2C_Stop();			/* Stop i2C communication */
}

void RTC_Read_Calendar(char read_calendar_address)
{
	I2C_Start(Device_Write_address);
	I2C_Write(read_calendar_address);
	I2C_Repeated_Start(Device_Read_address);

	day = bcd2bin((uint8_t)I2C_Read_Ack());		/* Read day */ 
	date = bcd2bin((uint8_t)I2C_Read_Ack());		/* Read date */
	month = bcd2bin((uint8_t)I2C_Read_Ack());		/* Read month */
	year = bcd2bin((uint8_t)I2C_Read_Nack()) + 2000;		/* Read the year with Nack */
	I2C_Stop();			/* Stop i2C communication */
}

void RTC_loop(void){
//   static char display_LCD[20];
  static char days[7][4]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  static uint32_t nextTick;
  static uint32_t currTick;
  currTick = get_currentTick();
  if(nextTick < currTick){
    nextTick = currTick + RTC_TIME_OUT;
	
	timerChecker_RTC_update = true;

    RTC_Read_Clock(0);	// Read clock with second add. i.e location is 0
	RTC_Read_Calendar(3);	// Read calendar with day address i.e location is 3 
	if((get_menuStat() == menu_mainPage_Stat) && (menu_mainPage_Stat_page == 1)){
		
		sprintf(display_LCD, "    %02d:%02d:%02d    ", hour, minute, second);
		LCD_String_xy(1, 0, display_LCD);

		// if (hour & TimeFormat12)	
		// {
		// sprintf(display_LCD, "%02d:%02d:%02d", (hour & 0b00011111), minute, second);
		// if(IsItPM(hour)){
		// 	strcat(display_LCD, "PM");
		// }
		// else{
		// 	strcat(display_LCD, "AM");
		// }
		// // lcd_print_xy(0,0,display_LCD);
		// LCD_String_xy(0,0,display_LCD);
		// }
		// else
		// {
		// sprintf(display_LCD, "%02d:%02d:%02d", (hour & 0b00011111), minute, second);
		// // lcd_print_xy(0,0,display_LCD);
		// LCD_String_xy(0,0,display_LCD);
		// }

		// sprintf(display_LCD, "%02d/%02d/%04d %s", month, date, year,day!=0?days[day-1]:days[6]);
		// // lcd_print_xy(1,0,display_LCD);
		// LCD_String_xy(1,0,display_LCD);
	}
  }
}