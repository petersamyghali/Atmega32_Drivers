/*
* LCD.h
*
* Created: 10-Feb-23 2:51:42 PM
*  Author: Peter Ghali
*/


#ifndef LCD_H_
#define LCD_H_

#include "../../00-LIB/STD_TYPES.h"
/*Some needed commands */
#define LCD_CLEAR				0x01          /* replace all characters with ASCII 'space'        */
#define LCD_HOME				0x80          /* return cursor to first position on first line     */
#define LCD_DISPLAY_OFF			0x08          // turn display off
#define LCD_DISPLAY_ON			0x0C          // display on, cursor off, don't blink character
#define LCD_Reset				0x30          // reset the LCD
#define LCD_CURSOR_LEFT			0x10
#define	LCD_CURSOR_RIGHT		0x14
#define	LCD_DISPLAY_LEFT		0x18
#define	LCD_DISPLAY_RIGHT		0x1C
//An enum data type to hold the error that may occur in any of the follwoing functions 
typedef enum
{
	LCDenuOK = 0,
	LCD_enuNOTK,
	LCD_enuNULLPtr,
	LCD_enuWrong_Parameters , 
	
}LCD_enuErrorStatus_t;


/*
A function to init the LCD based on the Given configurations in the cfg file 
INPUT	: void
Return	: Error status
*/
LCD_enuErrorStatus_t LCD_enuInit (void);

/*
A function to Send Data to the LCD
INPUT	: the required (ASCII)
Return	: Error status if one had occurred
*/

LCD_enuErrorStatus_t LCD_enuSendData (u8 Copy_u8Data);

/*
A function to Send a command to the LCD
INPUT	: the required command 
Return	: Error status if one had occurred
*/
LCD_enuErrorStatus_t LCD_enuSendCommand (u16 Copy_u8Command);

/*
A function to Make the cursor go to the given position 
INPUT	: The X , Y coordinates of the LCD (0 included)
Return	: Error status if one had occurred
*/
LCD_enuErrorStatus_t LCD_enuGotoXY      (u8 Copy_u8XPos, u8 Copy_u8YPos);

/*
A function to write a specific pattern at a specific place in the LCD
INPUT	: void
Return	: Error status if one had occurred
*/
LCD_enuErrorStatus_t LCD_enuWriteSpecialPattern  (const u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos);

/*
A function to Write a string to the LCD
INPUT	: A string
Return	: Error status if one had occurred
*/
LCD_enuErrorStatus_t LCD_enuSendString (const u8* Add_pchString);

/*
A function to Write a number to the LCD
INPUT	: A number  
Return	: Error status if one had occurred
*/
LCD_enuErrorStatus_t LCD_enuWriteNumber (u32 Copy_u16Number);



#endif /* LCD_H_ */