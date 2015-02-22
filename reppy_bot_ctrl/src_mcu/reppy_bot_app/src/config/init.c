/*
 * init.c
 *
 *  Created on: Jan 11, 2015
 *      Author: Christian Holl
 */

#include "../../../../../reppy_bot/src_mcu/reppy_bot_app/src/config/init.h"

void init()
{
	uart_init();
	adc_init();
	sei();
}
