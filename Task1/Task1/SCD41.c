/***************************************************************************
;*
;* Title: "SCD41.c" - SCD41 measurement
;* Author: Keerthi Kumanan
;* Version: 1.0
;* Last updated: 04/14/2022
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* driver functions for the SCD41
;*
;* VERSION HISTORY
;* 1.0 Original version
;**************************************************************************/
#include "SCD41.h"



///////////////////////////driver functions/////////////////////////////////

void I2C0_SCD40_init(void){
	//configure PA2 (SDA)  PA3 (SCl) as inputs
	PORTA.DIR = 0x00;

	//Master Baud rate set to 15
	TWI0.MBAUD = 15;

	//Enable the TWI master
	TWI0.MCTRLA = TWI_ENABLE_bm;

	//Forcing Bus state to Idle
	TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
}




void SCD40_WRITE_COMMAND(uint16_t command){
	
	Command_address send_command;
	send_command.address = command;
	
	//Master starts performing a bus transaction
	//when then the master address register is written
	TWI0.MADDR = WRITE_OPCODE;

	//wait for data packet to be transmitted
	while(!(TWI0.MSTATUS & TWI_WIF_bm));

	TWI0.MDATA = send_command.address_msb;

	//wait for data packet to be transmitted
	while(!(TWI0.MSTATUS & TWI_WIF_bm));

	TWI0.MDATA = send_command.address_lsb;

	//wait for data packet to be transmitted
	while(!(TWI0.MSTATUS & TWI_WIF_bm));

	//complete transaction by issuing a stop condition
	TWI0.MCTRLB |= TWI_MCMD_STOP_gc;
	
}


uint8_t* SCD40_READ(uint16_t command, uint8_t data_size){
	_delay_ms(50);
	
	uint8_t* read_value;
	read_value = data;
	uint8_t i = 0;
	
	Command_address send_command;
	send_command.address = command;
	
	//Master starts performing a bus transaction
	//when then the master address register is written
	TWI0.MADDR = WRITE_OPCODE;
	
	

	//wait for data packet to be transmitted
	while(!(TWI0.MSTATUS & TWI_WIF_bm));

	TWI0.MDATA = send_command.address_msb;

	//wait for data packet to be transmitted
	while(!(TWI0.MSTATUS & TWI_WIF_bm));

	TWI0.MDATA = send_command.address_lsb;

	//wait for data packet to be transmitted
	while(!(TWI0.MSTATUS & TWI_WIF_bm));
	
	//delay for 1 ms
	_delay_ms(1);
	
	//Repeated Start
	//Master starts performing a bus transaction
	//when then the master address register is written
	TWI0.MADDR = READ_OPCODE;
	
	
	for(i = data_size - 1 ; i > 0 ; i++){
		
		//wait till byte is fully received from slave
		while(!(TWI0.MSTATUS & TWI_RIF_bm));
		
		//read received value
		read_value[i] = TWI0.MDATA;
		
		//ACK to read in new data packet
		TWI0.MCTRLB = TWI_MCMD_RECVTRANS_gc;
	}
	
	
	
	//wait till byte is fully received from slave
	while(!(TWI0.MSTATUS & TWI_RIF_bm));
	
	read_value[0] = TWI0.MDATA;
	
	
	//NACK and stop command
	TWI0.MCTRLB = TWI_MCMD_gm | TWI_ACKACT_bm;
	
	return read_value;
	
}



uint8_t POLL_READY_STATUS(void){
	uint8_t* ready_data;
	
	ready_data = SCD40_READ(get_data_ready_status, 3);
	
	if (!(ready_data[1] && ((ready_data[2]) & (0x07)))) {
		return 0;
	}
	else{
		return 1;
	}

}

void SCD40_MEASUREMENT(void){
	SCD40_WRITE_COMMAND(start_periodic_measurement);

	//while(POLL_READY_STATUS()){};
	
	SCD40_READ(get_data_ready_status, 3);
	
	//if (!(READY[0] == 0x00 && ((int) (READY[1]) & (PIN0_bm | PIN1_bm | PIN2_bm) == 0x00))){
	if(READY[0] == 0x06){
		SCD40_READ(read_measurement, 9);
	}
}


void conversion(){
	uint32_t intermediate;
	
	//CO2
	result temp;
	
	temp.high = DATA[0];
	temp.low = DATA[1];
	
	result_final[0] = temp.merge;
	
	//Temperature
	
	temp.high = DATA[3];
	temp.low = DATA[4];
	intermediate = temp.merge;
	
	intermediate = intermediate/ 16;
	intermediate  = 5 * intermediate;
	intermediate = intermediate/ 16;
	intermediate  = 5 * intermediate;
	intermediate = intermediate/ 16;
	intermediate  = 7 * intermediate;
	intermediate = intermediate/ 16;
	intermediate -= 45;
	
	result_final[1] = intermediate;
	
	//Relative humidity
	
	temp.high = DATA[7];
	temp.low = DATA[8];
	
	intermediate = temp.merge;
	
	intermediate = intermediate/ 16;
	intermediate *= 10;
	intermediate /= 16;
	intermediate *= 10;
	intermediate /= 16;
	intermediate /= 16;
	
	
	result_final[2] = intermediate;

}

