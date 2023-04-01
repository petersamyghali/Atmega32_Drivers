/*
* TIM0.h
*
* Created: 26-Feb-23 1:24:36 PM
*  Author: Peter Ghali
*/


#ifndef TIM0_H_
#define TIM0_H_

#include "TIM0_Cfg.h"
#include "TIM0_Prv.h"

typedef enum
{
	TIM0_Normal_Mode ,
	TIM0_PWM_Phase_Correct_Mode ,
	TIM0_CTC_Mode  ,
	TIM0_Fast_PWM_Mode ,
}TIM0_Modes_t;

typedef enum
{
	TIM_OK ,
	TIM_Not_Ok,
	TIM_NULL_PTR ,
	TIM_Invalid_Pre_Scaleer ,
	TIM_Invalid_Mode,	
}TIM_Error_Status_t;

typedef enum
{
	TASK_Periodic ,
	TASK_ONCE
}TIM_Task_T;

TIM_Error_Status_t TIM0_enuInit(void);

TIM_Error_Status_t TIM0_vidDelay_ms_Busy_Waiting(u16 Cpy_Delay_ms ,void (*TIM0cbf_t)(void) );

TIM_Error_Status_t TIM0_vidDelay_ms(u16 Cpy_Delay_ms );

TIM_Error_Status_t TIM0_vidDelay_ms_INT(u16 Cpy_Delay_ms ,void (*TIM0cbf_t)(void) ,TIM_Task_T Cpy_Task_Type);

TIM_Error_Status_t TIM0_enuRegisterCallback_CTC( void (*TIM0cbf_t)(void));

TIM_Error_Status_t TIM0_enuRegisterCallback_OVF( void (*TIM0cbf_t)(void));

TIM_Error_Status_t TIM0_enuStart(void) ;

void TIM0_enuSet_OC_Value (u8 Cpy_u8Value);

TIM_Error_Status_t TIM0_enuSetDutyCycle( u8 Copy_u8Duty);

void TIM0_vidSetPreloadValue(u8 Copy_u8Preload);

#endif /* TIM0_H_ */