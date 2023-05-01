/*
 * accelerometer.c
 *
 * Created: 7-4-2022 08:55:55
 *  Author: Julia Aalbers
 */ 

#include "accelerometer.h"
#include <math.h>

#define PI 3.142857

void accelerometer_configure_register(unsigned int reg, char data)
{
	twi_start(ADXL345_ID, 0x00, TW_WRITE);
	twi_write(reg);
	twi_write(data);
	twi_stop();
}

// read value from the passed data register
uint8_t accelerometer_read(unsigned int reg, char* data)
{
	// read value from specified data register
	twi_start(ADXL345_ID, 0x00, TW_WRITE);
	twi_write(reg);
	
	twi_start(ADXL345_ID, 0x00, TW_READ);
	uint8_t raw = twi_read(&data, NACK);
	twi_stop();
			
	return raw;
}

float accelerometer_read_xyz(unsigned char type)
{
	
	uint8_t raw_0, raw_1 = 0;
	switch(type) {
		case ADXL345_READ_X:  
		raw_0 = accelerometer_read(ADXL345_REGISTER_X0, &raw_0);
		raw_1 = accelerometer_read(ADXL345_REGISTER_X1, &raw_1);
		break;
		case ADXL345_READ_Y:    
		raw_0 = accelerometer_read(ADXL345_REGISTER_Y0, &raw_0);
		raw_1 = accelerometer_read(ADXL345_REGISTER_Y1, &raw_1);
		break;
		case ADXL345_READ_Z: 
		raw_0 = accelerometer_read(ADXL345_REGISTER_Z0, &raw_0);
		raw_1 = accelerometer_read(ADXL345_REGISTER_Z1, &raw_1);
		break;
	}

	return (float)(raw_0 | raw_1 << 8) / 256;
}

void accelerometer_process_data(char *process_data, float x, float y, float z)
{
	char value_x[10], value_y[10], value_z[10], value_roll[10], value_pitch[10];
	
	float r = sqrt(x*x + y*y + z*z);
	float roll = 180 / PI * (PI/2 - acos(y/r));
	float pitch = 180 / PI * (PI/2 - acos(x/r));
	
	dtostrf(x, 1, 2, &value_x);
	dtostrf(y, 1, 2, &value_y);
	dtostrf(z, 1, 2, &value_z);
	
	dtostrf(roll, 1, 2, &value_roll);
	dtostrf(pitch, 1, 2, &value_pitch);
	
	// create JSON object to be parsed in C# example below
	/*
	{
		"x": -0.08,
		"y": -0.02,
		"z": 0.96,
		"roll": 95,
		"pitch": 4
	}
	*/
	snprintf(&process_data[0], 100, "{\"x\":%s, \"y\":%s, \"z\":%s, \"roll\":%s, \"pitch\":%s}\r", value_x, value_y, value_z, value_roll, value_pitch);
}

void accelerometer_default_configuration()
{
	accelerometer_configure_register(ADXL345_REGISTER_BW_RATE, 0x0A);
	accelerometer_configure_register(ADXL345_REGISTER_DATA_FORMAT, 0x08);
	accelerometer_configure_register(ADXL345_REGISTER_POWER_CTL, 0x08);
}

void accelerometer_get_data(char *data)
{
	float raw_x = accelerometer_read_xyz(ADXL345_READ_X);
	float raw_y = accelerometer_read_xyz(ADXL345_READ_Y);
	float raw_z = accelerometer_read_xyz(ADXL345_READ_Z);
	
	accelerometer_process_data(&data[0], raw_x, raw_y, raw_z);
}
