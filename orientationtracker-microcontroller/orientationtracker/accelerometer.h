/*
 * accelerometer.h
 *
 * Created: 7-4-2022 08:55:40
 *  Author: Julia Aalbers
 */ 

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <avr/io.h>
#include "twi.h"

#define F_CPU 16000000UL
#define SCL_CLOCK 400000L

#define ADXL345_ID 0x53

// ADXL345 configuration register
#define ADXL345_REGISTER_BW_RATE 0x2C
#define ADXL345_REGISTER_POWER_CTL 0x2D
#define ADXL345_REGISTER_DATA_FORMAT 0x31

// ADXL345 data read registers
#define ADXL345_REGISTER_X0 0x32
#define ADXL345_REGISTER_X1 0x33
#define ADXL345_REGISTER_Y0 0x34
#define ADXL345_REGISTER_Y1 0x35
#define ADXL345_REGISTER_Z0 0x36
#define ADXL345_REGISTER_Z1 0x37

#define ADXL345_READ_X 0
#define ADXL345_READ_Y 1
#define ADXL345_READ_Z 2

void accelerometer_configure_register(unsigned int reg, char data);
uint8_t accelerometer_read(unsigned int reg, char* data);
float accelerometer_read_xyz(unsigned char type);
void accelerometer_process_data(char *process_data, float x, float y, float z);

void accelerometer_default_configuration();
void accelerometer_get_data(char *data);

#endif /* ACCELEROMETER_H_ */