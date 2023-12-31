/*  
   LCD16x2 4 bit ATmega16 interface
   http://www.electronicwings.com
*/

#include "LCD.h"
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */

typedef enum{
    LCD_PIN_LOW  = 0,
    LCD_PIN_HIGH = 1
}lcdPinLevel_t;
typedef enum{
    LCD_LOWER_NIBBLE = 0,
    LCD_UPPER_NIBBLE = 1
}lcdNibble_t;
void LCD_WritePin(char *port, uint8_t pin, lcdPinLevel_t level);
void LCD_WriteReg(volatile uint8_t *reg, char data, lcdNibble_t nibble);

void LCD_Command( unsigned char cmnd )
{
	// LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
    LCD_WriteReg(&LCD_Port, cmnd, LCD_UPPER_NIBBLE);
	LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Port |= (1<<EN);		/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	// LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
    LCD_WriteReg(&LCD_Port, cmnd, LCD_LOWER_NIBBLE);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}
void LCD_Char( unsigned char data )
{
	// LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
    LCD_WriteReg(&LCD_Port, data, LCD_UPPER_NIBBLE);
	LCD_Port |= (1<<RS);		/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	// LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
    LCD_WriteReg(&LCD_Port, data, LCD_LOWER_NIBBLE);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}
void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Dir = 0xFF;			/* Make LCD port direction as o/p */
	_delay_ms(50);			/* LCD Power ON delay always >15ms */
	
	LCD_Command(0x03);
	_delay_ms(5);
	LCD_Command(0x03);
	_delay_ms(5);
	LCD_Command(0x03);
	_delay_ms(5);
	LCD_Command(0x02);		/* send for 4 bit initialization of LCD  */
	_delay_ms(5);
	LCD_Command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	_delay_ms(5);
	LCD_Command(0x0c);              /* Display on cursor off*/
	_delay_ms(5);
	LCD_Command(0x06);              /* Increment cursor (shift cursor to right)*/
	_delay_ms(5);
	LCD_Command(0x01);              /* Clear display screen*/
	_delay_ms(50);
	LCD_Clear();
	_delay_ms(50);
}
void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}
void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}
void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}
void LCD_WritePin(char *port, uint8_t pin, lcdPinLevel_t level){
    if(level){
        *port |=  (1 << pin);
    }
    else{
        *port &= ~(1 << pin);
    }
}
void LCD_WriteReg(volatile uint8_t *reg, char data, lcdNibble_t nibble){
    if(nibble){
        *reg = (*reg & 0x0F) | (data & 0xF0); /* upper nibble */
    }
    else{
        *reg = (*reg & 0x0F) | (data << 4);  /* sending lower nibble */       
    }
}