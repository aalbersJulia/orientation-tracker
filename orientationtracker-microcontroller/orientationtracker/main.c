/*
 * orientationtracker.c
 *
 * Created: 29-3-2022 13:41:23
 * Author : Julia Aalbers
 */ 

#include "twi.h"
#include "accelerometer.h"
#include "ioexpander.h"
#include "serialcommunication.h"

char value[200] = {'0'};

int main(void)
{
	twi_init();
	usart_init();
	UDR0 = 0;
	
	ioexpander_default_configuration();
	accelerometer_default_configuration();
	
	while (1) 
    {
		accelerometer_get_data(&value[0]);
		
		ioexpander_set_data(ioexpander_get_data());
		usart_transmit(&value[0]);
	}
}


