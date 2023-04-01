/*
 * UART_MGR.h
 *
 * Created: 23-Mar-23 7:55:16 PM
 *  Author: Peter Ghali
 */ 


#ifndef UART_MGR_H_
#define UART_MGR_H_

#define Queue_MAX_size		10

typedef void (*UART_CBF_t)(void) ;

typedef enum {
	UART_Async_Send = 0,
	UART_Sync_Send,
	UART_Async_Receieve,
	UART_Sync_Receieve
}JobType_t;

typedef struct {
	JobType_t JobType; /*send Async , send Sync , recieve Asyn , Receive Sync*/
	u8* Data;
	u8 Length ;
	UART_CBF_t CBF ; /*In case Async else null*/
}UART_MGR_JobRequest ;

u8 URTM_u8PerformJobRequest (UART_MGR_JobRequest *CopyJobInfo);
void URTM_voidExcuteJobs(void) ; 

#endif /* UART_MGR_H_ */