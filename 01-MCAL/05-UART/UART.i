# 0 "UART.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "UART.c"
# 10 "UART.c"
# 1 "UART.h" 1
# 13 "UART.h"
typedef void (*UART_CBF_t)(void) ;

typedef enum
{
 UART_ok ,
 UART_Not_ok ,
 UART_Null_PTR,
 UART_Invalid_Parameters ,
 UART_Invalid_Congirations,

}UART_enuError_Status_t;

UART_enuError_Status_t UART_enu_Init(void);

UART_enuError_Status_t UART_enuSendAsyncByte(u8 Cpy_Byte);

UART_enuError_Status_t UART_enuSendSyncByte(u8 Cpy_Byte);

UART_enuError_Status_t UART_enuRecieveAsyncByte(u8 * Add_Byte);

UART_enuError_Status_t UART_enuRecieveSyncByte(u8 * Add_Byte);

UART_enuError_Status_t UART_enuRecieve_CBF(UART_CBF_t Add_cfb_Function);

UART_enuError_Status_t UART_enuSend_CBF(UART_CBF_t Add_cfb_Function);

UART_enuError_Status_t UART_enuData_Register_Empty_CBF(UART_CBF_t Add_cfb_Function);
# 11 "UART.c" 2
# 1 "UART_cfg.h" 1
# 12 "UART.c" 2
# 1 "UART_prv.h" 1
# 13 "UART.c" 2



UART_enuError_Status_t UART_enu_Init(void)
{
 UART_enuError_Status_t Error_Status = UART_ok ;

 volatile u8 Temp_Reg = 0;
 volatile u32 UBRR = 0 ;

 SET_BIT(*((volatile u8*)0x2A),4);
 SET_BIT(*((volatile u8*)0x2A),3);
# 38 "UART.c"
 CLR_BIT(*((volatile u8*)0x40),3);
# 49 "UART.c"
 Temp_Reg = (0b10000000|*((volatile u8*)0x40)) ;
 Temp_Reg &= 0b11001111 ;
 Temp_Reg |=0b00000000 ;
 *((volatile u8*)0x40) = (0b10000000|Temp_Reg);
# 90 "UART.c"
 Temp_Reg = (0b10000000|*((volatile u8*)0x40)) ;
 Temp_Reg &=0b11111001 ;
 Temp_Reg |=0b00000110;
 *((volatile u8*)0x40) = Temp_Reg;
# 106 "UART.c"
 SET_BIT(*((volatile u8*)0x2B) ,1);
 UBRR = (u32)((u32)(8000000UL/(u32)(8*9600))-1);
 if (UBRR < 255)
 {
  *((volatile u8*)0x29) = UBRR ;
 }
 else
 {
  *((volatile u8*)0x29) = (u8)UBRR ;
  *((volatile u8*)0x40) = (0b00000000|(UBRR >> 8 ));
 }
# 133 "UART.c"
 return Error_Status ;
}



UART_enuError_Status_t UART_enuSendAsyncByte(u8 Cpy_Byte)
{
 UART_enuError_Status_t Error_Status = UART_ok ;

 return Error_Status ;
}

UART_enuError_Status_t UART_enuSendSyncByte(u8 Cpy_Byte)
{
 UART_enuError_Status_t Error_Status = UART_ok ;

 return Error_Status ;
}



UART_enuError_Status_t UART_enuRecieveAsyncByte(u8 * Add_Byte)
{
 UART_enuError_Status_t Error_Status = UART_ok ;

 return Error_Status ;
}



UART_enuError_Status_t UART_enuRecieveSyncByte(u8 * Add_Byte)
{
 UART_enuError_Status_t Error_Status = UART_ok ;

 return Error_Status ;
}



UART_enuError_Status_t UART_enuRecieve_CBF(UART_CBF_t Add_cfb_Function)
{
 UART_enuError_Status_t Error_Status = UART_ok ;

 return Error_Status ;
}



UART_enuError_Status_t UART_enuSend_CBF(UART_CBF_t Add_cfb_Function)
{
 UART_enuError_Status_t Error_Status = UART_ok ;

 return Error_Status ;
}



UART_enuError_Status_t UART_enuData_Register_Empty_CBF(UART_CBF_t Add_cfb_Function)
{
 UART_enuError_Status_t Error_Status = UART_ok ;

 return Error_Status ;
}

INTERRUPT_SERVICE_ROUTINE_(13)
{

}

INTERRUPT_SERVICE_ROUTINE_(14)
{

}

INTERRUPT_SERVICE_ROUTINE_(15)
{

}
