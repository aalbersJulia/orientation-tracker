/*
 * i2c.h
 *
 * Created: 30-3-2022 12:13:26
 *  Author: Julia Aalbers
 */ 


#ifndef I2C_H_
#define I2C_H_

#define I2C_START 0
#define I2C_NACK 1
#define I2C_ACK 2
#define I2C_STOP 3

#define ACK 1
#define NACK 0

void set_registers(unsigned char type)
{
	switch(type){
		case I2C_START:
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
		break;
		case I2C_NACK:
		TWCR = (1 << TWINT) | (1 << TWEN);
		break;
		case I2C_ACK:
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		break;
		case I2C_STOP:
		TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
		return 0;
	}
	
	while(!(TWCR & (1 << TWINT)));
	
	return (TWSR & 0xF8);
}

void i2c_start(const uint8_t address, unsigned int rw)
{
	// start I2C communication
	set_registers(I2C_START);
	// select slave according to the address and select the method (read or write)
	TWDR = address | rw;
	set_registers(I2C_NACK);
}

void i2c_stop()
{
	set_registers(I2C_STOP);
}

void i2c_write(const uint8_t data)
{
	// sends the data to I2C bus
	TWDR = data;
	set_registers(I2C_NACK);
}

uint8_t i2c_read(char *data, const char ack_type)
{
	
	ack_type == 1 ? set_registers(I2C_ACK) : set_registers(I2C_NACK);
	
	*data = TWDR;
	
	return TWDR;
}

#endif /* I2C_H_ */