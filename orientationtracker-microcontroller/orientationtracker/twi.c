/*
 * twi.c
 *
 * Created: 30-3-2022 20:30:43
 *  Author: Julia Aalbers
 */ 

#include "twi.h"

unsigned char twi_transmit(unsigned char type) 
{
	switch(type) {
		case I2C_START:    // start condition
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
		break;
		case I2C_DATA:     // send data with no-acknowledge
		TWCR = (1 << TWINT) | (1 << TWEN);
		break;
		case I2C_DATA_ACK: // send data with acknowledge
		TWCR = (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
		break;
		case I2C_STOP:     // stop condition
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
		return 0;
	}
	// wait for TWINT flag set on TWCR register
	while (!(TWCR & (1 << TWINT)));
	// return status
	return (TWSR & 0xF8);
}

unsigned char twi_start(unsigned int dev_id, unsigned int dev_addr, unsigned int method)
{
	// transmit start condition
	twi_transmit(I2C_START);
		
	uint8_t twst = TW_STATUS & 0xF8;
	if ((twst != TW_START) && (twst != TW_REP_START)) return 1;
		
	// TWDR = (dev_id & 0xF0) | (dev_addr & 0x0E) | method;
	// send slave address 
	uint8_t reg = method;
	reg |= dev_id << 1;
	TWDR = (dev_id << 1) | method;
		
	twi_transmit(I2C_DATA);
	
	twst = TW_STATUS & 0xF8;
	if(twst != TW_MT_SLA_ACK && twst != TW_MR_SLA_ACK) return twst;
	
	return 0;
	
}

void twi_stop()
{
	twi_transmit(I2C_STOP);
}

unsigned char twi_write(char data)
{
	// send data to I2C bus
	TWDR = data;
	// transmit I2C data
	twi_transmit(I2C_DATA);
	
	// uint8_t twst = TW_STATUS & 0xF8;
	uint8_t twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return twst;
	
	return 0;
}

uint8_t twi_read(char *data, char ack_type)
{
	if(ack_type)
	{
		twi_transmit(I2C_DATA_ACK);
	} else {
		twi_transmit(I2C_DATA);
	}
	
	// get data
	*data = TWDR;

	return TWDR;
}

void twi_init()
{
	TWSR = 0x00;
	// TWBR = 0x30;
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
}