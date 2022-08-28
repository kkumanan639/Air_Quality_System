/***************************************************************************
;*
;* "USART3.h" - USART3 function header
;*
;* Description: USART3 function header
;*
;* Author:			Keerthi Kumanan
;* Version:			0.1
;* Last updated:		101221
;* Target:			AVR128DB48
;*
***************************************************************************/



#include <avr/io.h>
#include <avr/interrupt.h>

#define F_PER 4000000


/***************************************************************************
;*
;* USART3_init - title
;*
;* Description: Initializes the USART3 module on the AVR128DB48
;*
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;* Parameters: uint16_t baud, uint8_t data, unsigned char parity
;*
;* Returns: none
;*
;*
;**************************************************************************/
void UART_init(uint16_t baud, uint8_t data, unsigned char parity);



/***************************************************************************
;*
;* USART3_transmit - title
;*
;* Description: transmits a byte of data using the USART protocol
;*
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;* Parameters: uint8_t data
;*
;* Returns: none
;*
;*
;**************************************************************************/
void UART_SendChar(char c);




