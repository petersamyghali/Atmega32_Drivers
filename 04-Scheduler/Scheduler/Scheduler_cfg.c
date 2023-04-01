/*
* RTOS_Config.c
*
* Created: 16-Mar-23 2:30:38 PM
*  Author: Peter Ghali
*/
#include "Scheduler_cfg.h"
#include "Scheduler.h"
extern void LED0_F (void);
extern void LED1_F (void);
extern void LED2_F (void);

const Task_t OS_strTaskCfg [Number_Of_Tasks] =
{
	[LED1_Task] =
	{
		.Task = LED0_F ,
		.Priority = 0,
		.Periodicity = 1000 ,
	},
	
	[LED2_Task] =
	{
		.Task = LED1_F ,
		.Priority = 0,
		.Periodicity = 2000 ,
	},
	
	/*[LED3_Task] =
	{
	.Task = LED2_F ,
	.Priority = 0,
	.Periodicity = 3000 ,
	}*/
};