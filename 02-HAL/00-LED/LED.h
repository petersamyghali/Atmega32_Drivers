
#ifndef LED_H_
#define LED_H_

#include "DIO.h"
#include "DIO_Cfg.h"
#include "STD_TYPES.h"
//some needed macros 

//A macro to indicate the HIGH level
#define HIGH	1
//A macro to indicate the LOW level
#define	 LOW	0


//An enum data type to have the errors that may happen in any function 
typedef enum
{
	LED_enuOk = 0,
	LED_enuNotOk = 1,
	LED_enuInavalidLEDNum,

}LED_tenuErrorStatus;

//An enum data type to have the LEDS numbers 
typedef enum {
	
	LED0 = 0 ,
	LED1 ,
	LED2 ,
	
	

	NUMBER_OF_LEDS , 
}LED_tenuLEDNumber;

//An enum data type to have the  indicate the HIGH & LOW level
typedef enum
{
	LED_enuActiveHigh = 0  ,
	LED_enuActiveLow ,
}LED_tenuLEDType;

//An struct data type to have the LED type (Active_Hight | Active_LOW)
//And the LED PIN 
typedef struct
{
	LED_tenuLEDType LED_Type ;
	LED_tenuLEDNumber LED_PIN ;
}LED_strLEDCfg_t;

/* LED init Function
Input: void
return : Error status
*/

LED_tenuErrorStatus LED_enuInit(void);


/* LED ON Function
Input: Pin Number (Range from 0 -  Number of LEDS )
return : Error status
*/

LED_tenuErrorStatus LED_enuLEDON(u8 Cpy_enuLEDNumber);

/* LED OFF Function
Input: Pin Number (Range from 0 -   Number of LEDS )
return : Error status
*/

LED_tenuErrorStatus LED_enuLEDOFF(u8 Cpy_enuLEDNumber);

LED_tenuErrorStatus LED_enuLEDToggle(u8 Cpy_enuLEDNumber);
#endif /* LED_H_ */