/*
 * LCD_Cfg.c
 *
 * Created: 10-Feb-23 2:52:14 PM
 *  Author: Peter Ghali
 */
#include "../../01-MCAL/00-DIO/DIO.h"
#include "LCD_Cfg.h"
#include "LCD_Prv.h"
#include "LCD.h"

u8  LCD_Data_PINS [LCD_BIT_MODE]=
{
/*D0*/	DIO_enuPORTA_Pin0 ,
/*D1*/	DIO_enuPORTA_Pin1 ,
/*D2*/	DIO_enuPORTA_Pin2 ,
/*D3*/	DIO_enuPORTA_Pin3 ,
/*D4*/	DIO_enuPORTA_Pin4 ,
/*D5*/	DIO_enuPORTA_Pin5 ,
/*D6*/	DIO_enuPORTA_Pin6 ,
/*D7*/	DIO_enuPORTA_Pin7
};

