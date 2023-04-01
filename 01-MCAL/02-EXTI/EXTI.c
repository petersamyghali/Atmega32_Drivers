/*
* EXTI.c
*
* Created: 24-Jan-23 9:40:54 PM
*  Author: Peter Ghali
*/
#include "../../00-LIB/STD_TYPES.h"
#include "../../00-LIB/Bit_Math.h"

#include "../../01-MCAL/01-GEI/GEI.h"

#include "EXTI.h"
#include "EXTI_Cfg.h"
#include "EXTI_Prv.h"

/*Global pointer to function to hold INT0 ISR address*/
void (*EXTI_pvINT0PtrFunc)(void) = NULL ;
//Enabling the EXTI as per the Cfg file
EXTI_tenuErrorStatus EXTI_enuEnable(void)
{
	EXTI_tenuErrorStatus Error_Status = EXTI_enuOK ;
	//Disabling the General interrupt
	GEI_enuDisable();
	//Clearing the EXTI flags in order to make sure they are not triggered
	SET_BIT(GIFR_REGISTER , EXTI0);
	SET_BIT(GIFR_REGISTER , EXTI1);
	SET_BIT(GIFR_REGISTER , EXTI2);
	//Enabling all the EXTI PINS
	SET_BIT(GICR_REGISTER,EXTI0);
	SET_BIT(GICR_REGISTER,EXTI1);
	SET_BIT(GICR_REGISTER,EXTI2);
	// if the given mode is RISING_EDGE
	#if EXTI0_MODE == RISING_EDGE
	MCUCR_REGISTER|= EXTI0_RISING_EDGE ;
	// if the given mode is FALLING_EDGE
	#elif EXTI0_MODE == FALLING_EDGE
	MCUCR_REGISTER|= EXTI0_FALLING_EDGE ;
	// if the given mode is ANY_CHANGE
	#elif EXTI0_MODE == ANY_CHANGE
	MCUCR_REGISTER|= EXTI0_ANY_CHANGE;
	// if the given mode is LOW_LEVEL
	#elif EXTI0_MODE == LOW_LEVEL
	MCUCR_REGISTER|= EXTI0_LOW_LEVEL;
	//if the EXTI is not enabled
	#elif EXTI0_MODE == DISABLE
	CLR_BIT(GICR_REGISTER,EXTI0);
	#else
	Error_Status = EXTI_enuInavalidINT_Type ;
	#endif
	
	#if EXTI1_MODE == RISING_EDGE
	MCUCR_REGISTER|= EXTI1_RISING_EDGE ;
	#elif EXTI1_MODE == FALLING_EDGE
	MCUCR_REGISTER|= EXTI1_FALLING_EDGE ;
	#elif EXTI1_MODE == ANY_CHANGE
	MCUCR_REGISTER|= EXTI1_ANY_CHANGE;
	#elif EXTI1_MODE == LOW_LEVEL
	MCUCR_REGISTER|= EXTI1_LOW_LEVEL;
	#elif EXTI1_MODE == DISABLE
	CLR_BIT(GICR_REGISTER,EXTI1);
	#else
	Error_Status = EXTI_enuInavalidINT_Type ;
	#endif
	
	#if EXTI2_MODE == RISING_EDGE
	MCUCR_REGISTER|= EXTI2_RISING_EDGE ;
	#elif EXTI2_MODE == FALLING_EDGE
	MCUCR_REGISTER|= EXTI2_FALLING_EDGE ;
	#elif EXTI1_MODE == DISABLE
	CLR_BIT(GICR_REGISTER,EXTI2);
	#else
	Error_Status = EXTI_enuInavalidINT_Type ;
	#endif
	GEI_enuEnable();
	return Error_Status ;
	
}
//A function to disable ONLY the EXTI interrupt
EXTI_tenuErrorStatus EXTI_enuDisable(void)
{
	EXTI_tenuErrorStatus Error_Status = EXTI_enuOK ;
	//just clearing the EXTI pins
	CLR_BIT(GICR_REGISTER,EXTI0);
	CLR_BIT(GICR_REGISTER,EXTI1);
	CLR_BIT(GICR_REGISTER,EXTI2);
	return Error_Status ;
}


EXTI_tenuErrorStatus EXTI0_enuSetCallBack(void (* Cpy_pvINT0Func) (void) )
{
	EXTI_tenuErrorStatus Error_Status = EXTI_enuOK ;
	if (Cpy_pvINT0Func == NULL )
	{
		Error_Status= EXTI_enuNULLPtr ;
	}
	else
	{
		EXTI_pvINT0PtrFunc = Cpy_pvINT0Func;
	}
	return Error_Status ;
}

EXTI_tenuErrorStatus EXTI1_enuSetCallBack(void (* Cpy_pvINT0Func) (void) )
{
	EXTI_tenuErrorStatus Error_Status = EXTI_enuOK ;
	if (Cpy_pvINT0Func == NULL )
	{
		Error_Status= EXTI_enuNULLPtr ;
	}
	else
	{
		EXTI_pvINT0PtrFunc = Cpy_pvINT0Func;
	}
	return Error_Status ;
}

EXTI_tenuErrorStatus EXTI2_enuSetCallBack(void (* Cpy_pvINT0Func) (void) )
{
	EXTI_tenuErrorStatus Error_Status = EXTI_enuOK ;
	if (Cpy_pvINT0Func == NULL )
	{
		Error_Status= EXTI_enuNULLPtr ;
	}
	else
	{
		EXTI_pvINT0PtrFunc = Cpy_pvINT0Func;
	}
	return Error_Status ;
}

INTERRUPT_SERVICE_ROUTINE_(1)
{
	if (EXTI_pvINT0PtrFunc != NULL)
	{
		EXTI_pvINT0PtrFunc();
		
	}
	else
	{
		
	}
	
}

INTERRUPT_SERVICE_ROUTINE_(2)
{
	if (EXTI_pvINT0PtrFunc != NULL)
	{
		EXTI_pvINT0PtrFunc();
		
	}
	else
	{
		
	}
	
}

INTERRUPT_SERVICE_ROUTINE_(3)
{
	if (EXTI_pvINT0PtrFunc != NULL)
	{
		EXTI_pvINT0PtrFunc();
		
	}
	else
	{
		
	}
	
}