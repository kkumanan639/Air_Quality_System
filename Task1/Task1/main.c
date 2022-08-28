/***************************************************************************
;*
;* Title: "main.c" - SCD41 measurement main file
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;*
;* DESCRIPTION
;*
;*
;* VERSION HISTORY
;* 1.0 Original version
;**************************************************************************/


#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_DOG_avr128_driver.h"
#include "SCD41.h"
#include "USART3.h"
#include "MCP23017_driver.h"

void bargraph();
void USART_print();

int main(void)
{


	init_lcd_dog();
	UART_init(9600, 8, 'N');  /* Set the baudrate to 19,200 bps using a 3.6864MHz crystal */

	while (1)
	{
		I2C0_SCD40_init();
		
		SCD40_MEASUREMENT();
	
		conversion();
	
		sprintf(dsp_buff1, "CO2: %d ", result_final[0]);
		sprintf(dsp_buff2, "Temp: %d ", result_final[1]);
		sprintf(dsp_buff3, "Hum: %d ", result_final[2]);
		
		update_lcd_dog();
		
		bargraph();
		

		
		
		USART_print();
		
	}
}

void bargraph(){
	I2C0_MCP23017_init();
	MCP23017_I2C0_init();
		
	if(result_final[0] >= 400 && result_final[0] < 500 ){
		MCP23017_I2C_write(WRITE_opcode, OLATBaddr_b1, 0x7F);
	}
	else if(result_final[0] >= 500 && result_final[0] < 600){
		MCP23017_I2C_write(WRITE_opcode, OLATBaddr_b1, 0x3F);
	}
	else if(result_final[0] >= 600 && result_final[0] < 700){
		MCP23017_I2C_write(WRITE_opcode, OLATBaddr_b1, 0x1F);
	}
	else if(result_final[0] >= 700 && result_final[0] < 800){
		MCP23017_I2C_write(WRITE_opcode, OLATBaddr_b1, 0x0F);
	}
	else if(result_final[0] >= 800 && result_final[0] < 900){
		MCP23017_I2C_write(WRITE_opcode, OLATBaddr_b1, 0x07);
	}
	else if(result_final[0] >= 900 && result_final[0] < 1000){
		MCP23017_I2C_write(WRITE_opcode, OLATBaddr_b1, 0x03);
	}
	else if(result_final[0] >= 1000 && result_final[0] < 1100){
		MCP23017_I2C_write(WRITE_opcode, OLATBaddr_b1, 0x03);
	}
	else if(result_final[0] >= 1100 && result_final[0] < 1200){
		MCP23017_I2C_write(WRITE_opcode, OLATBaddr_b1, 0x01);
	}
	else {
		MCP23017_I2C_write(WRITE_opcode, OLATBaddr_b1, 0x00);
	}
		
}


void USART_print(){
	_delay_ms(1000);
	//USART3 transmit
	for(int i = 0; i < 17; i++){
		 UART_SendChar(dsp_buff1[i]);
	
	}
	
		 UART_SendChar('\r');
		 UART_SendChar('\n');
	
	for(int i = 0; i < 17; i++){
		 UART_SendChar(dsp_buff2[i]);
	
	}
	
		 UART_SendChar('\r');
		 UART_SendChar('\n');
	
	for(int i = 0; i < 17; i++){
		 UART_SendChar(dsp_buff3[i]);
	
	}
	
		 UART_SendChar('\r');
		 UART_SendChar('\n');
	
}




