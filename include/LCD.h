#ifndef _LCD_H
#define _LCD_H

#define F_CPU 8000000UL		/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */

#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define RS PB0				/* Define Register Select pin */
#define RW PB1 				/* Define RW signal pin */
#define EN PB2 				/* Define Enable signal pin */

typedef enum{
    CMD_ClearDisplayScreen = 0x01,
    CMD_ReturnHome = 0x02,
    CMD_DecrementCursor = 0x04, //shift cursor to left
    CMD_IncrementCursor = 0x06, // shift cursor to right
    CMD_ShiftDisplayRight = 0x05,
    CMD_ShiftDisplayLeft = 0x07,
    CMD_DisplayOff_CursorOff = 0x08,
    CMD_DisplayOff_CursorOn = 0x0A,
    CMD_DisplayOn_CursorOff = 0x0C,
    CMD_DisplayOn_CursorBlinking = 0x0E,
    CMD_DisplayOff_CursorBlinking = 0x0F,
    CMD_ShiftCursorPositionToLeft = 0x10,
    CMD_ShiftTheCursorPositionToTheRight = 0x14,
    CMD_ShiftTheEntireDisplayToTheLeft = 0x18,
    CMD_ShiftTheEntireDisplayToTheRight = 0x1C,
    CMD_ForceCursorToTheBeginning0 = 0x80, //1st line
    CMD_ForceCursorToTheBeginning1 = 0x01, //2st line
    CMD_2LinesAnd_5x7_Matrix = 0x38,
}lcdCmd_t;

void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();


// int main()
// {
// 	LCD_Init();			/* Initialization of LCD*/

// 	LCD_String("ElectronicWINGS");	/* Write string on 1st line of LCD*/
// 	LCD_Command(0xC0);		/* Go to 2nd line*/
// 	LCD_String("Hello World");	/* Write string on 2nd line*/
// 	while(1);
// }

#endif //_LCD_H
