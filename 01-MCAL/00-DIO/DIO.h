//start of the guard
#ifndef	DIO_H
#define DIO_H

#include "../../00-LIB/STD_TYPES.h"
/*
Enum data type to hold the Ports name , Pins number
and the mac number of pins in this micro_controller
*/
typedef enum {
	//PORTA PINS
	DIO_enuPORTA_Pin0 = 0 ,
	DIO_enuPORTA_Pin1 ,
	DIO_enuPORTA_Pin2 ,
	DIO_enuPORTA_Pin3 ,
	DIO_enuPORTA_Pin4 ,
	DIO_enuPORTA_Pin5 ,
	DIO_enuPORTA_Pin6 ,
	DIO_enuPORTA_Pin7 ,
	//PORTB PINS
	DIO_enuPORTB_Pin0 ,
	DIO_enuPORTB_Pin1 ,
	DIO_enuPORTB_Pin2,
	DIO_enuPORTB_Pin3,
	DIO_enuPORTB_Pin4,
	DIO_enuPORTB_Pin5,
	DIO_enuPORTB_Pin6,
	DIO_enuPORTB_Pin7,
	//PORTC PINS
	DIO_enuPORTC_Pin0,
	DIO_enuPORTC_Pin1,
	DIO_enuPORTC_Pin2,
	DIO_enuPORTC_Pin3,
	DIO_enuPORTC_Pin4,
	DIO_enuPORTC_Pin5,
	DIO_enuPORTC_Pin6,
	DIO_enuPORTC_Pin7,
	//PORTD PINS
	DIO_enuPORTD_Pin0,
	DIO_enuPORTD_Pin1,
	DIO_enuPORTD_Pin2,
	DIO_enuPORTD_Pin3,
	DIO_enuPORTD_Pin4,
	DIO_enuPORTD_Pin5,
	DIO_enuPORTD_Pin6,
	DIO_enuPORTD_Pin7,
	//MAX NUMBER OF PINS
	DIO_enuNumberofPins,
}DIO_tenuPins;

/*
Enum data type for the hight and low value for the DIO_PINS
*/
typedef enum{
	DIO_enuLow = 0 ,
	DIO_enuHigh
}DIO_tenuPinValue;

/*
Enum datatype in order to know what kind of error has happened in each interface
*/
typedef enum
{
	DIO_enuOK = 0,
	DIO_enuNotOK,
	DIO_enuNullPointer,
	DIO_enuInavalidPortNum,
	DIO_enuInavalidPinNum,
	DIO_enuInavalidParametrs,
	DIO_enuInavalidMode,
}DIO_tenuErrorStatus;

typedef enum
{
	DIO_PORTA = 0,
	DIO_PORTB  ,
	DIO_PORTC  ,
	DIO_PORTD  ,
}DIO_enuPorCfg_t;

/*
DIO Init Function :
A function that initializes all of the DIO pins as in the Cfg.c file
Input : void
return : DIO_tenuErrorStatus to report error
*/
DIO_tenuErrorStatus DIO_enuInit(void);

/*
DIO SetPin Function :
A function that sets the DIO pin based on the given mode
Input	: Pin Number (Range from 0 to 31)
return	: DIO_tenuErrorStatus to report error
*/
DIO_tenuErrorStatus DIO_enuSetPin( u8 Cpy_u8PinNumber);

/*
DIO Clear Function
Input	: Pin Number (Range from 0 to 31)
return	: DIO_tenuErrorStatus to report error
*/
DIO_tenuErrorStatus DIO_enuClearPin( u8 Cpy_u8PinNumber );

/*
DIO Get Function
Input	: Pin Number (Range from 0 to 31)
return	: DIO_tenuErrorStatus to report error
*/
DIO_tenuErrorStatus DIO_enuGetPin(u8 Cpy_u8PinNumber, u8* Add_pu8PinValue);

#endif/*DIO_H*/