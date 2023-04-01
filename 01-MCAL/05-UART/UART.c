/*
* UART.c
*
* Created: 21-Mar-23 10:27:26 PM
*  Author: Peter Ghali
*/
#include "Bit_Math.h"
#include "STD_TYPES.h"

#include "UART.h"
#include "UART_cfg.h"
#include "UART_prv.h"

#define RXC_CBF			0
#define TXC_CBF			1
#define UDRE_CBF		2

static volatile u8 *GLO_Recived_Data = NULL ;

static UART_CBF_t cbf_arr[3] = {NULL};
static volatile u8 DATA_Buffeered;
static volatile u8 TX_Busy_Flag = DISABLE ;
static volatile u8 RX_Busy_Flag = DISABLE ;





UART_enuError_Status_t UART_enu_Init(void)
{
	UART_enuError_Status_t Error_Status = UART_ok ;
	volatile u16 BAUD_PRESCALE = 0 ;
	volatile u8 Temp_Reg = 0;

	#if UART_CFG == UART_TRANSMITTER_RECIVER
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
	
	#elif UART_CFG == UART_RECIVER
	SET_BIT(UCSRB,UCSRB_RXEN);
	
	#elif UART_CFG == UART_TRANSMITTER
	SET_BIT(UCSRB,UCSRB_TXEN);
	
	#else
	Error_Status = UART_Invalid_Congirations ;
	#endif


	#if UART_STOP_BITS == UART_ONE_STOP_BIT
	CLR_BIT(UCSRC,UCSRC_USBS);
	
	#elif UART_STOP_BITS == UART_TWO_STOP_BIT
	SET_BIT(UCSRC,UCSRC_USBS);
	
	#else
	Error_Status = UART_Invalid_Congirations ;
	#endif


	#if UART_PARITY_BIT == UART_PARITY_BIT_DISABLE
	Temp_Reg = (UCSRC_Register_Select|UCSRC) ;
	Temp_Reg &= PARITY_BIT_CLEAR_MASK ;
	Temp_Reg |=UART_PARITY_BIT_DISABLE ;
	UCSRC = Temp_Reg;
	
	#elif UART_PARITY_BIT == UART_PARITY_BIT_EVEN
	Temp_Reg = (UCSRC_Register_Select|UCSRC) ;
	Temp_Reg &= PARITY_BIT_CLEAR_MASK ;
	Temp_Reg |=UART_PARITY_BIT_EVEN ;
	UCSRC = Temp_Reg;
	
	#elif UART_PARITY_BIT == UART_PARITY_BIT_ODD
	Temp_Reg = (UCSRC_Register_Select|UCSRC) ;
	Temp_Reg &= PARITY_BIT_CLEAR_MASK ;
	Temp_Reg |=UART_PARITY_BIT_ODD ;
	UCSRC = Temp_Reg;
	
	#else
	Error_Status = UART_Invalid_Congirations ;
	#endif


	#if UART_DATA_BITS_NUMBER == UART_FIVE_DATA_BITS
	Temp_Reg = (UCSRC_Register_Select|UCSRC) ;
	Temp_Reg &=DATA_BITS_CLEAR_MASK ;
	Temp_Reg |=UART_FIVE_DATA_BITS;
	UCSRC = Temp_Reg;
	
	#elif  UART_DATA_BITS_NUMBER ==  UART_SIX_DATA_BITS
	Temp_Reg = (UCSRC_Register_Select|UCSRC) ;
	Temp_Reg &=DATA_BITS_CLEAR_MASK ;
	Temp_Reg |=UART_SIX_DATA_BITS;
	UCSRC = Temp_Reg;
	
	#elif  UART_DATA_BITS_NUMBER ==  UART_SEVEN_DATA_BITS
	Temp_Reg = (UCSRC_Register_Select|UCSRC) ;
	Temp_Reg &=DATA_BITS_CLEAR_MASK ;
	Temp_Reg |=UART_SEVEN_DATA_BITS;
	UCSRC = Temp_Reg;

	#elif  UART_DATA_BITS_NUMBER ==  UART_EIGH_DATA_BITS
	Temp_Reg = (UCSRC_Register_Select|UCSRC) ;
	Temp_Reg &=DATA_BITS_CLEAR_MASK ;
	Temp_Reg |=UART_EIGH_DATA_BITS;
	UCSRC =Temp_Reg;


	#elif  UART_DATA_BITS_NUMBER ==  UART_NINE_DATA_BITS
	Temp_Reg = (UCSRC_Register_Select|UCSRC) ;
	Temp_Reg &=DATA_BITS_CLEAR_MASK ;
	Temp_Reg |=(UCSRC_Register_Select|UART_NINE_DATA_BITS);
	UCSRC = Temp_Reg;
	SET_BIT(UCSRB , UCSRB_UCSZ2);
	#else
	Error_Status = UART_Invalid_Congirations ;
	#endif

	#if UART_DOUBLE_SPEED_MODE == ENABLE
	SET_BIT(UCSRA ,UCSRA_U2X);
	BAUD_PRESCALE =(((F_CPU/(UART_BAUD_RATE * 8UL )))-1);
	UBRRL = BAUD_PRESCALE ;
	UBRRH = (BAUD_PRESCALE >> 8);
	
	#elif  UART_DOUBLE_SPEED_MODE == DISABLE
	CLR_BIT(UCSRA ,UCSRA_U2X);
	BAUD_PRESCALE =(((F_CPU/(UART_BAUD_RATE * 16UL )))-1);
	UBRRL = BAUD_PRESCALE ;
	UBRRH = (BAUD_PRESCALE >> 8);
	#else
	Error_Status = UART_Invalid_Congirations ;
	#endif
	return Error_Status ;
}



