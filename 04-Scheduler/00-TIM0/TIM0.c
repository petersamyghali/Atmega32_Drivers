/*
* TIM0.c
*
* Created: 26-Feb-23 1:24:29 PM
*  Author: Peter Ghali
*/
#include "STD_TYPES.h"
#include "Bit_Math.h"

#include "TIM0.h"
#include "TIM0_Cfg.h"
#include "TIM0_Prv.h"


#define ENABLE						1
#define DISABLE						0
#define TIM0_MODE_CLR_MASK			0b10110111
#define TIM0_PRE_SCALER_CLR_MASK	0b11111000
#define TIM0_COM_CLR_MASK			0b11001111
#define	DISABLE						0
#define TIM0_MAX_VALUE				255


//static
static void (*TIM0_void_call_Back_CTC)(void)= NULL;

static void (*TIM0_void_call_Back_OVF)(void)= NULL;
static volatile u64 Glob_TCNT = 0 ;
static volatile f64 Glo_Num_of_OVFs = 0 ;
static volatile u64 Buffer_No_Of_OVFs = 0 ;

static u8 Periodic_Flag = DISABLE ;

TIM_Error_Status_t TIM0_enuInit(void)
{
	TIM_Error_Status_t Error_Status = TIM_OK ;
	
	u8 Temp_Reg = 0 ;
	#if TIM0_Mode == TIM0_Mode_OVF
	Temp_Reg = TCCR0 ;
	Temp_Reg&=TIM0_MODE_CLR_MASK;
	Temp_Reg|=TIM0_Mode_OVF;
	TCCR0 = Temp_Reg ;
	
	#elif  TIM0_Mode == TIM0_Mode_CTC
	Temp_Reg = TCCR0 ;
	Temp_Reg&=TIM0_MODE_CLR_MASK;
	Temp_Reg|=TIM0_Mode_CTC;
	TCCR0 = Temp_Reg ;
	OCR0 = TIM0_CTC_VALUE;
	
	#elif  TIM0_Mode == TIM0_Mode_PWM_Phase_Correct
	Temp_Reg = TCCR0 ;
	Temp_Reg&=TIM0_MODE_CLR_MASK;
	Temp_Reg|=TIM0_Mode_PWM_Phase_Correct;
	TCCR0 = Temp_Reg ;
	
	#elif  TIM0_Mode == TIM0_Mode_Fast_PWM
	Temp_Reg = TCCR0 ;
	Temp_Reg&=TIM0_MODE_CLR_MASK;
	Temp_Reg|=TIM0_Mode_Fast_PWM;
	TCCR0 = Temp_Reg ;
	
	#else
	Error_Status = TIM_Invalid_Mode ;
	#endif
	
	#if TIM0_PIN == TIM0_HW_And_Interrupt
	Temp_Reg=TCCR0;
	Temp_Reg&=TIM0_COM_CLR_MASK;
	Temp_Reg|=TIM0_OC0_PIN_MODE;
	TCCR0 = Temp_Reg ;
	SET_BIT(TIMSK , TIMSK_TOIE0);
	SET_BIT(TIMSK , TIMSK_OCIE0);

	#elif TIM0_PIN == TIM0_HW_PIN
	Temp_Reg=TCCR0;
	Temp_Reg&=TIM0_COM_CLR_MASK;
	Temp_Reg|=TIM0_OC0_PIN_MODE;
	TCCR0 = Temp_Reg ;
	#elif TIM0_PIN == TIM0_Interrupt
	SET_BIT(TIMSK , TIMSK_TOIE0);
	SET_BIT(TIMSK , TIMSK_OCIE0);

	#endif
	Temp_Reg=TCCR0;
	Temp_Reg &=TIM0_PRE_SCALER_CLR_MASK  ;
	TCCR0  = Temp_Reg ;
	return Error_Status ;

}
TIM_Error_Status_t TIM0_enuStart(void)
{
	TIM_Error_Status_t Error_Status = TIM_OK ;
	u8 Temp_Reg = 0 ;
	#if TIM0_Pre_Scaler == TIM0_Pre_Scaler_1
	Temp_Reg=TCCR0;
	Temp_Reg&=TIM0_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM0_Pre_Scaler_1;
	TCCR0 = Temp_Reg ;

	#elif TIM0_Pre_Scaler == TIM0_Pre_Scaler_8
	Temp_Reg=TCCR0;
	Temp_Reg&=TIM0_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM0_Pre_Scaler_8;
	TCCR0 = Temp_Reg ;

	#elif TIM0_Pre_Scaler == TIM0_Pre_Scaler_64
	Temp_Reg=TCCR0;
	Temp_Reg&=TIM0_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM0_Pre_Scaler_64;
	TCCR0 = Temp_Reg ;


	#elif TIM0_Pre_Scaler == TIM0_Pre_Scaler_256
	Temp_Reg=TCCR0;
	Temp_Reg&=TIM0_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM0_Pre_Scaler_256;
	TCCR0 = Temp_Reg ;

	#elif TIM0_Pre_Scaler == TIM0_Pre_Scaler_1024
	Temp_Reg=TCCR0;
	Temp_Reg&=TIM0_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM0_Pre_Scaler_1024;
	TCCR0 = Temp_Reg ;

	#else
	Error_Status = TIM_Invalid_Pre_Scaleer ;
	#endif
	return Error_Status ;
}
TIM_Error_Status_t TIM0_vidDelay_ms(u16 Cpy_Delay_ms )
{
	TIM_Error_Status_t Error_Status= TIM_OK ;

	u8 Temp_Reg = 0 ;
	Temp_Reg = TCCR0 ;
	Temp_Reg &= ~TIM0_PRE_SCALER_CLR_MASK ;
	u64 Counter = 0 ;
	switch (Temp_Reg)
	{
		case TIM0_No_Clk_Soruce :
		Error_Status = TIM_Invalid_Pre_Scaleer ;
		break;
		case TIM0_Pre_Scaler_1 :
		Glo_Num_of_OVFs = .031875 ;
		break;
		case TIM0_Pre_Scaler_8 :
		Glo_Num_of_OVFs = 0.255;
		break;
		case TIM0_Pre_Scaler_64 :
		Glo_Num_of_OVFs = 2.04 ;
		break;
		case TIM0_Pre_Scaler_256:
		Glo_Num_of_OVFs = 8.16;
		break;
		case TIM0_Pre_Scaler_1024 :
		Glo_Num_of_OVFs = 32.64 ;

		break;
	}

	Glo_Num_of_OVFs =(u64)(Cpy_Delay_ms/Glo_Num_of_OVFs);
	for (Counter = 0 ;Counter < Glo_Num_of_OVFs ; Counter++)
	{
		
		while (GET_BIT(TIFR,TIFR_TOV0) == DISABLE);
		SET_BIT(TIFR,TIFR_TOV0);

	}

	TCNT0 = Glob_TCNT ;
	while (GET_BIT(TIFR,TIFR_TOV0) == DISABLE);

	return Error_Status ;
}
TIM_Error_Status_t TIM0_vidDelay_ms_Busy_Waiting(u16 Cpy_Delay_ms ,void (*TIM0cbf_t)(void))
{
	TIM_Error_Status_t Error_Status= TIM_OK ;

	u8 Temp_Reg = 0 ;
	Temp_Reg = TCCR0 ;
	Temp_Reg &= ~TIM0_PRE_SCALER_CLR_MASK ;
	u64 Counter = 0 ;

	switch (Temp_Reg)
	{
		case TIM0_No_Clk_Soruce :
		Error_Status = TIM_Invalid_Pre_Scaleer ;
		break;
		case TIM0_Pre_Scaler_1 :
		Glo_Num_of_OVFs = .031875 ;
		break;
		case TIM0_Pre_Scaler_8 :
		Glo_Num_of_OVFs = 0.255;
		break;
		case TIM0_Pre_Scaler_64 :
		Glo_Num_of_OVFs = 2.04 ;
		break;
		case TIM0_Pre_Scaler_256:
		Glo_Num_of_OVFs = 8.16;
		break;
		case TIM0_Pre_Scaler_1024 :
		Glo_Num_of_OVFs = 32.64 ;

		break;
	}
	
	Glo_Num_of_OVFs =(u64)(Cpy_Delay_ms/Glo_Num_of_OVFs);
	for (Counter = 0 ;Counter < Glo_Num_of_OVFs ; Counter++)
	{
		while (GET_BIT(TIFR,TIFR_TOV0) == DISABLE);
		SET_BIT(TIFR,TIFR_TOV0);
	}
	
	TCNT0 = Glob_TCNT ;
	while (GET_BIT(TIFR,TIFR_TOV0) == DISABLE);
	TIM0cbf_t();
	return Error_Status ;
}

