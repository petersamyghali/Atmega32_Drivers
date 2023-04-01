
#ifndef LED_H_
#define LED_H_

#include "../../../../01-MCAL/00-DIO/GccApplication1/GccApplication1/DIO.h"
#include "../../../../01-MCAL/00-DIO/GccApplication1/GccApplication1/DIO_Cfg.h"
#include "../../../../00-LIB/STD_TYPES.h"

typedef enum
{
	LED_enuOk = 0,
	LED_enuNotOk = 1,
	LED_enuInavalidLEDNum,

}LED_tenuErrorStatus;

typedef enum {
	
	LED_enu_LED0 = 0 ,
	LED_enu_LED1 ,
	LED_enu_LED2 ,
	LED_enu_LED3 ,
	LED_enu_LED4 ,
	LED_enu_LED5 ,
	LED_enu_LED6 ,
	LED_enu_LED7 ,
}LED_tenuLEDNumber;

/* LED ON Function
Input: Pin Number (Range from 0 - 7 )
return : Error status
*/

LED_tenuErrorStatus LED_enuLEDON(u8 Cpy_enuLEDNumber);

/* LED OFF Function
Input: Pin Number (Range from 0 - 7 )
return : Error status
*/

LED_tenuErrorStatus LED_enuLEDOFF(u8 Cpy_enuLEDNumber);
#endif /* LED_H_ */