UART_enuError_Status_t UART_enuSendAsyncByte(u8 Cpy_Byte , UART_CBF_t Add_cbf)
{
	UART_enuError_Status_t Error_Status = UART_ok ;
	
	if (TX_Busy_Flag == DISABLE)
	{
		cbf_arr[UDRE_CBF] = Add_cbf ;
		DATA_Buffeered = Cpy_Byte ;
		TX_Busy_Flag = ENABLE ;
		SET_BIT(UCSRB,UCSRB_UDRIE);
	}
	else
	{
		Error_Status =  UART_Busy;
	}
	
	return Error_Status ;
}

UART_enuError_Status_t UART_enuSendSyncByte(u8 Cpy_Byte)
{
	UART_enuError_Status_t Error_Status = UART_ok ;
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR = Cpy_Byte;
	return Error_Status ;
}

void UART_SendString(char *str)
{
	u8 j=0;
	while (str[j]!='\0')		/* Send string till null */
	{
		UART_enuSendSyncByte(str[j]);
		j++;
	}
}


UART_enuError_Status_t UART_enuRecieveAsyncByte(u8 * Add_Byte , UART_CBF_t Add_cbf)
{
	UART_enuError_Status_t Error_Status = UART_ok ;
	if (Add_Byte == NULL)
	{
		Error_Status = UART_Null_PTR ;
	}
	else if (RX_Busy_Flag == DISABLE)
	{
		cbf_arr[RXC_CBF]= Add_cbf;
		GLO_Recived_Data = Add_Byte ;
		RX_Busy_Flag =ENABLE ;
		SET_BIT(UCSRB,UCSRB_RXCIE);
	}
	else
	{
		Error_Status =  UART_Busy;
	}
	return Error_Status ;
}



UART_enuError_Status_t UART_enuRecieveSyncByte(u8 * Add_Byte)
{
	UART_enuError_Status_t Error_Status = UART_ok ;
	while ((UCSRA & (1 << UCSRA_RXC)) == 0);/* Wait till data is received */
	* Add_Byte = UDR ; 		/* Return the byte */
	return Error_Status ;
}



UART_enuError_Status_t UART_enuRecieve_CBF(UART_CBF_t Add_cfb_Function)
{
	UART_enuError_Status_t Error_Status = UART_ok ;
	if (Add_cfb_Function)
	{
		cbf_arr[RXC_CBF] = Add_cfb_Function ;
	}
	else
	{
		Error_Status = UART_Null_PTR ;
	}

	return Error_Status ;
}



UART_enuError_Status_t UART_enuSend_CBF(UART_CBF_t Add_cfb_Function)
{
	UART_enuError_Status_t Error_Status = UART_ok ;
	if (Add_cfb_Function)
	{
		cbf_arr[TXC_CBF] = Add_cfb_Function ;
	}
	else
	{
		Error_Status = UART_Null_PTR ;
	}
	return Error_Status ;
}


void UART_Receive_String(u8 *str)
{
	u8 i=0;
	
	UART_enuRecieveSyncByte(&str[i]);
	while (str[i]!='#')
	{
		i++;
		UART_enuRecieveSyncByte(&str[i]);
	}

}
UART_enuError_Status_t UART_enuData_Register_Empty_CBF(UART_CBF_t Add_cfb_Function)
{
	UART_enuError_Status_t Error_Status = UART_ok ;

	return Error_Status ;
}

INTERRUPT_SERVICE_ROUTINE_(13)
{
	if (RX_Busy_Flag == ENABLE)
	{
		SET_BIT(UCSRA,UCSRB_RXCIE);
		*GLO_Recived_Data = UDR ;
		RX_Busy_Flag =DISABLE ;
	}
	if(cbf_arr[RXC_CBF])
	{
		cbf_arr[RXC_CBF]();
	}
	else
	{
		
	}
			CLR_BIT(UCSRB,UCSRB_RXCIE);
}

INTERRUPT_SERVICE_ROUTINE_(14)
{
	if (TX_Busy_Flag == ENABLE )
	{
		UDR = DATA_Buffeered;
		DATA_Buffeered = 0 ;
		TX_Busy_Flag = DISABLE ;
	}
	if(cbf_arr[UDRE_CBF])
	{
		
		cbf_arr[UDRE_CBF]();
	}
	CLR_BIT(UCSRB,UCSRB_UDRIE);
	
}

INTERRUPT_SERVICE_ROUTINE_(15)
{
	if(cbf_arr[TXC_CBF])
	{
		
		cbf_arr[TXC_CBF]();
	}
}