/*
 * adc.c
 *
 *  Created on: Jan 11, 2015
 *      Author: Christian Holl
 */
#include "adc.h"


void adc_multiplexer(uint8_t mux)
{
	mux&=0xF;
	for (int b = 0; b < 4; ++b)
	{
		uint8_t bit=!!(mux&(1<<b));
		ADMUX|=(bit<<b);
		ADMUX&=~(!bit<<b);
	}
}


void adc_init()
{
	//Internal voltage reference
	ADMUX|=_BV(REFS1) | _BV(REFS0);

	//Enable ADC
	ADCSRA|=_BV(ADEN);

	//Enable ADC Auto Trigger
	ADCSRA|=_BV(ADATE);

	//Enable ADC Conversion Complete Interrupt
	ADCSRA|=_BV(ADIE);

	//Clear the Left Adjust Result Setting
	ADMUX&=~(_BV(ADLAR));

	//Set multiplexer to analog input 0
	adc_multiplexer(0);

	//No Comparator Mode and ADC in free running mode
	ADCSRB=0;

	//Maximum ADC frequency is 1 MHz
	//Prescaler is 16 according to the arduino clock
	ADCSRA|=_BV(ADPS2);
	ADCSRA&=~(_BV(ADPS1) | _BV(ADPS0));
}

ISR(ADC_vect)
{
	uart_sendByte('~');
}
