/*
 * KeyPad.h
 *
 * Created: 21-Jan-23 9:03:59 AM
 *  Author: Peter Ghali
 */ 


#ifndef KeyPad_H_
#define KeyPad_H_

#include "../../00-LIB/STD_TYPES.h"

//An enum data type to have the error that may occur in the Keypad functions 
typedef enum{
	KeyPad_enuOk = 0,
	KeyPad_enuNotOk,
	KeyPad_enuNullPtr,
	KeyPad_enuInvalidPINNumber,
	KeyPad_enuInvalidNumber
}KeyPad_enuErrorStatus;
/*
Keypad init  Function :
A function that sets the DIO pin based on the given mode
Input	: Void 
return	: KeyPad_enuErrorStatus to report error
*/
KeyPad_enuErrorStatus KeyPad_enuInit (void) ; 

/*
Keypad init  Function :
A function that sets the DIO pin based on the given mode
Input	: Void 
return	: KeyPad_enuErrorStatus to report error
*/

KeyPad_enuErrorStatus KeyPad_enuGetKey(u8 * Add_u8KeyPressed);




#endif /* KeyPad_H_ */