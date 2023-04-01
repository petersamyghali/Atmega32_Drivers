/*
* SSegment_Cfg.c
*
* Created: 21-Jan-23 9:03:45 AM
*  Author: Peter Ghali
*/
#include "../../00-LIB/STD_TYPES.h"

#include "SSegment.h"
#include "SSegment_Cfg.h"


#include "../../01-MCAL/00-DIO/DIO.h"

u8 SSegment_LookUpTable [NUMBERS_DISPLAYED] = {
	
	[ZERO]	= 0b0111111,
	[ONE]	= 0b0000110,
	[TWO]	= 0b1011011,
	[THREE] = 0b1001111,
	[FOUR]	= 0b1100110,
	[FIVE]	= 0b1101101,
	[SIX]	= 0b1111101,
	[SEVEN]	= 0b0000111,
	[EIGHT] = 0b1111111,
	[NINE]	= 0b1101111

};

const SSegment_strSSegmentCfg_t SSegment_strSSegmentCfg [NUMBER_OFSSegmentS] =
{
	//THE right most number 
	[SSegment_enu_SSegment0] =
	{
		.SSegment_Type = SSegment_enuCommonAnode ,
		.SSegment_PINS =
		{
			DIO_enuPORTB_Pin0,	//A
			DIO_enuPORTB_Pin1,	//B
			DIO_enuPORTB_Pin2,	//C
			DIO_enuPORTB_Pin3,	//D
			DIO_enuPORTB_Pin4,	//E
			DIO_enuPORTB_Pin5,	//F
			DIO_enuPORTB_Pin6,	//G
			DIO_enuPORTB_Pin7,	//.
		},
	} ,
	
	[SSegment_enu_SSegment1] =
	{
		.SSegment_Type = SSegment_enuCommonAnode ,
		.SSegment_PINS =
		{
			DIO_enuPORTC_Pin0,	//A
			DIO_enuPORTC_Pin1,	//B
			DIO_enuPORTC_Pin2,	//C
			DIO_enuPORTC_Pin3,	//D
			DIO_enuPORTC_Pin4,	//E
			DIO_enuPORTC_Pin5,	//F
			DIO_enuPORTC_Pin6,	//G
			DIO_enuPORTC_Pin7,	//.
		},
	} ,
	
	// 	[SSegment_enu_SSegment2] =
	// 	{
	// 		.SSegment_Type = SSegment_enuCommonAnode ,
	// 		.SSegment_PINS =
	// 		{
	// 			DIO_enuPORTC_Pin0,	//A
	// 			DIO_enuPORTC_Pin1,	//B
	// 			DIO_enuPORTC_Pin2,	//C
	// 			DIO_enuPORTC_Pin3,	//D
	// 			DIO_enuPORTC_Pin4,	//E
	// 			DIO_enuPORTC_Pin5,	//F
	// 			DIO_enuPORTC_Pin6,	//G
	// 			DIO_enuPORTC_Pin7,	//.
	// 		},
	// 	} ,
	
};