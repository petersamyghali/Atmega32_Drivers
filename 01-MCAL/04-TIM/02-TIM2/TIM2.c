/*
* TIM2.c
*
* Created: 26-Feb-23 1:24:29 PM
*  Author: Peter Ghali
*/
#include "STD_TYPES.h"
#include "Bit_Math.h"

#include "TIM2.h"
#include "TIM2_Cfg.h"
#include "TIM2_Prv.h"

//static
static void (*TIM2_void_call_Back_CTC)(void)= NULL;

static void (*TIM2_void_call_Back_OVF)(void)= NULL;

#define TIM2_MODE_CLR_MASK			0b10110111
#define TIM2_PRE_SCALER_CLR_MASK	0b11111000
#define TIM2_COM_CLR_MASK			0b11001111




TIM2_Error_Status_t TIM2_enuInit(void)
{
	TIM2_Error_Status_t Error_Status = TIM2_OK ;
	
	u8 Temp_Reg = 0 ;
	#if TIM2_Mode == TIM2_Mode_OVF
	Temp_Reg = TCCR2 ;
	Temp_Reg&=TIM2_MODE_CLR_MASK;
	Temp_Reg|=TIM2_Mode_OVF;
	TCCR2 = Temp_Reg ;
	
	#elif  TIM2_Mode == TIM2_Mode_CTC
	Temp_Reg = TCCR2 ;
	Temp_Reg&=TIM2_MODE_CLR_MASK;
	Temp_Reg|=TIM2_Mode_CTC;
	TCCR2 = Temp_Reg ;
	OCR2 = TIM2_CTC_VALUE;
	#elif  TIM2_Mode == TIM2_Mode_PWM_Phase_Correct
	Temp_Reg = TCCR2 ;
	Temp_Reg&=TIM2_MODE_CLR_MASK;
	Temp_Reg|=TIM2_Mode_PWM_Phase_Correct;
	TCCR2 = Temp_Reg ;
	
	#elif  TIM2_Mode == TIM2_Mode_Fast_PWM
	Temp_Reg = TCCR2 ;
	Temp_Reg&=TIM2_MODE_CLR_MASK;
	Temp_Reg|=TIM2_Mode_Fast_PWM;
	TCCR2 = Temp_Reg ;
	
	#else
	Error_Status = TIM_Invalid_Mode ;
	#endif
	
	#if TIM2_PIN == TIM2_HW_And_Interrupt
	Temp_Reg=TCCR2;
	Temp_Reg&=TIM2_COM_CLR_MASK;
	Temp_Reg|=TIM2_OC2_PIN_MODE;
	TCCR2 = Temp_Reg ;
	#endif
	Temp_Reg=TCCR2;
	Temp_Reg &=TIM2_PRE_SCALER_CLR_MASK  ;
	TCCR2  = Temp_Reg ;
	return Error_Status ;
}


TIM2_Error_Status_t TIM2_enuStart(void)
{
	TIM2_Error_Status_t Error_Status = TIM2_OK ;
	u8 Temp_Reg = 0 ;
	#if TIM2_Pre_Scaler == TIM2_Pre_Scaler_0
	Temp_Reg=TCCR2;
	Temp_Reg&=TIM2_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM2_Pre_Scaler_0;
	TCCR2 = Temp_Reg ;

	#elif TIM2_Pre_Scaler == TIM2_Pre_Scaler_8
	Temp_Reg=TCCR2;
	Temp_Reg&=TIM2_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM2_Pre_Scaler_8;
	TCCR2 = Temp_Reg ;

	#elif TIM2_Pre_Scaler == TIM2_Pre_Scaler_64
	Temp_Reg=TCCR2;
	Temp_Reg&=TIM2_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM2_Pre_Scaler_64;
	TCCR2 = Temp_Reg ;


	#elif TIM2_Pre_Scaler == TIM2_Pre_Scaler_256
	Temp_Reg=TCCR2;
	Temp_Reg&=TIM2_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM2_Pre_Scaler_256;
	TCCR2 = Temp_Reg ;

	#elif TIM2_Pre_Scaler == TIM2_Pre_Scaler_1024
	Temp_Reg=TCCR2;
	Temp_Reg&=TIM2_PRE_SCALER_CLR_MASK;
	Temp_Reg|=TIM2_Pre_Scaler_1024;
	TCCR2 = Temp_Reg ;

	#else
	Error_Status = TIM_Invalid_Pre_Scaleer ;
	#endif
	return Error_Status ;
}

TIM2_Error_Status_t TIM2_enuRegisterCallback_OVF(TIM2cbf_t Add_Fun)
{

	TIM2_Error_Status_t Error_Status = TIM2_OK ;

	SET_BIT(TIMSK,TIMSK_TOIE2);


	if(Add_Fun != NULL)
	{
		TIM2_void_call_Back_OVF = Add_Fun ;
	}
	else
	{
		Error_Status = TIM2_NULL_PTR ;
	}
	return Error_Status ;
}
TIM2_Error_Status_t TIM2_enuRegisterCallback_CTC( TIM2cbf_t Add_Fun)
{
	
	TIM2_Error_Status_t Error_Status = TIM2_OK ;

	SET_BIT(TIMSK,TIMSK_OCIE2);

	if(Add_Fun != NULL)
	{
		TIM2_void_call_Back_CTC = Add_Fun ;
	}
	else
	{
		Error_Status = TIM2_NULL_PTR ;
	}
	return Error_Status ;
}

TIM2_Error_Status_t TIM2_enuSetDutyCycle( u8 Copy_u8Duty)
{
	TIM2_Error_Status_t Error_Status = TIM2_OK ;
	u8 OC2_mode = TCCR2 & 0x30;
	u8 compare=0;
	if (TIM2_Mode == TIM2_Mode_Fast_PWM ||TIM2_Mode == TIM2_Mode_PWM_Phase_Correct  ){
		if (TIM2_OC2_PIN_MODE == SET_OC2_ON_COMPARE_MATCH_CLEAR_AT_BOTTOM){
			compare = (255-  (((f32)255/100)*Copy_u8Duty));
			OCR2 = compare;
		}
		else if (OC2_mode== CLEAR_OC2_ON_COMPARE_MATCH_SET_AT_BOTTOM){
			compare = (255 * Copy_u8Duty)/100;
			OCR2 = compare;
		}
		else {
			Error_Status = TIM2_Not_Ok;
		}
	}
	else{
		Error_Status = TIM2_Not_Ok;
	}

	return Error_Status ;

}

void TIM2_enuSet_OC_Value (u8 Cpy_u8Value)
{
	OCR2 = Cpy_u8Value ;
}

void TIM2_vidSetPreloadValue(u8 Copy_u8Preload)
{
	TCNT2 = Copy_u8Preload;
}

INTERRUPT_SERVICE_ROUTINE_(4)
{
	SET_BIT(TIFR,TIFR_OCF2);

	if (TIM2_void_call_Back_CTC != NULL)
	{
		TIM2_void_call_Back_CTC();
	}
	else
	{
		
	}
}

INTERRUPT_SERVICE_ROUTINE_(5)
{
	SET_BIT(TIFR,TIFR_TOV2);
	TCNT2 = TIM2_PRE_LOAD;
	
	if (TIM2_void_call_Back_OVF != NULL)
	{
		TIM2_void_call_Back_OVF();
	}
	else
	{
		
	}
}