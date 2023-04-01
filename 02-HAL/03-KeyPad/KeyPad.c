/*
* KeyPad.c
*
* Created: 21-Jan-23 9:02:34 AM
*  Author: Peter Ghali
*/
#include "../../00-LIB/BIT_MATH.h"
#include "../../00-LIB/STD_TYPES.h"

#include "../../01-MCAL/00-DIO/DIO.h"

#include "KeyPad.h"
#include "KeyPad_Cfg.h"
#include "KeyPad_Prv.h"
//SOME needed macros
#define KEY_PRESSED			0
#define KEY_NOT_PRESSED		1
#define ZERO				0
#define TIME_OUT_TRIALS		10000
//Initialize the keypad Row as input high (internally pulled up) &
//the Cols pins as Output high
KeyPad_enuErrorStatus KeyPad_enuInit (void)
{
	KeyPad_enuErrorStatus Error_Status = KeyPad_enuOk ;
	u8 LOC_u8RowCounter = ZERO , LOC_u8ColCounter  =  ZERO ;
	//the keypad Row as input high (internally pulled up)
	for ( LOC_u8RowCounter= 0 ; LOC_u8RowCounter < NUMBER_OF_ROWS ; LOC_u8RowCounter++)
	{
		DIO_enuSetPin(KeyPad_ArrRowsCfg[LOC_u8RowCounter]);
	}
	//the Cols pins as Output high
	for ( LOC_u8ColCounter = 0 ; LOC_u8ColCounter < NUMBER_OF_COLMUNS ; LOC_u8ColCounter++)
	{
		DIO_enuSetPin(KeyPad_ArrColsCfg[LOC_u8ColCounter]);
	}
	return Error_Status ;
}

//get the pressed key for the keypad 2D array
KeyPad_enuErrorStatus KeyPad_enuGetKey(u8 * Add_u8KeyPressed)
{
	KeyPad_enuErrorStatus Error_Status = KeyPad_enuOk ;
	u8 LOC_u8PinValue = KEY_NOT_PRESSED ;
	u8 LOC_u8RowCounter = ZERO ,LOC_u8ColCounter=  ZERO ;
	//u32 LOC_u32TimeOut  = ZERO ;
	//if the given address points to null then
	if (Add_u8KeyPressed == NULL )
	{
		Error_Status  = KeyPad_enuNullPtr ;
	}
	
	else {
		//a for loop to switch between the keypad pins in order to make only one by 0 (output low )
		for ( LOC_u8ColCounter =  ZERO ; LOC_u8ColCounter < NUMBER_OF_COLMUNS ; LOC_u8ColCounter++)
		{
			Error_Status = DIO_enuClearPin(KeyPad_ArrColsCfg[LOC_u8ColCounter]);
			//a for loop to check if the user had pressed any row key in that is connected to this col pin (the zero one )
			for ( LOC_u8RowCounter = ZERO; LOC_u8RowCounter < NUMBER_OF_ROWS ; LOC_u8RowCounter++)
			{
				// get the values in the Row pins
				Error_Status = DIO_enuGetPin(KeyPad_ArrRowsCfg[LOC_u8RowCounter], &LOC_u8PinValue);
				//is the user had pressed on a key
				if (  LOC_u8PinValue == KEY_PRESSED )
				{
					// put the key in this Col(the zero one ) and in the Row for the Keypad in the given address in this function
					* Add_u8KeyPressed = KeyPad_LookUpTable [LOC_u8RowCounter][LOC_u8ColCounter];
					/*wait until the key is released or the timeout occurs */
					/*while (LOC_u8PinValue == 0 && LOC_u32TimeOut <  TIME_OUT_TRIALS)
					{
						DIO_enuGetPin(KeyPad_ArrRowsCfg[LOC_u8RowCounter], &LOC_u8PinValue);
						LOC_u32TimeOut++;
					}*/
				}
				
			}
			//set this Col pin again to High
			DIO_enuSetPin(KeyPad_ArrColsCfg[LOC_u8ColCounter]);
		}
		
	}
	return Error_Status ;
}