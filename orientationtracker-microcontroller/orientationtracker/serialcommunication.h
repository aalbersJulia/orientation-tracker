/*
 * serialcommunication.h
 *
 * Created: 20-4-2022 11:13:54
 *  Author: Julia Aalbers
 */ 


#ifndef SERIALCOMMUNICATION_H_
#define SERIALCOMMUNICATION_H_

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void usart_init(void);
void usart_transmit(char* data);

#endif /* SERIALCOMMUNICATION_H_ */