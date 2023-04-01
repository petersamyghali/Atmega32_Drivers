/*
* UltraSonic.c
*
* Created: 10-Mar-23 4:31:34 PM
*  Author: Peter Ghali
*/
#define F_CPU	8000000UL
#include "Bit_Math.h"
#include "STD_TYPES.h"

#include "../../01-MCAL/00-DIO/DIO.h"
#include "../../01-MCAL/04-TIM/01-TIM1/TIM1.h"
#include "../../02-HAL/05-LCD/LCD.h"
#include "UltraSonic.h"
#include "UltraSonic_Cfg.h"
#include <util/delay.h>

#define  MAX_TIM1_INT	65535
#define	 RISING_EDGE	1
#define	 FALLING_EDGE	0


#define DISTANCE_IN_CM	466

static  u16 ICR_Value = 0 , OVFs_Count = 0 ;

static volatile u32 Distance = 0 ;
static volatile u64 Timer_Value = 0 ;



static void UltraSonic_ChangeEdge (void);




void UltraSonic_enuInit(void)
{
	TIM1_enuSet_Mode(TIM1_Normal_Mode) ;
	TIM1_enuEnableINT(OVF);
	TIM1_enuEnableINT(ICU);
	TIM1_enuSetCLK(TIM1_Pre_Scaler_0);
	TIM1_enuICU_Trigger(ICU_Trigger_Rising_Edge);
	TIM1_enuStart();
	TIM1_enuRegisterCallback_ICU(UltraSonic_ChangeEdge);
}

void UltraSonic_Trigger(void)
{
	DIO_enuSetPin(Trigger_PIN);
	_delay_us(15);
	DIO_enuClearPin(Trigger_PIN);
}



u32 UltraSonic_GetReading(void)
{
	
	//u16 Timer_Value = 0 ;
	//overflows times *(2^16)+ the value in the counter register
	//TIM1_enuGet_Timer_ICR_Value(&ICR_Value);
	//TIM1_enuGet_Timer_OVFs_Count(&OVFs_Count);
	
	//Timer_Value =  ICR_Value;
	//Timer_Value =  ICR_Value +(MAX_TIM1_INT * OVFs_Count) ;
	/*466=(34300*.125*10^-6)/2)to return the distance in CM*/
	/* 8MHz Timer freq, sound speed =343 m/s */
	//Distance = Timer_Value /DISTANCE_IN_CM  ;
	
	if (Distance > 400)
	{
		Distance = 400 ;
	}

	return Distance ;

}
void UltraSonic_ChangeEdge (void)
{
	static volatile u8 Edge = RISING_EDGE ;
	if (Edge == RISING_EDGE)
	{
		TIM1_enuSet_Timer_Value(0);
		TIM1_enuICU_Trigger(ICU_Trigger_Falling_Edge);
		TIM1_enuSet_Timer_OVFs_Count(0);	
		Edge = FALLING_EDGE ;
		
	}
	else
	{
		TIM1_enuGet_Timer_Value(&ICR_Value);
		TIM1_enuGet_Timer_OVFs_Count(&OVFs_Count);
		Timer_Value =  ICR_Value +(MAX_TIM1_INT * OVFs_Count) ;
		Distance = Timer_Value /DISTANCE_IN_CM  ;
		TIM1_enuSet_Timer_Value(0);
		TIM1_enuICU_Trigger(ICU_Trigger_Rising_Edge);
		Edge = RISING_EDGE ;
		
		
	}
}