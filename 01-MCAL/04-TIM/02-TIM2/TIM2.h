/*
* TIM2.h
*
* Created: 26-Feb-23 1:24:36 PM
*  Author: Peter Ghali
*/


#ifndef TIM2_H_
#define TIM2_H_

typedef void (*TIM2cbf_t)(void) ; 
typedef enum
{
	TIM2_Normal_Mode ,
	TIM2_PWM_Phase_Correct_Mode ,
	TIM2_CTC_Mode  ,
	TIM2_Fast_PWM_Mode ,
}TIM2_Modes_t;

typedef enum
{
	TIM2_No_Clk_Soruce ,
	TIM2_Pre_Scaler_0	,
	TIM2_Pre_Scaler_8	,
	TIM2_Pre_Scaler_32	,
	TIM2_Pre_Scaler_64	,
	TIM2_Pre_Scaler_128	,
	TIM2_Pre_Scaler_256	,
	TIM2_Pre_Scaler_1024,
}TIM2_Clock_t;

typedef enum
{
	TIM2_OK ,
	TIM2_Not_Ok,
	TIM2_NULL_PTR ,
	TIM2_Invalid_Pre_Scaleer ,
	TIM2_Invalid_Mode,
}TIM2_Error_Status_t;

TIM2_Error_Status_t TIM2_enuInit(void);

TIM2_Error_Status_t TIM2_enuRegisterCallback_CTC(TIM2cbf_t Add_Fun );

TIM2_Error_Status_t TIM2_enuRegisterCallback_OVF( TIM2cbf_t Add_Fun);

TIM2_Error_Status_t TIM2_enuStart(void) ; 

void TIM2_enuSet_OC_Value (u8 Cpy_u8Value);

TIM2_Error_Status_t TIM2_enuSetDutyCycle( u8 Copy_u8Duty);

void TIM2_vidSetPreloadValue(u8 Copy_u8Preload);

#endif /* TIM2_H_ */