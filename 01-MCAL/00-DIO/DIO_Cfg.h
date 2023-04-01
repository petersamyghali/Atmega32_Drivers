/*

DIO Configuration File
?Author : Peter_Ghali
Data : 12th Jan. 2023

*/
//Start of the guard
#ifndef	DIO_CFG_H
#define	DIO_CFG_H

#include "../../00-LIB/STD_TYPES.h"
//An enum data type to have the modes the PIN may be configured as 
typedef enum {
	DIO_DIR_INPUT = 0	,
	DIO_INPUT_PULL_UP	,
	DIO_INPUT_TRI_STATE ,
	DIO_DIR_OUTPUT 		,
	DIO_OUTPUT_HIGH		,
	DIO_OUTPUT_LOW	 ,
}DIO_enuModet;

//A struct data type to indicate the PIN direction and its status 
typedef struct {
	
	u8 DIO_PinDirection ;
	u8 DIO_InputStatus;
	
}DIO_strPinCfg_t;
//extern the configurations the user have applied to the DIO PINS 
extern const DIO_strPinCfg_t DIO_strPinCfg [32];





#endif/*DIO_CFG_H*/