/*
 * EXTI.h
 *
 * Created: 24-Jan-23 9:41:39 PM
 *  Author: Peter Ghali
 */ 


#ifndef EXTI_H_
#define EXTI_H_
//An Enum that holds the Errors 
typedef enum
{
	EXTI_enuOK = 0,
	EXTI_enuNotOK,
	EXTI_enuInavalidINT_Number,
	EXTI_enuInavalidINT_Type,
	EXTI_enuInavalidParametrs,
	EXTI_enuInavalidMode,
	EXTI_enuNULLPtr,
	
}EXTI_tenuErrorStatus;

/*
EXTI Enable Function :
A function that sets the I bit for the global interrupt and the EXTI as configured
Input	: void
return	: EXTI_tenuErrorStatus to report error
*/
EXTI_tenuErrorStatus EXTI_enuEnable(void);
/*
EXTI Disable Function :
A function that Disable the I bit for the global interrupt
Input	: void
return	: EXTI_tenuErrorStatus to report error
*/
EXTI_tenuErrorStatus EXTI_enuDisable(void);
/*
EXTI Disable Function :
A function to know the address of the function to be executed when firing the interrupt 
Input	: A pointer to function 
return	: EXTI_tenuErrorStatus to report error
*/
EXTI_tenuErrorStatus EXTI0_enuSetCallBack(void (*Cpy_pvINT0Func) (void) );

/*
EXTI Disable Function :
A function to know the address of the function to be executed when firing the interrupt
Input	: A pointer to function
return	: EXTI_tenuErrorStatus to report error
*/
EXTI_tenuErrorStatus EXTI1_enuSetCallBack(void (*Cpy_pvINT0Func) (void) );

/*
EXTI Disable Function :
A function to know the address of the function to be executed when firing the interrupt
Input	: A pointer to function
return	: EXTI_tenuErrorStatus to report error
*/
EXTI_tenuErrorStatus EXTI2_enuSetCallBack(void (*Cpy_pvINT0Func) (void) );

#endif /* EXTI_H_ */