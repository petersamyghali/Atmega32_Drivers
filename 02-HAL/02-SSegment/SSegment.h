/*
 * SSegment.h
 *
 * Created: 21-Jan-23 9:03:59 AM
 *  Author: Peter Ghali
 */ 


#ifndef SSegment_H_
#define SSegment_H_

#include "../../00-LIB/STD_TYPES.h"

#define MAX_NUM_DISPLAYED		9
#define NUMBER_OFSSegmentS		2
#define NUMBERS_DISPLAYED		10

typedef enum{
	SSegment_enuOk = 0,
	SSegment_enuNotOk,
	SSegment_enuNullPtr,
	SSegment_enuInvalidPINNumber,
	SSegment_enuInvalidPINType,
	SSegment_enuInvalidNumber
}_7_Seg_enuErrorStatus;

typedef enum {
	
	SSegment_enu_SSegment0 = 0 ,
	SSegment_enu_SSegment1 ,
	SSegment_enu_SSegment2 ,
	SSegment_enu_SSegment3 ,

}SSegment_tenuSSegmentCount;

typedef struct
{
	u8 SSegment_Type ;
	u8 SSegment_PINS[MAX_NUM_DISPLAYED] ;
}SSegment_strSSegmentCfg_t;

typedef enum {
	ZERO	=0,
	ONE	 ,
	TWO	 ,
	THREE ,
	FOUR ,
	FIVE ,
	SIX	 ,
	SEVEN ,
	EIGHT ,
	NINE ,
}SSegment_tenuSSegmentNumber;

typedef enum
{
	SSegment_enuCommonAnode =0 ,
	SSegment_enuCommonCathode ,
	
}SSegment_tenuSSegmentType;

_7_Seg_enuErrorStatus SSegment_enuInit(void);

_7_Seg_enuErrorStatus SSegment_enuSetNumber (u16 Cpy_u8Number);



#endif /* SSegment_H_ */