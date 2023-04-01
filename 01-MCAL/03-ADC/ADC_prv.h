/*
 * ADC_prv.h
 *
 * Created: 03-Feb-23 10:15:10 PM
 *  Author: Peter Ghali
 */ 


#ifndef ADC_PRV_H_
#define ADC_PRV_H_
#define	ADCSR		*(( volatile u8 * )0x28)
#define	ADMUX		*(( volatile u8 * )0x27)
#define	ADCSRA		*(( volatile u8 * )0x26)
#define	ADCH		*(( volatile u8 * )0x25)
#define	ADCL		*(( volatile u8 * )0x24)
#define	ADC_VALUE	*(( volatile u16*)0x24)
#define SFIOR		*(( volatile u8 * )0x50)

#define	ENABLE		1
#define DISABLE		0

#define ADC_MUX_CLAER_MASK			0b1110000

#define ADC_REF_MASK				0b00111111
#define ADC_REF_AREF				0b00000000
#define ADC_REF_AVCC				0b01000000
#define ADC_REF_INTERNAL			0b11000000

#define ADC_ENABLE					7
#define	ADC_ADJUST_LEFT				5
#define	ADC_START_CONVERSION		6
#define	ADC_AUTO_TRIGGER			5
#define	ADC_INTERRUPT_FLAG			4
#define	ADC_INTERRUPT_ENABLE		3

#define	ADC_PRE_SCALER_MASK			0b11111000
#define	ADC_PRE_SCALER_2			1
#define	ADC_PRE_SCALER_4			2
#define	ADC_PRE_SCALER_8			3
#define	ADC_PRE_SCALER_16			4
#define	ADC_PRE_SCALER_32			5
#define	ADC_PRE_SCALER_64			6
#define	ADC_PRE_SCALER_128			7

#define ADC_8BITS					0
#define ADC_10BITS					1

#define ADC_TRIGGER_PINS			5
#define ADC_TRIGGER_MASK			0b000
#define ADC_TRIGGER_FREE_RUNNIGN	0
#define ADC_TRIGGER_ANALOG_COMPA	1
#define ADC_TRIGGER_EXTI0			2
#define ADC_TRIGGER_TIM0_COMP		3
#define ADC_TRIGGER_TIM0_OVF		4
#define ADC_TRIGGER_TIM0_COMPB		5
#define ADC_TRIGGER_TIM1_OVF		6
#define ADC_TRIGGER_TIM1_CAP_EVENT	7

#define ADC_BUSY					1
#define ADC_READY					0

#endif /* ADC_PRV_H_ */