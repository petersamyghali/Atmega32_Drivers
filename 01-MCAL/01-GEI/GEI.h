/*
 * GEI.h
 *
 * Created: 24-Jan-23 9:41:39 PM
 *  Author: Peter Ghali
 */ 


#ifndef GEI_H_
#define GEI_H_
//An Enum that holds the Errors 
typedef enum
{
	GEI_enuOK = 0,
	GEI_enuNotOK,
	GEI_enuInavalidINT_Number,
	GEI_enuInavalidINT_Type,
	GEI_enuInavalidParametrs,
	GEI_enuInavalidMode,
}GEI_tenuErrorStatus;

/*
GEI Enable Function :
A function that sets the I bit for the global interrupt and the GEI as configured
Input	: void
return	: GEI_tenuErrorStatus to report error
*/
GEI_tenuErrorStatus GEI_enuEnable(void);
/*
GEI Disable Function :
A function that Disable the I bit for the global interrupt
Input	: void
return	: GEI_tenuErrorStatus to report error
*/
GEI_tenuErrorStatus GEI_enuDisable(void);


#endif /* GEI_H_ */