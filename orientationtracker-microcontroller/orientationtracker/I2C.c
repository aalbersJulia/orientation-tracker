/*
 * I2C.c
 *
 * Created: 29-3-2022 13:57:49
 *  Author: Julia Aalbers
 */ 

#define MAX_TRIES 50
#define I2C_START 0
#define I2C_DATA 1
#define I2C_DATA_ACK 2
#define I2C_STOP 3
#define ACK 1
#define NACK 0
#define DATASIZE 32

unsigned char I2C_transmit(unsigned char type) {
	switch(type){
		case I2C_START:
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
		break;
		case I2C_DATA:
		
	}
}

char I2C_start(unsigned int dev_id, unsigned int dev_addr, unsigned char rw_type)
{
	
}

