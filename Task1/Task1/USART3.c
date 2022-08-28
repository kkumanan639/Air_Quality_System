
#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART3.h"

#define F_PER 4000000


//////////////////////USART3 driver functions///////////////////////

/* Initialize USART */
void UART_init(uint16_t baud, uint8_t data, unsigned char parity){
	//setting the Baud rate
	USART3.BAUD = 1667;
	
	
	if(parity == 'E'){
		//Asynchronous mode, 0 - 8 bit data, no stop bit, 1 stop bit,  even parity
		USART3.CTRLC =  USART_CMODE_ASYNCHRONOUS_gc | (data - 5) | USART_PMODE_EVEN_gc  |USART_SBMODE_1BIT_gc;
	}
	else if(parity == 'O'){
		//Asynchronous mode, 0 - 8 bit data, no stop bit, 1 stop bit,  odd parity
		USART3.CTRLC =  USART_CMODE_ASYNCHRONOUS_gc | (data - 5) | USART_PMODE_ODD_gc  |USART_SBMODE_1BIT_gc;
	}
	else{
		//Asynchronous mode, 0 - 8 bit data, no stop bit, 1 stop bit,  no parity
		USART3.CTRLC =  USART_CMODE_ASYNCHRONOUS_gc | (data - 5) | USART_PMODE_DISABLED_gc  |USART_SBMODE_1BIT_gc;
	}
	
	//configuring the TXD pin as an output
	PORTB.DIR = PIN0_bm;
		
	//Normal mode and enable transmit
	USART3.CTRLB =  USART_RXMODE_NORMAL_gc |  USART_TXEN_bm;
	
}

void UART_SendChar(char c){
	while(!(USART3.STATUS & USART_DREIF_bm)){};
	USART3.TXDATAL = c;
}
