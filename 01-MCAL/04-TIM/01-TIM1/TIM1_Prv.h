/*
* TIM1_Prv.h
*
* Created: 26-Feb-23 1:25:16 PM
*  Author: Peter Ghali
*/


#ifndef TIM1_PRV_H_
#define TIM1_PRV_H_


#define TIMSK	*((volatile u8*)0x59)
#define TIMSK_TOIE1		2
#define TIMSK_OCIE1A		4
#define TIMSK_OCIE1B		3
#define TIMSK_TICIE1		5

#define TIFR	*((volatile u8*)0x58)
#define TIFR_TOV1		2
#define TIFR_ICF1		5
#define TIFR_OCF1A		4
#define TIFR_OCF1B		3

#define TCCR1A	*((volatile u8*)0x4F)
#define TCCR1B	*((volatile u8*)0x4E)
#define TCCR1B_ICES1	6


#define TCNT1	*((volatile u16*)0x4C)


#define OCR1A	*((volatile u16*)0x4A)


#define OCR1B	 *((volatile u16*)0x48)

#define ICR1	*((volatile u16*)0x46)



#define		TIM1_Mode_OVF					0b00000000
#define		TIM1_Mode_CTC					0b00001000
#define		TIM1_Mode_PWM_Phase_Correct		0b01000000
#define		TIM1_Mode_Fast_PWM				0b01001000

#define		TIM1_Pre_Scaler_0		1
#define		TIM1_Pre_Scaler_8		2
#define		TIM1_Pre_Scaler_64		3
#define		TIM1_Pre_Scaler_256		4
#define		TIM1_Pre_Scaler_1024	5

#define		TIM1_HW_PIN				8
#define		TIM1_Interrupt			9
#define		TIM1_HW_And_Interrupt	10

#define TOGGL_OC0_ON_COMPARE_MATCH	0b00010000
#define	CLEAR_OC0_ON_COMPARE_MATCH	0b00100000
#define SET_OC0_ON_COMPARE_MATCH	0b00110000

#define CLEAR_OC0_ON_COMPARE_MATCH_SET_AT_BOTTOM	0b00100000
#define SET_OC0_ON_COMPARE_MATCH_CLEAR_AT_BOTTOM	0b00110000

#define CLEAR_OC0_ON_COMPARE_MATCH_UP_SET_AT_DOWN	0b00100000
#define SET_OC0_ON_COMPARE_MATCH_UP_CLEAR_AT_DOWN	0b00110000



#endif /* TIM1_PRV_H_ */