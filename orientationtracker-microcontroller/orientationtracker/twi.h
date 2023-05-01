/*
 * twi.h
 *
 * Created: 30-3-2022 20:30:26
 *  Author: Julia Aalbers
 */ 

#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <compat/twi.h>

#define F_CPU 16000000UL
#define SCL_CLOCK 400000L

#define I2C_START 0
#define I2C_DATA 1
#define I2C_DATA_ACK 2
#define I2C_STOP 3
#define ACK 1
#define NACK 0
#define DATASIZE 32

#define TWI_WRITE 0
#define TWI_READ 1

unsigned char twi_transmit(unsigned char type);
unsigned char twi_start(unsigned int dev_id, unsigned int dev_addr, unsigned int method);
void twi_stop();
unsigned char twi_write(char data);
uint8_t twi_read(char *data, char ack_type);
void twi_init();



#endif /* TWI_H_ */