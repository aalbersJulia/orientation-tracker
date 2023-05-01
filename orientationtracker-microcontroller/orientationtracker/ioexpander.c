/*
 * ioexpander.c
 *
 * Created: 19-4-2022 19:33:39
 *  Author: Julia Aalbers
 */ 

#include "ioexpander.h"
#include "serialcommunication.h"

void ioexpander_configure_register(unsigned int reg, char data)
{
	twi_start(IOEXPANDER_ID, 0x00, TW_WRITE);
	twi_write(reg);
	twi_write(data);
	twi_stop();
}

void ioexpander_set_data(char *data)
{
	twi_start(IOEXPANDER_ID, 0x00, TW_WRITE);
	twi_write(GPIO);
	twi_write(data);
	twi_stop();
}

uint8_t ioexpander_get_data()
{
	
	uint8_t led_value = 0b000000;
	float x = accelerometer_read_xyz(ADXL345_READ_X);
	float y = accelerometer_read_xyz(ADXL345_READ_Y);
	float z = accelerometer_read_xyz(ADXL345_READ_Z);
	
	if(ioexpander_led_data(x) == 1){
		return 0b110000;
	} else if(ioexpander_led_data(y) == 1){
		return 0b001100;
	} else if(ioexpander_led_data(z) == 1){
		return 0b000011;
	}else {
		return 0b000000;
	}
}

uint8_t ioexpander_led_data(float value)
{
	if((value > 0.90 && value < 1.10) || (value > -1.10 && value < -0.90)) return 1;
	return -1;
}
	

void ioexpander_default_configuration()
{
	ioexpander_configure_register(IODIR, 0b00000000);
	ioexpander_configure_register(GPIO, 0b00000000); // reset output port
}
