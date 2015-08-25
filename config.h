/*
 * config.h
 *
 *  Created on: Aug 25, 2015
 *      Author: najiji
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>

/* PORT CONFIGURATION */
#define MOT1_DDR DDRB
#define MOT1_PORT PORTB
#define MOT1_A PB0
#define MOT1_B PB1
#define MOT1_C PB2
#define MOT1_D PB3

#define MOT2_DDR DDRB
#define MOT2_PORT PORTB
#define MOT2_A PB4
#define MOT2_B PB5
#define MOT2_C PB6
#define MOT2_D PB7

#define MOT3_DDR DDRD
#define MOT3_PORT PORTD
#define MOT3_A PD0
#define MOT3_B PD1
#define MOT3_C PD2
#define MOT3_D PD3

#define MOT4_DDR DDR
#define MOT4_PORT PORTD
#define MOT4_A PD4
#define MOT4_B PD5
#define MOT4_C PD6
#define MOT4_D PD7


#endif /* CONFIG_H_ */
