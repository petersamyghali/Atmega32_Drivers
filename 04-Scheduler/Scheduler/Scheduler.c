/*
* RTOS.c
*
* Created: 16-Mar-23 2:29:58 PM
*  Author: Peter Ghali
*/

#include "../../00-LIB/STD_TYPES.h"
#include "../../00-LIB/BIT_MATH.h"

#include "../00-TIM0/TIM0.h"
#include "../01-GEI/GEI.h"

#include "Scheduler.h"
#include "Scheduler_cfg.h"
#include "Scheduler_Prv.h"
#define DISBALE 	0
#define ENABLE		1

u8 Sched_Flag = DISBALE ;
u8 CPU_LOAD_100 = DISBALE ;
void  Tick_CBF(void) ;


void Scheduler_vidInit(void)
{
	GEI_enuEnable();
	SET_BIT(TIMSK,TIMSK_OCIE0) ;
	SET_BIT(TIMSK,TIMSK_TOIE0) ;
	TIM0_enuInit();
	TIM0_enuStart();
	TIM0_enuRegisterCallback_CTC(Tick_CBF);
}



OS_tenuErrorStatus Scheduler_enuStart(void)
{
	OS_tenuErrorStatus Erro_Status = OS_enuOK ;
	while (1)
	{
		if (Sched_Flag == ENABLE)
		{
			Scheduler();
			Sched_Flag= DISBALE;
		}
	}

	return Erro_Status ;
	
}


static void Scheduler(void)
{

	u8 Task_Counter;
	static u16 Ticks_Counter = 0 ;

	for(Task_Counter = 0; Task_Counter < Number_Of_Tasks ; Task_Counter++)
	{
		if((Ticks_Counter % (OS_strTaskCfg[Task_Counter].Periodicity )) == 0)
		{

			if(OS_strTaskCfg[Task_Counter].Task != NULL)
			{
				OS_strTaskCfg[Task_Counter].Task();
			}
			
			
		}
		else
		{
			
		}
	}
	Ticks_Counter++;
}
void  Tick_CBF(void)
{
	if (Sched_Flag == DISBALE)
	{
		Sched_Flag = ENABLE ;
	}
	else
	{
		CPU_LOAD_100 = ENABLE ;
	}

}