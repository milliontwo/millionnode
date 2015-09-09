/*
 * motor.h
 *
 *  Created on: Sep 3, 2015
 *      Author: najiji
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

typedef volatile uint8_t Register;


/*
 * Type that stores motor pin configuration and motor position states
 */
typedef struct {
	Register* 	port;				//the hardware port register, the motor is connected
	uint8_t 	pins[4];			//The pins on the port on which the wires of motor are connected.
	int8_t 		sequence_position;	//the current position in the four-beat cycle of that motor
} Motor;


/*
 * Does move the motor a single step
 */
void motor_step_forward(Motor* motor);
void motor_step_backward(Motor* motor);

#endif /* MOTOR_H_ */
