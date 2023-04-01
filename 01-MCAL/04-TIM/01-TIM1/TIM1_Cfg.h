/*
* TIM1_Cfg.h
*
* Created: 26-Feb-23 1:25:06 PM
*  Author: Peter Ghali
*/


#ifndef TIM1_CFG_H_
#define TIM1_CFG_H_
/*
A macro to define the Mode of Timer0
Options :
TIM1_Mode_OVF
TIM1_Mode_CTC
TIM1_Mode_PWM_Phase_Correct
TIM1_Mode_Fast_PWM
*/
#define TIM1_Mode			TIM1_Mode_Fast_PWM

/*
A macro to define the value to compared if the CTC mode to be chosen
options :: 1 -> 255
*/
#if TIM1_Mode == TIM1_Mode_CTC
#define TIM1_CTC_VALUE	125
#endif
/*
A macro to define the Pre_scaler of Timer0

Options :
TIM1_Pre_Scaler_0
TIM1_Pre_Scaler_8
TIM1_Pre_Scaler_64
TIM1_Pre_Scaler_256
TIM1_Pre_Scaler_1024
*/

#define	TIM1_Pre_Scaler		TIM1_Pre_Scaler_64
/*
A macro to define how you would like to see the output of the time
either on the OC0 PIn or using the Interrupt or both
Options :
TIM1_HW_PIN
TIM1_Interrupt
TIM1_HW_And_Interrupt
*/
#define TIM1_PIN	TIM1_HW_And_Interrupt

/*
A macro to define how you would like to use the OC0 PIN
in case of the Overflow mode or the CTC mode (non_PWM mode)
Options :
TOGGL_OC0_ON_COMPARE_MATCH
CLEAR_OC0_ON_COMPARE_MATCH
SET_OC0_ON_COMPARE_MATCH
*/
#define TIM1_OC0_PIN_MODE	CLEAR_OC0_ON_COMPARE_MATCH_SET_AT_BOTTOM
/*
#if (TIM1_Mode == TIM1_Mode_OVF)
#elif  (TIM1_Mode == TIM1_Mode_CTC)
#elif (TIM1_PIN == TIM1_HW_And_Interrupt )
#elif (TIM1_PIN == TIM1_HW_PIN)

#endif*/
/*
A macro to define how you would like to use the OC0 PIN
in case of the Fast PWM Mode
Options :
TOGGL_OC0_ON_COMPARE_MATCH
CLEAR_OC0_ON_COMPARE_MATCH
SET_OC0_ON_COMPARE_MATCH
*/
/*
#if (TIM1_Mode == TIM1_Mode_Fast_PWM)
#if (TIM1_PIN == TIM1_HW_And_Interrupt )
#elif (TIM1_PIN == TIM1_HW_PIN)
#define TIM1_OC0_PIN_MODE	CLEAR_OC0_ON_COMPARE_MATCH_SET_AT_BOTTOM
#endif
#endif*/

/*
A macro to define how you would like to use the OC0 PIN
in case of the Phase Correct  PWM Mode
Options :
TOGGL_OC0_ON_COMPARE_MATCH
CLEAR_OC0_ON_COMPARE_MATCH
SET_OC0_ON_COMPARE_MATCH
*/
/*
#if ((TIM1_Mode == TIM1_Mode_PWM_Phase_Correct) && ((TIM1_PIN == TIM1_HW_And_Interrupt ) || (TIM1_PIN == TIM1_HW_PIN)))
#define TIM1_OC0_PIN_MODE	CLEAR_OC0_ON_COMPARE_MATCH_UP_SET_AT_DOWN
#endif*/

#endif /* TIM1_CFG_H_ */