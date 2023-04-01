#include "../../00-LIB/BIT_MATH.h"
#include "../../00-LIB/STD_TYPES.h"

#include "LED.h"
#include "LED_Cfg.h"

#define	MAX_LEDS_COUNT	8 

LED_tenuErrorStatus LED_enuLEDON (u8 Cpy_enuLEDNumber)
{
	DIO_enuInit();
	LED_tenuErrorStatus Error_Status = LED_enuOk ;
	if (Cpy_enuLEDNumber >=  MAX_LEDS_COUNT  || Cpy_enuLEDNumber < 0 )
	{
		Error_Status = LED_enuInavalidLEDNum ;
	}
	else
	{
		if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveHigh )
		{
			DIO_enuSetPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_Number);
		}
		else if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveLow)
		{
			DIO_enuClearPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_Number);
		}
		else Error_Status = LED_enuNotOk ; 
	}
	return Error_Status; 
}


LED_tenuErrorStatus LED_enuLEDOFF(u8 Cpy_enuLEDNumber)
{
	DIO_enuInit();
	LED_tenuErrorStatus Error_Status = LED_enuOk ;
	if (Cpy_enuLEDNumber >  MAX_LEDS_COUNT )
	{
		Error_Status = LED_enuInavalidLEDNum ;
	}
	else
	{
		if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveLow )
		{
			DIO_enuSetPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_Number);
		}
		else if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveHigh)
		{
			DIO_enuClearPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_Number);
		}
		else Error_Status = LED_enuNotOk ;
	}
	return Error_Status;
}