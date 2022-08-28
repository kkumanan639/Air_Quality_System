#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include "MCP23017_driver.h"


void I2C0_MCP23017_init(void){
	//configure PA2 (SDA)  PA3 (SCl) as inputs
	PORTA.DIR = 0x00;
	
	//Master Baud rate set to 0
	TWI0.MBAUD = 0;
	
	//Enable the TWI master
	TWI0.MCTRLA = TWI_ENABLE_bm;
	
	//Forcing Bus state to Idle
	TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
}


void MCP23017_I2C_write(uint8_t opcode, uint8_t slave_register, uint8_t data){
	
	//Master starts performing a bus transaction
	//when then the master address register is written
	TWI0.MADDR = opcode;
	
	//wait for data packet to be transmitted
	while(!(TWI0.MSTATUS & TWI_WIF_bm));
	
	TWI0.MDATA = slave_register;
	
	//wait for data packet to be transmitted
	while(!(TWI0.MSTATUS & TWI_WIF_bm));
	
	TWI0.MDATA = data;
	
	//wait for data packet to be transmitted
	while(!(TWI0.MSTATUS & TWI_WIF_bm));
	
	//complete transaction by issuing a stop condition
	TWI0.MCTRLB = TWI_MCMD_gm;
	
}

void  MCP23017_I2C0_init(void){
	//split into two 8 bit general purpose IO pins
	MCP23017_I2C_write(WRITE_opcode, IOCONaddr_b0, 0x80);
	//Set GPA as outputs
	MCP23017_I2C_write(WRITE_opcode, IODIRAaddr_b1, 0x00);
	//Set GPB as outputs
	MCP23017_I2C_write(WRITE_opcode, IODIRBaddr_b1, 0x00);
	//Enable internal pullup resistors on all the GPA pins
	//MCP23017_I2C_write(WRITE_opcode, GPPUAaddr_b1, 0xFF);
}


