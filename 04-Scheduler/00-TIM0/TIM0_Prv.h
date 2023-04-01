/*
* TIM0_Prv.h
*
* Created: 26-Feb-23 1:25:16 PM
*  Author: Peter Ghali
*/


#ifndef TIM0_PRV_H_
#define TIM0_PRV_H_


#define TIMSK	*((volatile u8*)0x59)
#define TIMSK_TOIE0		0
#define TIMSK_OCIE0		1

#define TIFR	*((volatile u8*)0x58)
#define TIFR_TOV0		0
#define TIFR_OCF0		1

#define OCR0	*((volatile u8*)0x5C)
#define TCCR0	*((volatile u8*)0x53)
#define TCNT0	*((volatile u8*)0x52)

#define		TIM0_Mode_OVF					0b00000000
#define		TIM0_Mode_CTC					0b00001000
#define		TIM0_Mode_PWM_Phase_Correct		0b01000000
#define		TIM0_Mode_Fast_PWM				0b01001000

#define		TIM0_No_Clk_Soruce		0
#define		TIM0_Pre_Scaler_1		1
#define		TIM0_Pre_Scaler_8		2
#define		TIM0_Pre_Scaler_64		3
#define		TIM0_Pre_Scaler_256		4
#define		TIM0_Pre_Scaler_1024	5

#define		TIM0_HW_PIN				8
#define		TIM0_Interrupt			9
#define		TIM0_HW_And_Interrupt	10

#define TOGGL_OC0_ON_COMPARE_MATCH	0b00010000
#define	CLEAR_OC0_ON_COMPARE_MATCH	0b00100000
#define SET_OC0_ON_COMPARE_MATCH	0b00110000

#define CLEAR_OC0_ON_COMPARE_MATCH_SET_AT_BOTTOM	0b00100000
#define SET_OC0_ON_COMPARE_MATCH_CLEAR_AT_BOTTOM	0b00110000

#define CLEAR_OC0_ON_COMPARE_MATCH_UP_SET_AT_DOWN	0b00100000
#define SET_OC0_ON_COMPARE_MATCH_UP_CLEAR_AT_DOWN	0b00110000

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



#endif /* TIM0_PRV_H_ */