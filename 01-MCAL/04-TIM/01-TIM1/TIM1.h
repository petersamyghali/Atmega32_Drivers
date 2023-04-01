/*
* TIM1.h
*
* Created: 26-Feb-23 1:24:36 PM
*  Author: Peter Ghali
*/


#ifndef TIM1_H_
#define TIM1_H_



typedef enum
{
	OVF = 2  ,
	COMB ,
	COMBA ,
	ICU ,
	MAX_TIM1_INT,
}TIM1_INT_EN_t;

typedef enum
{
	TIM1_Normal_Mode ,
	TIM1_PWM_Phase_Correct_8_bit ,
	TIM1_PWM_Phase_Correct_9_bit ,
	TIM1_PWM_Phase_Correct_10_bit ,
	TIM1_CTC_Mode_Top_OCR1A ,
	TIM1_Fast_PWM_8_bit ,
	TIM1_Fast_PWM_9_bit ,
	TIM1_Fast_PWM_10_bit ,
	TIM1_PWM_Phase_and_Frequency_Correct_Top_ICR1,
	TIM1_PWM_Phase_and_Frequency_Correct_Top_OCR1A ,
	TIM1_PWM_Phase_Correct_Top_ICR1,
	TIM1_PWM_Phase_Correct_Top_OCR1A ,
	TIM1_CTC_Mode_Top_ICR1 ,
	TIM1_Fast_PWM_Top_ICR1=14  ,
	TIM1_Fast_PWM_Top_OCR1A ,
}TIM1_Modes_t;

typedef enum
{
	TIM1_No_Clk_Soruce ,
	TIM1_Pre_Scaler_0,
	TIM1_Pre_Scaler_8,
	TIM1_Pre_Scaler_64,
	TIM1_Pre_Scaler_256,
	TIM1_Pre_Scaler_1024,
	TIM1_External_Falling,
	TIM1_External_Rising,
}TIM1_Clock_t;

typedef enum
{
	TIM1_OK ,
	TIM1_Not_Ok,
	TIM1_NULL_PTR ,
	TIM1_Invalid_Pre_Scaleer ,
	TIM1_Invalid_Mode,
}TIM1_Error_Status_t;

typedef enum
{
	/*for non PWM Modes */
	OC1A_Toggle_ON_COM = 64  ,
	OC1A_SET_ON_COM = 192 ,
	OC1A_Clear_ON_COM  = 128 ,
	
	OC1B_Toggle_ON_COM =16,
	OC1B_SET_ON_COM  = 48  ,
	OC1B_Clear_ON_COM = 32  ,
	/*Fast PWM Mode*/
	Toggle_OC1A_on_COM = 64,
	OC1B_disconnected = 16,
	Clear_OC1A_on_compare_match_set_OC1A_at_BOTTOM = 128,
	Clear_OC1B_on_compare_match_set_OC1B_at_BOTTOM  = 32,
	Set_OC1A_on_compare_match_Clear_OC1A_at_BOTTOM  = 192,
	Set_OC1B_on_compare_match_Clear_OC1B_at_BOTTOM  = 48,
	/*Phase Correct and Phase and Frequency Correct PWM Modes*/
	Toggle_OC1A_on_Compare_Match = 64,
	Clear_OC1A_when_up_counting_Set_OC1A_when_downcounting = 128,
	Clear_OC1B_when_up_counting_Set_OC1B_when_downcounting =32 ,
	Set_OC1A_when_up_counting_Clear_OC1A_when_downcounting = 192,
	Set_OC1B_when_up_counting_Clear_OC1B_when_downcounting = 48 ,
	
	
}TIM1_OC1_t;

typedef enum
{
	ICU_Trigger_Rising_Edge =1  ,
	ICU_Trigger_Falling_Edge = 0  ,
}TIM1_enuICU_Trigger_t;

typedef enum
{
	Flag_HIGH= 1  ,
	Flag_Low  = 0
}TIM1_Flag;


TIM1_Error_Status_t TIM1_enuSet_Mode (TIM1_Modes_t CPY_Mode);

/*This function shall only be used in case of a non PWM Mode */
TIM1_Error_Status_t TIM1_enuSetC_OC1_Pin (TIM1_OC1_t Cpy_Mode);

TIM1_Error_Status_t TIM1_enuICU_Trigger(TIM1_enuICU_Trigger_t Cpy_ICE_Trigger);

TIM1_Error_Status_t TIM1_enuSetCLK (TIM1_Clock_t Cpy_CLK);

TIM1_Error_Status_t TIM1_enuSet_Timer_Value (u16 Cpy_Value );

TIM1_Error_Status_t TIM1_enuGet_Timer_Value (u16 *Cpy_Value );

TIM1_Flag TIM1_enuGet_Timer_Flag  (TIM1_INT_EN_t Cpy_Flag);

TIM1_Error_Status_t TIM1_enuGet_Timer_OVFs_Count (volatile u16 * Cpy_Value);

void TIM1_enuSet_Timer_OVFs_Count (u16  Cpy_Value);


TIM1_Error_Status_t TIM1_enuGet_Timer_ICR_Value (u16 *Cpy_Value );

TIM1_Error_Status_t TIM1_enuRegisterCallback_CTC_B( void (*TIM1cbf_t)(void));

TIM1_Error_Status_t TIM1_enuRegisterCallback_CTC_A( void (*TIM1cbf_t)(void));

TIM1_Error_Status_t TIM1_enuRegisterCallback_OVF( void (*TIM1cbf_t)(void));

TIM1_Error_Status_t TIM1_enuRegisterCallback_ICU ( void (*TIM1cbf_t)(void));

TIM1_Error_Status_t TIM1_enuEnableINT(TIM1_INT_EN_t Cpy_INT);

TIM1_Error_Status_t TIM1_enuClearINT_Flag(TIM1_INT_EN_t Cpy_INT);

void TIM1_enuStart(void) ;

void TIM1_enuSet_OCA_Value (u16 Cpy_u16Value);

void TIM1_enuSet_OCB_Value (u16 Cpy_u16Value);

void TIM1_enuSet_ICR_Value (u16 Cpy_u16Value)  ;

TIM1_Error_Status_t TIM1_enuSetDutyCycle( u16 Cpy_u16Value);

void TIM1_vidSetPreloadValue(u16 Copy_u8Preload);

#endif /* TIM1_H_ */