TIM_Error_Status_t TIM0_vidDelay_ms_INT(u16 Cpy_Delay_ms ,void (*TIM0cbf_t)(void) , TIM_Task_T Cpy_Task_Type)
{
	TIM_Error_Status_t Error_Status= TIM_OK ;
	u8 Temp_Reg = 0 ;
	Temp_Reg = TCCR0 ;
	Temp_Reg &= ~TIM0_PRE_SCALER_CLR_MASK ;
	if (Cpy_Task_Type == TASK_Periodic )
	{
		Periodic_Flag = ENABLE ;
	}
	switch (Temp_Reg)
	{
		case TIM0_No_Clk_Soruce :
		Error_Status = TIM_Invalid_Pre_Scaleer ;
		break;
		case TIM0_Pre_Scaler_1 :
		Glo_Num_of_OVFs = .031875 ;
		break;
		case TIM0_Pre_Scaler_8 :
		Glo_Num_of_OVFs = 0.255;
		break;
		case TIM0_Pre_Scaler_64 :
		Glo_Num_of_OVFs = 2.04 ;
		break;
		case TIM0_Pre_Scaler_256:
		Glo_Num_of_OVFs = 8.16;
		break;
		case TIM0_Pre_Scaler_1024 :
		Glo_Num_of_OVFs = 32.64 ;

		break;
	}
	
	Glo_Num_of_OVFs =(u64)(Cpy_Delay_ms/Glo_Num_of_OVFs);
	Buffer_No_Of_OVFs  = Glo_Num_of_OVFs;
	TIM0_void_call_Back_OVF = TIM0cbf_t;

	return Error_Status ;
}
TIM_Error_Status_t TIM0_enuRegisterCallback_OVF( void (*TIM0cbf_t)(void))
{

	TIM_Error_Status_t Error_Status = TIM_OK ;

	SET_BIT(TIMSK,TIMSK_TOIE0) ;


	if(TIM0cbf_t != NULL )
	{
		TIM0_void_call_Back_OVF = TIM0cbf_t ;
		
	}
	else
	{
		Error_Status = TIM_NULL_PTR ;
	}
	return Error_Status ;
}
TIM_Error_Status_t TIM0_enuRegisterCallback_CTC( void (*TIM0cbf_t)(void))
{
	
	TIM_Error_Status_t Error_Status = TIM_OK ;

	SET_BIT(TIMSK,TIMSK_OCIE0) ;

	if(TIM0cbf_t != NULL)
	{
		TIM0_void_call_Back_CTC = TIM0cbf_t ;
	}
	else
	{
		Error_Status = TIM_NULL_PTR ;
	}
	return Error_Status ;
}

