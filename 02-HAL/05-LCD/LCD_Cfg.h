/*
 * LCD_Cfg.h
 *
 * Created: 10-Feb-23 2:51:30 PM
 *  Author: Peter Ghali
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_
#include "LCD_Prv.h"
/*
In order to know how many bits you are using
Options : 
			LCD_8BIT_MODE
			LCD_4_BIT_MODE
*/
#define LCD_BIT_MODE	LCD_8BIT_MODE

/*
In order to know if you want the cursor to be on or off
Options :
		CURSOR_ON
		CURSOR_OFF
*/
#define	LCD_DISPLAY_CURSOR CURSOR_ON

/*A couple of macros to define the number of rows and the number of cols 
*/
#define NUMBER_OF_ROWS		2
#define	NUMBER_OF_COLMUNS	16

/*
A Macro to define the number of control PINS the LCD has
*/
#define /*RS*/	LCD_RS_PIN		DIO_enuPORTB_Pin0
#define /*R/W*/	LCD_RW_PIN		DIO_enuPORTB_Pin1
#define /*E*/	LCD_E_PIN		DIO_enuPORTB_Pin2 


extern u8 LCD_Data_PINS [LCD_BIT_MODE] ; 


#endif /* LCD_CFG_H_ */