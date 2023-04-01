/*
 * RTOS_Congi.h
 *
 * Created: 16-Mar-23 2:30:24 PM
 *  Author: Peter Ghali
 */ 


#ifndef RTOS_CONGI_H_
#define RTOS_CONGI_H_
#include "../../00-LIB/STD_TYPES.h"

typedef void(*pfun)(void);


typedef struct {

	u16 Periodicity;

	u8 Priority;
	/* pointer to function */
	pfun Task ;
}Task_t;

typedef enum {
	
	LED1_Task,
	LED2_Task,
	//LED3_Task,
	Number_Of_Tasks ,
}Tasks_Name_t ;

extern const Task_t OS_strTaskCfg [Number_Of_Tasks] ; 


#endif /* RTOS_CONGI_H_ */