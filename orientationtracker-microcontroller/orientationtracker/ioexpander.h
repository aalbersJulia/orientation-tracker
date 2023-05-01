/*
 * ioexpander.h
 *
 * Created: 19-4-2022 19:33:26
 *  Author: Julia Aalbers
 */ 


#ifndef IOEXPANDER_H_
#define IOEXPANDER_H_

#include <avr/io.h>
#include "twi.h"
#include "accelerometer.h"

#define IOEXPANDER_ID 0x20
#define IODIR 0x00
#define GPIO 0x09

void ioexpander_set_data(char *data);
void ioexpander_configure_register(unsigned int reg, char data);
uint8_t ioexpander_get_data();
uint8_t ioexpander_led_data(float value);
void ioexpander_default_configuration();


#endif /* IOEXPANDER_H_ */