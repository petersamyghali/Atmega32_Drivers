/*
 * EXTI_Prv.h
 *
 * Created: 24-Jan-23 9:42:08 PM
 *  Author: Peter Ghali
 */ 


#ifndef EXTI_PRV_H_
#define EXTI_PRV_H_
//The needed addresses in this module 
#define SREG_REGISTER		(*(volatile u8* ) 0x5F)



// defining the I_Bit by its position in the SREG register 
#define I_BIT	7









#endif /* EXTI_PRV_H_ */