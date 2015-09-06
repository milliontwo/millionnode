/*
 * feedback.h
 *
 *  Created on: Sep 6, 2015
 *      Author: najiji
 */

#ifndef FEEDBACK_H_
#define FEEDBACK_H_

/*
 * The amount of feedback positions on disk
 * A Feedback position is basically an edge between dark/bright
 *
 * (!) if larger than 256, a few integer types have to be
 * redefined
 */
#define FEEDBACK_POSITIONS 256

/*
 * Type to describe current rotation direction of hand
 */
typedef enum {CLOCKWISE, ANTICLOCKWISE} Direction;
typedef enum {BRIGHT, UNDEFINED, DARK} Brightness;


/*
 * Struct to hold feedback position of a certain clockhand
 */
typedef struct {
	uint8_t 	position;
	Direction 	direction;
	Brightness	last_brightness;

} Feedback;


#endif /* FEEDBACK_H_ */
