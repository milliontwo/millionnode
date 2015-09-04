/*
 * motor.c
 *
 *  Created on: Sep 3, 2015
 *      Author: najiji
 */
#include "motor.h"

/*
 * Possible operation modes
 */
#define TWO_PHASE 1
#define SINGLE_PHASE 2
#define EIGHT_SHOT 3

//Define operation mode to be used
#define MODE EIGHT_SHOT

/*
 * Calculates new port state for desired sequence position and applies it
 */
void _motor_step_into_sequence_position(Motor* motor){
#if MODE == TWO_PHASE
	switch(motor->sequence_position){
	case 0:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[0])|(1<<motor->pins[2]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[1])|(1<<motor->pins[3]));
		break;
	case 1:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[1])|(1<<motor->pins[2]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[3]));
		break;
	case 2:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[1])|(1<<motor->pins[3]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[2]));
		break;
	case 3:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[0])|(1<<motor->pins[3]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[1])|(1<<motor->pins[2]));
		break;
	default:
		motor->sequence_position = 0;
	}
#endif
#if MODE == SINGLE_PHASE
	switch(motor->sequence_position){
	case 0:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[0]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[1])|(1<<motor->pins[2])|(1<<motor->pins[3]));
		break;
	case 1:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[2]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[1])|(1<<motor->pins[3]));
		break;
	case 2:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[1]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[2])|(1<<motor->pins[3]));
		break;
	case 3:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[3]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[1])|(1<<motor->pins[2]));
		break;
	default:
		motor->sequence_position = 0;
	}
#endif

#if MODE == EIGHT_SHOT
	switch(motor->sequence_position){
	case 0:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[0])|(1<<motor->pins[2]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[1])|(1<<motor->pins[3]));
		break;
	case 1:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[2]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[1])|(1<<motor->pins[3]));
		break;
	case 2:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[1])|(1<<motor->pins[2]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[3]));
		break;
	case 3:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[1]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[2])|(1<<motor->pins[3]));
		break;
	case 4:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[1])|(1<<motor->pins[3]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[2]));
		break;
	case 5:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[3]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[0])|(1<<motor->pins[1])|(1<<motor->pins[2]));
		break;
	case 6:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[0])|(1<<motor->pins[3]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[1])|(1<<motor->pins[2]));
		break;
	case 7:
		*(motor->port) = *(motor->port) |= (1<<motor->pins[0]);
		*(motor->port) = *(motor->port) &= ~((1<<motor->pins[1])|(1<<motor->pins[2])|(1<<motor->pins[3]));
		break;
	default:
		motor->sequence_position = 0;
	}
#endif
}

/*
 * Moves the motor a step forward
 */
void motor_step_forward(Motor* motor) {
	motor->sequence_position++;
#if MODE == EIGHT_SHOT
	if(motor->sequence_position >= 7) {
		motor->sequence_position = 0;
	}
#else
	if(motor->sequence_position >= 3) {
		motor->sequence_position = 0;
	}
#endif
	_motor_step_into_sequence_position(motor);
}

/*
 * Moves the motor a step backward
 */
void motor_step_backward(Motor* motor){

	if(motor->sequence_position <= 0) {
#if MODE == EIGHT_SHOT
		motor->sequence_position = 7;
#else
		motor->sequence_position = 3;
#endif
	}

	else {
		motor->sequence_position--;
	}
	_motor_step_into_sequence_position(motor);
}
