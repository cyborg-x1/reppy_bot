/*
 * config.h
 *
 *  Created on: Jan 11, 2015
 *      Author: Christian Holl
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/*
 * Standard Includes
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "../globals/globals.h"


#define BAUD 9600


typedef enum
{
	REPPY_AVR_GET_ADC0,
	REPPY_AVR_GET_ADC1,
	REPPY_AVR_GET_ADC2,
	REPPY_AVR_GET_ADC3,
	REPPY_AVR_GET_ADC4,
	REPPY_AVR_GET_ADC5,
	REPPY_AVR_GET_ADC6,
	REPPY_AVR_GET_ADC7,
	REPPY_AVR_SET_VEL0,
	REPPY_AVR_SET_VEL1,
	REPPY_ROS_REC_ADC0,
	REPPY_ROS_REC_ADC1,
	REPPY_ROS_REC_ADC2,
	REPPY_ROS_REC_ADC3,
	REPPY_ROS_REC_ADC4,
	REPPY_ROS_REC_ADC5,
	REPPY_ROS_REC_ADC6,
	REPPY_ROS_REC_ADC7,
}reppy_avr_cmds_t;

#define HEADER_ARRAY_INIT 		   { 0xAA, 0x55, 0xA5, 0x5A }
#define AVR_CMD_ARRAY_INIT         {\
										REPPY_AVR_GET_ADC0,\
										REPPY_AVR_GET_ADC1,\
										REPPY_AVR_GET_ADC2,\
										REPPY_AVR_GET_ADC3,\
										REPPY_AVR_GET_ADC4,\
										REPPY_AVR_GET_ADC5,\
										REPPY_AVR_GET_ADC6,\
										REPPY_AVR_GET_ADC7,\
										REPPY_AVR_SET_VEL0,\
										REPPY_AVR_SET_VEL1,\
										REPPY_ROS_REC_ADC0,\
										REPPY_ROS_REC_ADC1,\
										REPPY_ROS_REC_ADC2,\
										REPPY_ROS_REC_ADC3,\
										REPPY_ROS_REC_ADC4,\
										REPPY_ROS_REC_ADC5,\
										REPPY_ROS_REC_ADC6,\
										REPPY_ROS_REC_ADC7\
									};

#define AVR_PAYLOAD_LEN_ARRAY_INIT {0,0,0,0,0,0,0,0,\
                                    2,2,2,2,2,2,2,2 }
#define AVR_PAYLOAD_BUFFER_LEN	   2


#endif /* CONFIG_H_ */
