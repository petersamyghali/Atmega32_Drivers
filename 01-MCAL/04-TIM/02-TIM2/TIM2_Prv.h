/*
* TIM2_Prv.h
*
* Created: 26-Feb-23 1:25:16 PM
*  Author: Peter Ghali
*/


#ifndef TIM2_PRV_H_
#define TIM2_PRV_H_


#define TIMSK	*((volatile u8*)0x59)
#define TIMSK_TOIE2		6
#define TIMSK_OCIE2		7

#define TIFR	*((volatile u8*)0x58)
#define TIFR_TOV2		6
#define TIFR_OCF2		7


#define		TIM2_Mode_OVF					0b00000000
#define		TIM2_Mode_CTC					0b00001000
#define		TIM2_Mode_PWM_Phase_Correct		0b01000000
#define		TIM2_Mode_Fast_PWM				0b01001000


#define		TIM2_Pre_Scaler_0		1
#define		TIM2_Pre_Scaler_8		2
#define		TIM2_Pre_Scaler_32		3
#define		TIM2_Pre_Scaler_64		4
#define		TIM2_Pre_Scaler_128		5
#define		TIM2_Pre_Scaler_256		6
#define		TIM2_Pre_Scaler_1024	7

#define		TIM2_HW_PIN				8
#define		TIM2_Interrupt			9
#define		TIM2_HW_And_Interrupt	10

#define TOGGL_OC2_ON_COMPARE_MATCH	0b00010000
#define	CLEAR_OC2_ON_COMPARE_MATCH	0b00100000
#define SET_OC2_ON_COMPARE_MATCH	0b00110000

#define CLEAR_OC2_ON_COMPARE_MATCH_SET_AT_BOTTOM	0b00100000
#define SET_OC2_ON_COMPARE_MATCH_CLEAR_AT_BOTTOM	0b00110000

#define CLEAR_OC2_ON_COMPARE_MATCH_UP_SET_AT_DOWN	0b00100000
#define SET_OC2_ON_COMPARE_MATCH_UP_CLEAR_AT_DOWN	0b00110000

#define TCCR1A	*((volatile u8*)0x4F)
#define TCCR1B	*((volatile u8*)0x4E)
#define TCNT1H	*((volatile u8*)0x4D)
#define TCNT1L	*((volatile u8*)0x4C)
#define OCR1AH	*((volatile u8*)0x4B)
#define OCR1AL	*((volatile u8*)0x4A)
#define OCR1BH	*((volatile u8*)0x49)
#define OCR1BL	*((volatile u8*)0x48)
#define ICR1H	*((volatile u8*)0x47)
#define ICR1L	*((volatile u8*)0x46)

#define TCCR2	*((volatile u8*)0x45)
#define TCNT2	*((volatile u8*)0x44)
#define OCR2	*((volatile u8*)0x43)



#endif /* TIM2_PRV_H_ */