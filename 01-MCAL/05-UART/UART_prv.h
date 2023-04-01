/*
 * UART_prv.h
 *
 * Created: 21-Mar-23 10:28:01 PM
 *  Author: Peter Ghali
 */ 


#ifndef UART_PRV_H_
#define UART_PRV_H_

#define MAX_NUMBERS_IN_8_BITS	255

#define		UBRRH		*((volatile u8*)0x40)
#define		UCSRC		*((volatile  u8*)0x40)
#define		UCSRC_USBS	3

#define		UDR			*((volatile  u8*)0x2C)
#define		UCSRA		*((volatile u8*)0x2B)
#define		UCSRA_U2X	1
#define		UCSRA_UDRE	5
#define		UCSRA_RXC	7

#define		UCSRB		*((volatile  u8*)0x2A)
#define		UCSRB_UDRIE	5
#define		UCSRB_RXCIE	7
#define		UCSRB_TXCIE	6
#define		UCSRB_RXEN	4
#define		UCSRB_TXEN	3
#define		UCSRB_UCSZ2	2
#define		UBRRL		*((volatile  u8*)0x29)


#define		UART_ONE_STOP_BIT			1
#define		UART_TWO_STOP_BIT			2

#define		ENABLE						1
#define		DISABLE						0

#define		UCSRC_Register_Select		0b10000000
#define		UBRRH_Register_Select		0b00000000

#define		PARITY_BIT_CLEAR_MASK		0b11001111
#define		UART_PARITY_BIT_EVEN		0b00000010
#define		UART_PARITY_BIT_ODD			0b00000011
#define		UART_PARITY_BIT_DISABLE		0b00000000

#define		DATA_BITS_CLEAR_MASK		0b11111001
#define		UART_FIVE_DATA_BITS			0b00000000
#define		UART_SIX_DATA_BITS			0b00000010
#define		UART_SEVEN_DATA_BITS		0b00000100
#define		UART_EIGH_DATA_BITS			0b00000110
#define		UART_NINE_DATA_BITS			0b00000110

#define		UART_CFG_CLEAR				0b11100111
#define		UART_TRANSMITTER			0b00001000	
#define		UART_RECIVER				0b00010000
#define		UART_TRANSMITTER_RECIVER	0b00011000



	
#endif /* UART_PRV_H_ */