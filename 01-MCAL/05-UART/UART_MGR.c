/*
* UART_MGR.c
*
* Created: 23-Mar-23 7:55:25 PM
*  Author: Peter Ghali
*/

#include "STD_TYPES.h"
#include "Bit_Math.h"

#include "UART_MGR.h"
#include "UART.h"
#include "UART_prv.h"


void func (void);

u8 RecivedAsynByte[Queue_MAX_size][Queue_MAX_size] = {0};

/*An array to have the jobs to be executed with the length of a macro given in the header file */
UART_MGR_JobRequest UARTM_Queue[Queue_MAX_size];
/*A counter to indicate the current job */
static u8 UARTM_QCurrent = 0;
/*A counter to indicate the next job*/
static u8 UARTM_QNext = 0;
/*A counter to know how many available  jobs */
static u8 UARTM_QAvaiblable = Queue_MAX_size;
/*A flag to indicate if their is a job is being executed*/
static u8 UARTM_BusyFlag = 0;
/*A counter to indicate the Async jobs */
static u8 UARTM_AsynCounter = 0;
/*******************************************	STATIC FUNCTIONS PROTOTYPES******************/
static void voidSendSynch (void);
static void voidReciveSynch(void);
static void voidStart(void) ;
static void voidSendAsync(void) ;
static void AsynCallbackSend (void);
static void voidReciveAsync(void) ;
static void AsynCallbackRecive (void) ;

UART_enuError_Status_t URTM_u8PerformJobRequest (UART_MGR_JobRequest *CopyJobInfo)
{
	UART_enuError_Status_t Error_Status = UART_ok;
	/*if their is an available  spot */
	if (UARTM_QAvaiblable > 0)
	{
		/*decrement the number of available spots by one */
		UARTM_QAvaiblable--;
		/*copy the data of the passed struct to the current available spot in the queue */
		UARTM_Queue[UARTM_QNext].Length  = CopyJobInfo->Length;
		UARTM_Queue[UARTM_QNext].CBF = CopyJobInfo->CBF;
		UARTM_Queue[UARTM_QNext].Data = CopyJobInfo->Data;
		UARTM_Queue[UARTM_QNext].JobType = CopyJobInfo->JobType;
		/*increment the next available place [index] by one */
		UARTM_QNext++;
		/*if the available spaces equals the max size of the array then over write the first job*/
		if (UARTM_QNext == Queue_MAX_size)
		{
			UARTM_QNext = 0;
			Error_Status = UART_Buffer_Full ;
		}
	}
	else
	{
		Error_Status = UART_Buffer_Full;
	}
	return Error_Status ;
}
/*A function to be called by the user in order to loop over the jobs and execute them all */
void URTM_voidExcuteJobs(void)
{
	if (UARTM_BusyFlag == DISABLE)
	{
		voidStart();
	}
	
	else
	{
		
	}
}

void voidStart(void)
{
	/*A flag to indicate if their is an Async job */
	u8 AsyncFlag = 0;
	while(1)
	{
		/*if queue Is empty */
		if (UARTM_QAvaiblable == Queue_MAX_size)
		{
			UARTM_BusyFlag = DISABLE;
			break;
		}
		/*if their is any job in the Q*/
		else
		{
			
			UARTM_BusyFlag = ENABLE;
			/*switch in order to know what jobs shall be executed */
			switch (UARTM_Queue[UARTM_QCurrent].JobType)
			{
				case(UART_Async_Send):
				voidSendAsync();
				AsyncFlag = ENABLE;
				break;
				
				case(UART_Sync_Send):
				voidSendSynch();
				break;
				
				case(UART_Async_Receieve):
				voidReciveAsync();
				AsyncFlag = ENABLE;
				break;
				
				case(UART_Sync_Receieve):
				voidReciveSynch();
				break;
				
			}
			/*if the Async flag is enabled then terminate from the while 1 */
			if(AsyncFlag == 1)
			{
				break;
			}
			else
			{
				/*Do Nothing*/
			}
		}
	}
}

static void voidSendSynch (void)
{
	/*in order to send the given bytes synchronous we need to halt the system in order to send them all byte by byte */
	u8 Index;
	for (Index = 0; Index <UARTM_Queue[UARTM_QCurrent].Length;Index++)
	{
		/*keep sending the bytes*/
		UART_enuSendSyncByte(UARTM_Queue[UARTM_QCurrent].Data[Index]);
	}
	/*After sending the bytes the job has been executed then increment the size of the available jobs by one */
	UARTM_QAvaiblable++;
	if (UARTM_QAvaiblable > Queue_MAX_size)
	{
		UARTM_QAvaiblable = Queue_MAX_size ; 
	}
	else 
	{
		
	}
	/*the current job to be executed is the next job the Q */
	UARTM_QCurrent++;
	/*if the next job is to be done is the last one */
	if (UARTM_QCurrent == Queue_MAX_size)
	{
		/*reInitialize the counter to indicate the first job */
		UARTM_QCurrent = 0;
	}
	else
	{
		/*Do Nothing*/
	}
}



