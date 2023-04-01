/*
* UART.h
*
* Created: 21-Mar-23 10:27:46 PM
*  Author: Peter Ghali
*/


#ifndef UART_H_
#define UART_H_

#define TIME_OUT_TRIALS		10

typedef void (*UART_CBF_t)(void) ; 

typedef enum
{
	UART_ok ,
	UART_Not_ok ,
	UART_Null_PTR,
	UART_Invalid_Parameters ,
	UART_Invalid_Congirations,
	UART_Time_Out,
	UART_Busy , 
	UART_Buffer_Full , 
}UART_enuError_Status_t;

UART_enuError_Status_t UART_enu_Init(void);

UART_enuError_Status_t UART_enuSendAsyncByte(u8 const Cpy_Byte , UART_CBF_t Add_cbf);

UART_enuError_Status_t UART_enuSendSyncByte(u8 volatile const Cpy_Byte);

void UART_SendString(char *str);
void UART_Receive_String(u8 *str);

UART_enuError_Status_t UART_enuRecieveAsyncByte(u8 * Add_Byte , UART_CBF_t Add_cbf);

UART_enuError_Status_t UART_enuRecieveSyncByte(u8 * Add_Byte);

UART_enuError_Status_t UART_enuRecieve_CBF(UART_CBF_t Add_cfb_Function);

UART_enuError_Status_t UART_enuSend_CBF(UART_CBF_t Add_cfb_Function);

UART_enuError_Status_t UART_enuData_Register_Empty_CBF(UART_CBF_t Add_cfb_Function);




#endif /* UART_H_ */