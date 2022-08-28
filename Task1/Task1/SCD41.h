#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_DOG_avr128_driver.h"

//Hex codes
#define WRITE_OPCODE 0xC4
#define READ_OPCODE 0XC5
#define get_data_ready_status 0xE4B8
#define start_periodic_measurement 0x21b1
#define read_measurement 0xEC05
#define stop_periodic_measurement 0x3F86



/***************************************************************************
;*
;* I2C0_MCP23017_init - title
;*
;* Description: Initializes the I2C module for the SCD41
;*
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;* Parameters: none
;*
;* Returns: none
;*
;*
;**************************************************************************/
void I2C0_SCD40_init(void);
/***************************************************************************
;*
;* SCD40_MEASUREMENT - title
;*
;* Description: starts measurement, checks if the data is ready and then 
;*				reads the data into an array
;*
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;* Parameters: none
;*
;* Returns: none
;*
;*
;**************************************************************************/
void SCD40_MEASUREMENT(void);
/***************************************************************************
;*
;* SCD40_WRITE_COMMAND - title
;*
;* Description: Writes command to the SCD41
;*
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;* Parameters: uint16_t command
;*
;* Returns: none
;*
;*
;**************************************************************************/
void SCD40_WRITE_COMMAND(uint16_t command);
/***************************************************************************
;*
;* SCD40_READ - title
;*
;* Description: reads from the SCD41
;*
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;* Parameters: uint16_t command, uint8_t data_size
;*
;* Returns: array with read data
;*
;*
;**************************************************************************/
uint8_t* SCD40_READ(uint16_t command, uint8_t data_size);
/***************************************************************************
;*
;* POLL_READY_STATUS - title
;*
;* Description: checks if the SCD41 is ready to be read for data
;*
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;* Parameters: none
;*
;* Returns: uint8_t (1 if ready and 0 if not ready)
;*
;*
;**************************************************************************/
uint8_t POLL_READY_STATUS(void);
/***************************************************************************
;*
;* conversion - title
;*
;* Description: converts results to values that can be displayed on the LCD
;*
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;* Parameters: none
;*
;* Returns: none
;*
;*
;**************************************************************************/
void conversion(void);

typedef union{
	uint16_t address;
	struct{
		uint8_t address_lsb;
		uint8_t address_msb;
		
	};
}Command_address;

typedef union{
	uint16_t merge;
	struct{
		uint8_t low;
		uint8_t high;
		
	};
}result;

//globals
uint8_t data[9];
uint16_t result_final[3];
uint8_t DATA[9];
uint8_t READY[3];
