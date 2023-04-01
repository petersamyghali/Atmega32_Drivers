/*
* TIM0_Cfg.h
*
* Created: 26-Feb-23 1:25:06 PM
*  Author: Peter Ghali
*/


#ifndef TIM0_CFG_H_
#define TIM0_CFG_H_
/*
A macro to define the Mode of Timer0
Options :
TIM0_Mode_OVF
TIM0_Mode_CTC
TIM0_Mode_PWM_Phase_Correct
TIM0_Mode_Fast_PWM
*/
#define TIM0_Mode			TIM0_Mode_CTC

/*
A macro to define the value to compared if the CTC mode to be chosen
options :: 1 -> 255
*/
#define TIM0_CTC_VALUE	125

/*
A macro to define the Pre_scaler of Timer0

Options :
TIM0_Pre_Scaler_1
TIM0_Pre_Scaler_8
TIM0_Pre_Scaler_64
TIM0_Pre_Scaler_256
TIM0_Pre_Scaler_1024
*/

#define	TIM0_Pre_Scaler		TIM0_Pre_Scaler_64
/*
A macro to define how you would like to see the output of the time
either on the OC0 PIn or using the Interrupt or both
Options :
TIM0_HW_PIN
TIM0_Interrupt
TIM0_HW_And_Interrupt
*/
#define TIM0_PIN	TIM0_HW_And_Interrupt

/*
A macro to define how you would like to use the OC0 PIN
in case of the Overflow mode or the CTC mode (non_PWM mode)
Options :
//For non PWM Mode 
TOGGL_OC0_ON_COMPARE_MATCH
CLEAR_OC0_ON_COMPARE_MATCH
SET_OC0_ON_COMPARE_MATCH

//For PWM Mode
CLEAR_OC0_ON_COMPARE_MATCH_SET_AT_BOTTOM
SET_OC0_ON_COMPARE_MATCH_CLEAR_AT_BOTTOM

//For Phase correct Mode 
CLEAR_OC0_ON_COMPARE_MATCH_UP_SET_AT_DOWN
SET_OC0_ON_COMPARE_MATCH_UP_CLEAR_AT_DOWN
*/
#define TIM0_OC0_PIN_MODE	TOGGL_OC0_ON_COMPARE_MATCH


#endif /* TIM0_CFG_H_ */