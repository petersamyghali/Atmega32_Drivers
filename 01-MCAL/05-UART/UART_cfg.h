/*
 * UART_cfg.h
 *
 * Created: 21-Mar-23 10:27:52 PM
 *  Author: Peter Ghali
 */ 


#ifndef UART_CFG_H_
#define UART_CFG_H_
/*
A macro to define the numbe of data thant can be buffered 
*/


/*A macro to define the UART 
options :
UART_TRANSMITTER
UART_RECIVER
UART_TRANSMITTER_RECIVER
*/
#define UART_CFG				UART_TRANSMITTER_RECIVER

/*
A macro to define the frequency of the CPU*/
#define F_CPU					8000000UL

/*A macro to define the baud rate of the UART 
*/
#define UART_BAUD_RATE			9600
/*A macro to define the number of stop bits in the UART
options : 
UART_ONE_STOP_BIT
UART_TWO_STOP_BIT
*/
#define UART_STOP_BITS			UART_ONE_STOP_BIT

/*
A macro to define the if the user wants a parity bit or not 
options : 
UART_PARITY_BIT_EVEN
UART_PARITY_BIT_ODD
UART_PARITY_BIT_DISABLE
*/
#define UART_PARITY_BIT			UART_PARITY_BIT_DISABLE

/*
A macro to define the number of the data bits in the UART 
options : 
UART_FIVE_DATA_BITS
UART_SIX_DATA_BITS
UART_SEVEN_DATA_BITS
UART_EIGH_DATA_BITS
UART_NINE_DATA_BITS
*/
#define UART_DATA_BITS_NUMBER	UART_EIGH_DATA_BITS
/*A MACRO TO DEFINE THE Double speed option in th 
AVR
options : 
ENABLE 
DISABLE 
*/
#define UART_DOUBLE_SPEED_MODE	DISABLE


#endif /* UART_CFG_H_ */