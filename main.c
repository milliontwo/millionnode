/*
 * millionboot is the userspace application for a single node in the milliontwo project.
 *
 * A node receives commands over I2C and controls four motors (two watchfaces) accordingly
 *
 *  Created on: Aug 25, 2015
 *      Author: najiji
 */

#include <avr/io.h>
#include "io/uart.h"
#include "motor.h"
#include "motor_config.h"

#define DEBUG 1


int main(){

	/*
	 * Initialization
	 */

	/* Declare all motor pins as output */
	MOT1_DDR |= (1<<MOT1_A)|(1<<MOT1_B)|(MOT1_C)|(MOT1_D);
	MOT2_DDR |= (1<<MOT2_A)|(1<<MOT2_B)|(MOT2_C)|(MOT2_D);
	MOT3_DDR |= (1<<MOT3_A)|(1<<MOT3_B)|(MOT3_C)|(MOT3_D);
	MOT4_DDR |= (1<<MOT4_A)|(1<<MOT4_B)|(MOT4_C)|(MOT4_D);

	/* create the 4 motors on the stack */
	Motor mot1 = {
			&MOT1_PORT,
			{MOT1_A, MOT1_B, MOT1_C, MOT1_D},
			0
	};
	Motor mot2 = {
			&MOT2_PORT,
			{MOT2_A, MOT2_B, MOT2_C, MOT2_D},
			0
	};
	Motor mot3 = {
			&MOT3_PORT,
			{MOT3_A, MOT3_B, MOT3_C, MOT3_D},
			0
	};
	Motor mot4 = {
			&MOT4_PORT,
			{MOT4_A, MOT4_B, MOT4_C, MOT4_D},
			0
	};



	/*
	 * Infinite loop starts here
	 */
	while(1) {

	}

	return 0;
}
