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
 * Thresholds that define when a measurement gets read
 * as HIGH or LOW
 * Minimum value for measurement: 0
 * Maximum value for measurement: 255
 */
#define LOW_THRESHOLD 80
#define HIGH_THRESHOLD 175


/*
 * Type to describe current rotation direction of hand
 */
typedef enum {CLOCKWISE = 1, ANTICLOCKWISE = -1} Direction;

/*
 * Type that describes the measured level either as high or low
 */
typedef enum {HIGH, LOW} Level;


/*
 * Struct to hold feedback position of a certain clockhand
 */
typedef struct {
	uint8_t				adc_pin;
	volatile uint8_t 	position;
	Direction 			direction;
	Level				last_level;

} Feedback;


/*
 * Initializes the adc to start acquring feedback
 */
void feedback_init();

/*
 * Updates the feedback provided
 */
void feedback_update(Feedback* feedback);


#endif /* FEEDBACK_H_ */
