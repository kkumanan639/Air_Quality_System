#include <avr/io.h>
#include <stdio.h>
#include "LCD_DOG_avr128_driver.h"


///////////////////////// Driver Functions //////////////////////////

void lcd_spi_transmit_CMD (unsigned char cmd) {
	volatile uint8_t read;
	//RS = 0 for command
	PORTC.OUT = 0x00;
	
	//select CS_bar
	PORTA.OUT &= ~(1 << 7);
	
	//start transmission of data
	SPI0.DATA = cmd;
	
	/*wait for transmission to be complete*/
	while(!(SPI0.INTFLAGS & SPI_IF_bm)){};

	//deselect CS_bar
	PORTA.OUT |= (1 << 7);
	
	//clear IF flag
	SPI0.INTFLAGS = SPI_IF_bm;
	read = SPI0.DATA;
}

void lcd_spi_transmit_DATA (unsigned char cmd) {
	volatile uint8_t read;
	//RS = 1 for data
	PORTC.OUT = (1 << 0);
	
	//select CS_bar
	PORTA.OUT &= ~(1 << 7);
	
	//start transmission of data
	SPI0.DATA = cmd;
	
	/*wait for transmission to be complete*/
	while(!(SPI0.INTFLAGS & SPI_IF_bm)){};

	//deselect CS_bar
	PORTA.OUT |= (1 << 7);
	
	//clear IF flag
	SPI0.INTFLAGS = SPI_IF_bm;
	read = SPI0.DATA;
}

void init_spi_lcd (void) {
	/*configure the location of the SPI pins*/
	
	//PA4 SPI0 MOSI configured as an output
	//PA5 SPIO MISO configured as an input
	//PA6 SCK configured as an output
	//PA7 set as slave select
	PORTA.DIR = (1 << 4)|(1 << 6)|(1<<7);
	

	//PA7 SS_bar set to idle at logic 1
	PORTA.OUT = (1 << 7);
	
	
	/*select SPI master by writing to master/slave bit
	in CTRLA, clock speed by writing to PRESC and CLK2X 
	bit and the order of transmission of the data with 
	the DORD bit*/
	SPI0.CTRLA =  SPI_MASTER_bm | SPI_CLK2X_bm;
	
	/*SPI mode 3 for the DOG LCD*/
	/*SPI MODE 0 and slave select on master disabled*/
	SPI0.CTRLB = SPI_SSD_bm | 0x03 ;
	
	/*Enable SPI*/
	SPI0.CTRLA |= SPI_ENABLE_bm;
	
	/*PC0 for RS of LCD*/
	PORTC.DIR = (1 << 0);
	PORTC.OUT = 0x00;		//RS = 0 for command
	
}


void init_lcd_dog (void) {

init_spi_lcd();		//Initialize mcu for LCD SPI

//start_dly_40ms:
delay_40mS();    //startup delay.


//func_set1:
lcd_spi_transmit_CMD(0x39);   // sedn function set #1
delay_30uS();	//delay for command to be processed


//func_set2:
lcd_spi_transmit_CMD(0x39);	//send fuction set #2
delay_30uS();	//delay for command to be processed


//bias_set:
lcd_spi_transmit_CMD(0x1E);	//set bias value.
delay_30uS();	//delay for command to be processed


//power_ctrl:
lcd_spi_transmit_CMD(0x55);	//~ 0x50 nominal for 5V
//~ 0x55 for 3.3V (delicate adjustment).
delay_30uS();	//delay for command to be processed


//follower_ctrl:
lcd_spi_transmit_CMD(0x6C);	//follower mode on...
delay_40mS();	//delay for command to be processed


//contrast_set:
lcd_spi_transmit_CMD(0x7F);	//~ 77 for 5V, ~ 7F for 3.3V
delay_30uS();	//delay for command to be processed


//display_on:
lcd_spi_transmit_CMD(0x0c);	//display on, cursor off, blink off
delay_30uS();	//delay for command to be processed


//clr_display:
lcd_spi_transmit_CMD(0x01);	//clear display, cursor home
delay_30uS();	//delay for command to be processed


//entry_mode:
lcd_spi_transmit_CMD(0x06);	//clear display, cursor home
delay_30uS();	//delay for command to be processed
}


void delay_40mS(void) {
int i;
for (int n = 40; n > 0; n--)
for (i = 0; i < 800; i++)
__asm("nop");
}

void delay_30uS(void) {
int i;
for (int n = 1; n > 0; n--)
for (i = 0; i < 2; i++)
__asm("nop");
}


// Updates the LCD display lines 1, 2, and 3, using the
// contents of dsp_buff_1, dsp_buff_2, and dsp_buff_3, respectively.
void update_lcd_dog(void) {

init_spi_lcd();		//init SPI port for LCD.

// send line 1 to the LCD module.
lcd_spi_transmit_CMD(0x80);	//init DDRAM addr-ctr
delay_30uS();
for (int i = 0; i < 16; i++) {
lcd_spi_transmit_DATA(dsp_buff1[i]);
delay_30uS();
}

// send line 2 to the LCD module.
lcd_spi_transmit_CMD(0x90);	//init DDRAM addr-ctr
delay_30uS();
for (int i = 0; i < 16; i++) {
lcd_spi_transmit_DATA(dsp_buff2[i]);
delay_30uS();
}

// send line 3 to the LCD module.
lcd_spi_transmit_CMD(0xA0);	//init DDRAM addr-ctr
delay_30uS();
for (int i = 0; i < 16; i++) {
lcd_spi_transmit_DATA(dsp_buff3[i]);
delay_30uS();
}
}


