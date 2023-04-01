/*
* SSegment.c
*
* Created: 21-Jan-23 9:02:34 AM
*  Author: Peter Ghali
*/
#include "../../00-LIB/BIT_MATH.h"
#include "../../00-LIB/STD_TYPES.h"

#include "../../01-MCAL/00-DIO/DIO.h"

#include "SSegment.h"
#include "SSegment_Cfg.h"
#include "SSegment_Prv.h"

//INit the 7 segment/s by zero 

_7_Seg_enuErrorStatus SSegment_enuInit(void)
{
	u8 PINS_Counter = ZERO ;
	u8 BIT = ZERO ;
	u8 LocalCounter2  = ZERO;
	_7_Seg_enuErrorStatus Error_Status = SSegment_enuOk ;
//for loop to iterate by the number of the SSegments 
	for (LocalCounter2  = ZERO ; LocalCounter2  < NUMBER_OFSSegmentS ; LocalCounter2++)
	{
		//checking if the type either a common anode nor a common cathode 
		if(SSegment_strSSegmentCfg[LocalCounter2].SSegment_Type  == SSegment_enuCommonAnode)
		{
			//a for loop to light each led in the SSegment if it is a common Anode 
			// 0 to light it up as the common pin is connected to the VCC 
			for ( PINS_Counter = ZERO ; PINS_Counter  <  MAX_NUM_DISPLAYED - 1  ; PINS_Counter++ )
			{
				//go to the look up table and check each pin 
				BIT = GET_BIT(SSegment_LookUpTable[ZERO],PINS_Counter);
				//if it is a 1(LED ON) 
				//clear the DIO pin to light it up 
				if (1 == BIT)
				{
					DIO_enuClearPin(SSegment_strSSegmentCfg[LocalCounter2].SSegment_PINS[PINS_Counter]);
				}
				//if it is a zero 
				//set the DIO pin to dim it 
				else
				{
					DIO_enuSetPin(SSegment_strSSegmentCfg[LocalCounter2].SSegment_PINS[PINS_Counter]);
				}
			}
		}
		//if the SSegmet is common cathode 
		else if(SSegment_strSSegmentCfg[LocalCounter2].SSegment_Type == SSegment_enuCommonCathode)
		{
			//a for loop to light each led in the SSegment if it is a common cathode 
			// 1 to light it up as the common pin is connected to the ground
			for ( PINS_Counter = ZERO ; PINS_Counter  <  MAX_NUM_DISPLAYED - 1  ; PINS_Counter++)
			{
				
				BIT = GET_BIT(SSegment_LookUpTable[ZERO],PINS_Counter);
				//if the given bit is 1
				if (1 == BIT)
				{
					//Set the DIO pin in order to light it up 
					DIO_enuSetPin(SSegment_strSSegmentCfg[LocalCounter2].SSegment_PINS[PINS_Counter]);
				}
				else
				{
					//Clear  the DIO pin in order to dim it 
					DIO_enuClearPin(SSegment_strSSegmentCfg[LocalCounter2].SSegment_PINS[PINS_Counter]);
				}
			}
		}
		else
		{
			//if there is a problem in the CFGs return an error 
			Error_Status = SSegment_enuInvalidPINType ;
		}
	}
	return Error_Status ;
}

// a function to set the given number to all the SSegment/s 
_7_Seg_enuErrorStatus SSegment_enuSetNumber (u16 Cpy_u8Number)
{
	u8 LocalCounter  = ZERO;
	u8 PINS_Counter = ZERO ;
	u8 BIT = ZERO ;
	u8 Counter =  ZERO;
	u8 Counter2 = ZERO ;
	//An array of u8s to have split the given number to 4 digits separated 
	u8 Loc_Temp_Number[4] = {0} ;
	u8 LocalCounter2  = ZERO;
	_7_Seg_enuErrorStatus Error_Status = SSegment_enuOk ;
	//a fore loop to split the given number 
	for(LocalCounter  = ZERO ; Cpy_u8Number != 0 ; LocalCounter++)
	{
		//add the most right number to the first position in the array 
		Loc_Temp_Number[LocalCounter] = Cpy_u8Number % 10 ;
		//divide the number by 10 to eliminate  the most right number 
		Cpy_u8Number = Cpy_u8Number/10;
		//increment the counter 
		Counter++ ;
	}
	Counter--;
	
	if (Cpy_u8Number > NUMBER_OFSSegmentS * 9)
	{
		Error_Status = SSegment_enuInvalidNumber ;
	}

	else
	{
		
		for (LocalCounter2  = ZERO ; LocalCounter2  < NUMBER_OFSSegmentS ; LocalCounter2++)
		{
			if(SSegment_strSSegmentCfg[LocalCounter2].SSegment_Type  == SSegment_enuCommonAnode)
			{
				
				for ( PINS_Counter = ZERO ; PINS_Counter  <  MAX_NUM_DISPLAYED - 1  ; PINS_Counter++ )
				{
					BIT = GET_BIT(SSegment_LookUpTable[Loc_Temp_Number[LocalCounter2]],PINS_Counter);
					if (BIT)
					{
						DIO_enuClearPin(SSegment_strSSegmentCfg[LocalCounter2].SSegment_PINS[PINS_Counter]);
					}
					else
					{
						DIO_enuSetPin(SSegment_strSSegmentCfg[LocalCounter2].SSegment_PINS[PINS_Counter]);
					}
				}
			}
			else if(SSegment_strSSegmentCfg[LocalCounter2].SSegment_Type == SSegment_enuCommonCathode)
			{
				for ( PINS_Counter = ZERO ; PINS_Counter  <  MAX_NUM_DISPLAYED - 1  ; PINS_Counter++)
				{
					BIT = GET_BIT(SSegment_LookUpTable[Loc_Temp_Number[Counter]],PINS_Counter);
					if (BIT)
					{
						DIO_enuSetPin(SSegment_strSSegmentCfg[LocalCounter2].SSegment_PINS[PINS_Counter]);
					}
					else
					{
						DIO_enuClearPin(SSegment_strSSegmentCfg[LocalCounter2].SSegment_PINS[PINS_Counter]);
					}
				}
			}
			else
			{
				Error_Status = SSegment_enuInvalidPINType ;
			}
			Counter2++;
		}
	}
	return Error_Status ;
}