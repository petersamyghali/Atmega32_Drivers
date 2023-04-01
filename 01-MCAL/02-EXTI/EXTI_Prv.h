/*
 * EXTI_Prv.h
 *
 * Created: 24-Jan-23 9:42:08 PM
 *  Author: Peter Ghali
 */ 


#ifndef EXTI_PRV_H_
#define EXTI_PRV_H_
//the needed addresses to be accessed in order to configure the EXTI 
#define GICR_REGISTER		(*(volatile u8* ) 0x5B)
#define MCUCR_REGISTER		(*(volatile u8* ) 0x55)
#define MCUCSR_REGISTER		(*(volatile u8* ) 0x54)
#define GIFR_REGISTER		(*(volatile u8* ) 0x5A)
//Some needed macros 
#define RISING_EDGE		0
#define FALLING_EDGE	1
#define ANY_CHANGE		2
#define LOW_LEVEL		3
#define DISABLE			4
//Defining each interrupt as per its position in the register
#define EXTI0	6
#define EXTI1	7
#define EXTI2	5
//defining each mode to mask it with the required register 
#define EXTI0_RISING_EDGE	0b00000011	
#define EXTI0_FALLING_EDGE	0b00000010
#define EXTI0_LOW_LEVEL		0b00000000
#define EXTI0_ANY_CHANGE	0b00000001
//defining each mode to mask it with the required register 
#define EXTI1_RISING_EDGE	0b00001100
#define EXTI1_FALLING_EDGE	0b00001000
#define EXTI1_LOW_LEVEL		0b00000000
#define EXTI1_ANY_CHANGE	0b00000100
//defining each mode to mask it with the required register 
#define EXTI2_RISING_EDGE	0b01000000
#define	EXTI2_FALLING_EDGE	0b00000000









#endif /* EXTI_PRV_H_ */