TIM_Error_Status_t TIM0_enuSetDutyCycle( u8 Copy_u8Duty)
{
	TIM_Error_Status_t Error_Status = TIM_OK ;
	u8 oc0_mode = TCCR0 & 0x30;
	u8 compare=0;
	if (TIM0_Mode == TIM0_Mode_Fast_PWM ||TIM0_Mode == TIM0_Mode_PWM_Phase_Correct  ){
		if (TIM0_OC0_PIN_MODE == SET_OC0_ON_COMPARE_MATCH_CLEAR_AT_BOTTOM){
			compare = (255-  (((f32)255/100)*Copy_u8Duty));
			OCR0 = compare;
		}
		else if (oc0_mode == CLEAR_OC0_ON_COMPARE_MATCH_SET_AT_BOTTOM){
			compare = (255 * Copy_u8Duty)/100;
			OCR0 = compare;
		}
		else {
			Error_Status = TIM_Not_Ok;
		}
	}
	else{
		Error_Status = TIM_Not_Ok;
	}

	return Error_Status ;

}

void TIM0_enuSet_OC_Value (u8 Cpy_u8Value)
{
	OCR0 = Cpy_u8Value ;
}

void TIM0_vidSetPreloadValue(u8 Copy_u8Preload)
{
	TCNT0 = Copy_u8Preload;
}

INTERRUPT_SERVICE_ROUTINE_(10)
{
	SET_BIT(TIFR,TIFR_OCF0);

	if (TIM0_void_call_Back_CTC != NULL)
	{
		TIM0_void_call_Back_CTC();
	}
	else
	{
		
	}
}

INTERRUPT_SERVICE_ROUTINE_(11)
{
	SET_BIT(TIFR,TIFR_TOV0);
	Glo_Num_of_OVFs-- ;
	if (TIM0_void_call_Back_OVF != NULL && Glo_Num_of_OVFs == 0)
	{
		//TCNT0 = Glob_TCNT ;
		
		TIM0_void_call_Back_OVF();
		Glob_TCNT = 0 ;
		Glo_Num_of_OVFs = 0 ;
		if (Periodic_Flag == ENABLE)
		{
			Glo_Num_of_OVFs = Buffer_No_Of_OVFs ;
		}

		
	}
	else
	{
		
	}
}