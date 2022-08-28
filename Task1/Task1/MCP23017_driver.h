/***************************************************************************
;*
;* Title: MCP23017.h
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* Tests the MCP23017_I2C0_init, MCP23017_I2C_write, and I2C0_MCP23017_init
;* functions
;*
;*
;* VERSION HISTORY
;* 1.0 Original version
;**************************************************************************/


#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>


#define IOCONaddr_b0	0x0A
#define IOCONaddr_b1	0x05
#define IODIRAaddr_b1	0x00
#define IODIRBaddr_b1	0x10
#define GPPUAaddr_b1	0x06
#define GPIOaddr_b1		0x09
#define OLATAaddr_b1	0x0A
#define OLATBaddr_b1	0x1A
#define WRITE_opcode	0x40
#define READ_opcode		0x41


/***************************************************************************
;*
;* I2C0_MCP23017_init - title
;*
;* Description: Initializes the I2C module for the MCP23017 IO expander
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
void I2C0_MCP23017_init(void);


/***************************************************************************
;*
;* MCP23017_I2C_write - title
;*
;* Description: transfer one byte of data to the MCP23017 using I2C protocol
;*
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;* Parameters: uint8_t opcode, uint8_t slave_register, uint8_t data
;*
;* Returns: none
;*
;*
;**************************************************************************/
extern void MCP23017_I2C_write(uint8_t opcode, uint8_t slave_register, uint8_t data);

/***************************************************************************
;*
;* MCP23017_I2C0_init - title
;*
;* Description: Initializes the ports on the MCP23017 IO expander for
;* reading in values from PORTA and output values to PORTB
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
void  MCP23017_I2C0_init(void);

