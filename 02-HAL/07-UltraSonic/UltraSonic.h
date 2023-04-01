/*
* UltraSonic.h
*
* Created: 10-Mar-23 4:31:19 PM
*  Author: Peter Ghali
*/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define Trigger_PIN   DIO_enuPORTA_Pin0

typedef void (*UltraSonic_CBF)(void);

typedef enum
{
	UltraSonic_Ok,
	UltraSonic_Not_Ok ,
	UltraSonic_Null_PTR ,
}UltraSonic_ErrorStatus_t;

void UltraSonic_enuInit(void);

void UltraSonic_Trigger(void);

u32 UltraSonic_GetReading(void);
#endif /* ULTRASONIC_H_ */