static void voidReciveSynch(void)
{
	u8 Index;
	/*in order to send the given bytes synchronous we need to halt the system in order to receive them all byte by byte */
	for (Index = 0; Index <UARTM_Queue[UARTM_QCurrent].Length;Index++)
	{
		/*keep receiving the bytes*/
		UART_enuRecieveSyncByte(&(UARTM_Queue[UARTM_QCurrent].Data[Index])) ; 
	}
	/*After sending the bytes the available  places will be incremented by one */
	UARTM_QAvaiblable++;
	if (UARTM_QAvaiblable > Queue_MAX_size)
	{
		UARTM_QAvaiblable = Queue_MAX_size ;
	}
	else
	{
		
	}
	/*the current job to be executed is the next job the Q */
	UARTM_QCurrent++;
	/*if the next job is to be done is the last one */
	if (UARTM_QCurrent == Queue_MAX_size)
	{
		/*reInitialize the counter to indicate the first job */
		UARTM_QCurrent = 0;
	}
	else
	{
		/*Do Nothing*/
	}
}
/*if the job was to send the data Async*/
void voidSendAsync(void)
{
	/*The Async counter will be zero to indicate the first byte of the transmitted data */
	UARTM_AsynCounter = 0;
	/*using the Async function to send the the data in the UARTM_AsynCounter  in the job to be done using the UARTM_QCurrent */
	/*After the one byte is sent the AsynCallbackSend will be executed */
	UART_enuSendAsyncByte(UARTM_Queue[UARTM_QCurrent].Data[UARTM_AsynCounter],AsynCallbackSend);
	/*A one byte will be sent therefore the UARTM_AsynCounter will be incremented by one */
	UARTM_AsynCounter++;
}

void AsynCallbackSend (void)
{
	/*if the UARTM_AsynCounter is less than the length of the data to be sent the */
	if (UARTM_AsynCounter < UARTM_Queue[UARTM_QCurrent].Length)
	{
		/*keeps buffering the data in the Async function*/
		UART_enuSendAsyncByte(UARTM_Queue[UARTM_QCurrent].Data[UARTM_AsynCounter],AsynCallbackSend);
		/*increment it by one in order to move all the data to the buffer in the Async send function*/
		UARTM_AsynCounter++;
	}
	else
	{
		/*if all the data have been buffered the cbf of the current job shall be executed */
		UARTM_Queue[UARTM_QCurrent].CBF();
		/*increment the number of the available jobs by one */
		UARTM_QAvaiblable++;
		if (UARTM_QAvaiblable > Queue_MAX_size)
		{
			UARTM_QAvaiblable = Queue_MAX_size ;
		}
		else
		{
			
		}
		/*Do the next job*/
		UARTM_QCurrent++;
		/*if the next job to be done is more than the buffer it self rewrite the jobs */
		if (UARTM_QCurrent == Queue_MAX_size)
		{
			UARTM_QCurrent = 0;
		}
		else
		{
			/*Do Nothing*/
		}
	}
}

/*if the job was to receive the byte Async */
void voidReciveAsync(void)
{
	/*The Async counter will be zero to indicate the first byte of the Received data */
	UARTM_AsynCounter = 0;
	UART_enuRecieveAsyncByte(&RecivedAsynByte[UARTM_QCurrent] [UARTM_AsynCounter], AsynCallbackRecive);
	UARTM_AsynCounter++;
}

void AsynCallbackRecive (void)
{
	if (UARTM_AsynCounter < UARTM_Queue[UARTM_QCurrent].Length)
	{
		//UARTM_Queue[UARTM_QCurrent].Data[UARTM_AsynCounter-1] = RecivedAsynByte[UARTM_AsynCounter]; /*RecivedAsynByte: Global Variable from ISR*/
		/*receive the byte in this double array */
		UART_enuRecieveAsyncByte(&RecivedAsynByte[UARTM_QCurrent][UARTM_AsynCounter],AsynCallbackRecive);
		/*Add the Async counter by 1 in order to know the next byte*/
		UARTM_AsynCounter++;
	}
	else
	{
		/*in order to receive the last byte */
		UART_enuRecieveAsyncByte(&RecivedAsynByte[UARTM_QCurrent][UARTM_AsynCounter],AsynCallbackRecive); /*RecivedAsynByte: Global Variable from ISR*/
		/*if all the bytes had been received then call the function of this job*/
		UARTM_Queue[UARTM_QCurrent].CBF();
		/*Add the number of the available jobs by one */
		UARTM_QAvaiblable++;
		if (UARTM_QAvaiblable > Queue_MAX_size)
		{
			UARTM_QAvaiblable = Queue_MAX_size ;
		}
		else
		{
			
		}
		/*Excute the next job */
		UARTM_QCurrent++;
		if (UARTM_QCurrent == Queue_MAX_size)
		{
			UARTM_QCurrent = 0;
		}
		else
		{
			/*Do Nothing*/
		}
	}
}


