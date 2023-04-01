#define F_CPU 8000000UL
#include "../../00-LIB/BIT_MATH.h"
#include "../../00-LIB/STD_TYPES.h"
#include "../../01-MCAL/00-DIO/DIO.h"
#include "PUSH_BUTTON.h"
#include <util/delay.h>

#define MAX_PINS_IN_A_PORT	8
#define DE_BOUNCING_TRIALS	5
#define ZERO				0

PushButton_enuErrorStatus PushButton_enuInit(void)
{
	u8 LocalCounter  = ZERO;
	PushButton_enuErrorStatus Error_Status = PushButton_enuOk ;
	
	for(LocalCounter = ZERO ; LocalCounter < PushButton_Numbers ; LocalCounter++)
	{
		if(PushButton_strPushButtonCfg[LocalCounter].PushButton_Type == PushButton_enuActiveHigh)
		{
			DIO_enuClearPin(PushButton_strPushButtonCfg[LocalCounter].PushButton_PIN);
		}
		
		else if (PushButton_strPushButtonCfg[LocalCounter].PushButton_Type == PushButton_enuActiveLow)
		{
			DIO_enuSetPin(PushButton_strPushButtonCfg[LocalCounter].PushButton_PIN);
			
		}
		else
		{
			Error_Status = PushButton_enuInvalidMode ;
		}
	}
	return Error_Status;
	
}
PushButton_enuErrorStatus PushButton_enuGetState(PushButton_tenuPushButtonNumber Cpy_u8Pin, PushButton_t* Add_u8ButtonVal)
{
	u8 Loc_Flag = 2 ;
	u8 Loc_Counter = 0 ;
	PushButton_enuErrorStatus Error_Status = PushButton_enuOk ;
	if(Cpy_u8Pin > PushButton_Numbers)
	{
		Error_Status = PushButton_enuInvalidPINNumber ;
	}
	else if (Add_u8ButtonVal == NULL )
	{
		Error_Status = PushButton_enuNullPtr ;
	}
	else
	{
		for (Loc_Counter = ZERO ; Loc_Counter <= DE_BOUNCING_TRIALS ; Loc_Counter++)
		{
			DIO_enuGetPin(PushButton_strPushButtonCfg[Cpy_u8Pin].PushButton_PIN, Add_u8ButtonVal);
			if( *Add_u8ButtonVal == 0)
			{
				Loc_Flag = 0;
				_delay_ms(35);
			}
			
			else
			{
				Loc_Flag = 1;
			}
			
		}
		* Add_u8ButtonVal = Loc_Flag ;
	}
	return Error_Status;
}
