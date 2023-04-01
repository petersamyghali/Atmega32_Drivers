//including the LIB files
#include "../../00-LIB/BIT_MATH.h"
#include "../../00-LIB/STD_TYPES.h"
//including the LED.h files
#include "LED.h"
#include "LED_Cfg.h"
#define	 ZERO	0
static volatile u8 State = LOW  ;  

LED_tenuErrorStatus LED_enuInit(void)
{
	LED_tenuErrorStatus Error_Status = LED_enuOk ;
	u8 Loc_Counter = ZERO ;
	for (Loc_Counter =  ZERO ; Loc_Counter < NUMBER_OF_LEDS ; Loc_Counter++)
	{
		if (LED_strLEDCfg[Loc_Counter].LED_Type == LED_enuActiveHigh )
		{
			DIO_enuClearPin(LED_strLEDCfg[Loc_Counter].LED_PIN);
		}
		else if (LED_strLEDCfg[Loc_Counter].LED_Type == LED_enuActiveLow)
		{
			DIO_enuSetPin(LED_strLEDCfg[Loc_Counter].LED_PIN);
		}
		else Error_Status = LED_enuNotOk ;
	}
	return Error_Status;
}

LED_tenuErrorStatus LED_enuLEDON (u8 Cpy_enuLEDNumber)
{

	LED_tenuErrorStatus Error_Status = LED_enuOk ;
	if (Cpy_enuLEDNumber >=  NUMBER_OF_LEDS  || Cpy_enuLEDNumber < 0 )
	{
		Error_Status = LED_enuInavalidLEDNum ;
	}
	else
	{
		if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveHigh )
		{
			
			DIO_enuSetPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_PIN);
			
		}
		else if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveLow)
		{
		
			DIO_enuClearPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_PIN);
		
		}
		else Error_Status = LED_enuNotOk ;
	}
	State == HIGH ; 
	return Error_Status;
}


LED_tenuErrorStatus LED_enuLEDOFF(u8 Cpy_enuLEDNumber)
{
	
	LED_tenuErrorStatus Error_Status = LED_enuOk ;
	if (Cpy_enuLEDNumber >  NUMBER_OF_LEDS )
	{
		Error_Status = LED_enuInavalidLEDNum ;
	}
	else
	{
		if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveLow )
		{
			DIO_enuSetPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_PIN);
		}
		else if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveHigh)
		{
			DIO_enuClearPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_PIN);
		}
		else Error_Status = LED_enuNotOk ;
	}
	State = LOW ; 
	return Error_Status;
}

LED_tenuErrorStatus LED_enuLEDToggle(u8 Cpy_enuLEDNumber)
{
	LED_tenuErrorStatus Error_Status = LED_enuOk ;
	if (Cpy_enuLEDNumber >  NUMBER_OF_LEDS )
	{
		Error_Status = LED_enuInavalidLEDNum ;
	}
	else
	{
		if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveLow  )
		{
			if (State == LOW)
			{
				DIO_enuClearPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_PIN);
				State = HIGH ; 
			}
		
			else
			{
					DIO_enuSetPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_PIN);
					State = LOW ; 
			}
		}
		else if (LED_strLEDCfg[Cpy_enuLEDNumber].LED_Type == LED_enuActiveHigh)
		{
			if (State == LOW)
			{
				DIO_enuSetPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_PIN);
				State = HIGH ; 
			}
			
			else
			{
				DIO_enuClearPin(LED_strLEDCfg[Cpy_enuLEDNumber].LED_PIN);
				State = LOW ; 
			}
			
		}
		else Error_Status = LED_enuNotOk ;
	}
	return Error_Status;

}