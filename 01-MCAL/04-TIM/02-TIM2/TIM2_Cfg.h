/*
* TIM2_Cfg.h
*
* Created: 26-Feb-23 1:25:06 PM
*  Author: Peter Ghali
*/


#ifndef TIM2_CFG_H_
#define TIM2_CFG_H_
/*
A macro to define the Mode of Timer0
Options :
TIM2_Mode_OVF
TIM2_Mode_CTC
TIM2_Mode_PWM_Phase_Correct
TIM2_Mode_Fast_PWM
*/
#define TIM2_Mode			TIM2_Mode_Fast_PWM

/*
A macro to define the value to compared if the CTC mode to be chosen
options :: 1 -> 255
*/
#if TIM2_Mode == TIM2_Mode_CTC
#define TIM2_CTC_VALUE	125
#endif

#if TIM2_Mode == TIM2_Mode_OVF
#define TIM2_PRE_LOAD	0
#endif

/*
A macro to define the Pre_scaler of Timer0

Options :
TIM2_Pre_Scaler_0
TIM2_Pre_Scaler_8
TIM2_Pre_Scaler_32
TIM2_Pre_Scaler_64
TIM2_Pre_Scaler_128
TIM2_Pre_Scaler_256
TIM2_Pre_Scaler_1024
*/
#define	TIM2_Pre_Scaler		TIM2_Pre_Scaler_64
/*
A macro to define how you would like to see the output of the time
either on the OC2 PIn or using the Interrupt or both
Options :
TIM2_HW_PIN
TIM2_Interrupt
TIM2_HW_And_Interrupt
*/
#define TIM2_PIN	TIM2_HW_And_Interrupt

/*
A macro to define how you would like to use the OC2 PIN
Options :
TOGGL_OC2_ON_COMPARE_MATCH
CLEAR_OC2_ON_COMPARE_MATCH
SET_OC2_ON_COMPARE_MATCH
CLEAR_OC2_ON_COMPARE_MATCH_SET_AT_BOTTOM
SET_OC2_ON_COMPARE_MATCH_CLEAR_AT_BOTTOM
CLEAR_OC2_ON_COMPARE_MATCH_UP_SET_AT_DOWN
SET_OC2_ON_COMPARE_MATCH_UP_CLEAR_AT_DOWN
*/
#if (TIM2_OC2_PIN_MODE == TIM2_HW_And_Interrupt) || (TIM2_OC2_PIN_MODE == TIM2_Interrupt)
#define TIM2_OC2_PIN_MODE		CLEAR_OC2_ON_COMPARE_MATCH_SET_AT_BOTTOM
#endif



#endif /* TIM2_CFG_H_ */