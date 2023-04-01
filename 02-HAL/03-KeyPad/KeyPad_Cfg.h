/*
* KeyPad_Cfg.h
*
* Created: 21-Jan-23 9:03:09 AM
*  Author: Peter Ghali
*/


#ifndef KeyPad_CFG_H_
#define KeyPad_CFG_H_

#include "STD_TYPES.h"
//#include "KeyPad.h"
// a couple of macros to define the number or rows
//and the number of columns in the keypad
#define NUMBER_OF_COLMUNS		4

#define NUMBER_OF_ROWS			4

//extern the numbers that has been configured in the keypad
extern u8 KeyPad_LookUpTable [NUMBER_OF_ROWS] [NUMBER_OF_COLMUNS] ;
//extern the columns pins 
extern const u8 KeyPad_ArrColsCfg [ NUMBER_OF_COLMUNS];
//extern the Rows pins 
extern const u8 KeyPad_ArrRowsCfg [ NUMBER_OF_ROWS] ; 


#endif /* KeyPad_CFG_H_ */