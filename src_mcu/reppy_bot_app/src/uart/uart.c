
//void uart_init()
//{
//	//USART Enable 9600 baud, 8 bit, 1 stop bit, no parity,
//	UCSR0A|=(1<<U2X0);
//	UCSR0B|=(1<<RXCIE0)|(1<<TXEN0)|(1<<RXEN0);
//	UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00)|(1<<USBS0);
//	UBRR0=UBRRH_VALUE;
//}

/*
 * uart.c
 *
 *  Created on: Jan 11, 2015
 *      Author: Christian Holl
 */



#include "uart.h"
#include <sersyncproto.h>

void uart_sendByte(uint8_t byte)
{
	//Wait for empty output buffer
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = byte;
}

#include <util/setbaud.h>

void uart_init(void)
{
    UBRR0 = UBRR_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);   	/* Enable RX and TX */
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); 				/* 8-bit data */
}



ISR(USART_RX_vect)
{
	static const uint8_t cmds[]=AVR_CMD_ARRAY_INIT;
	static const uint8_t payload_len[]=AVR_PAYLOAD_LEN_ARRAY_INIT;
	static const uint8_t header[]=HEADER_ARRAY_INIT;
	static uint8_t payload_buffer[2];
	INIT_SERSYNCPROTO_DATA(data,cmds,payload_len,header,payload_buffer);


	uint8_t cur_byte=UDR0;
	if(sersyncproto(&data,cur_byte))
	{
		switch (SERSYNCPROTO_GET_CUR_CMD(data))
		{
			case REPPY_AVR_GET_ADC0:
				uart_sendByte('~');//TODO remove just for testing
				break;
			default:
				break;
		}
	}
}
