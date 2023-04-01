/*
 * RTOS.h
 *
 * Created: 16-Mar-23 2:29:49 PM
 *  Author: Peter Ghali
 */ 


#ifndef RTOS_H_
#define RTOS_H_


typedef enum
{
	OS_enuOK = 0,
	OS_enuNotOK,
	OS_enuNullPointer,
	OS_enuInavalidPortNum,
	OS_enuInavalidPinNum,
	OS_enuInavalidParametrs,
	OS_enuInavalidMode,
}OS_tenuErrorStatus;

void Scheduler_vidInit(void);

OS_tenuErrorStatus Scheduler_enuStart(void);
 


#endif /* RTOS_H_ */