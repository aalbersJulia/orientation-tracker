/*
 * serialcommunication.c
 *
 * Created: 20-4-2022 11:14:09
 *  Author: Julia Aalbers
 */ 

#include "serialcommunication.h"

void usart_init(void)
{
	// baud rate
	UBRR0=103;
	// enable receiver and transmitter
	UCSR0B |=(1<<RXEN0 |(1 <<TXEN0));
	// frame format - 8 bit data 2 stop bits
	UCSR0C = (1<<USBS0 )|(3<<UCSZ00);
}

void usart_transmit(char* data)
{
	
	// Wait for empty transmit buffer
	while ( !( UCSR0A & (1<<UDRE0)) );
	
	for(int i = 0; i < strlen(data); i++){
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = data[i];
	}

	//  Put data into buffer, sends the data
	// UDR0 = data;
}
