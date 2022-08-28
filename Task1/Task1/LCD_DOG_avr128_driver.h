/***************************************************************************
;*
;* " LCD_DOG_avr128_driver.h" - DOG LCD driver
;*
;* Description: DOG LCD driver
;*
;* Author:			Keerthi Kumanan
;* Version:			0.1
;* Last updated:		101221
;* Target:			AVR128DB48
;*
***************************************************************************/


/* modified p8_1.c:
*
* SPI0 is configured as SPI with hardware Slave Select.
* Clock rate is set to 2 MHz, half of the main clock.
* Polarity/Phase are 1, 1 to communicate with DOG LCD
*
* PA4  PAD0  MOSI
* PA6  PAD1  SCK
* PA7 PAD2  /SS       hardware controlled
* PA5  PAD3  MISO
*
* PC0  RS LCD	// Register select for LCD
*
* Tested with Atmel Studio 7
*/

#include <avr/io.h>
#include <stdio.h>

//junk
uint8_t read;

// Display buffer for DOG LCD using sprintf()
char dsp_buff1[17];
char dsp_buff2[17];
char dsp_buff3[17];



void lcd_spi_transmit_CMD (unsigned char cmd);


void lcd_spi_transmit_DATA (unsigned char cmd);


void init_spi_lcd (void);


void init_lcd_dog (void);


void delay_40mS(void);


void delay_30uS(void);


void update_lcd_dog(void);

