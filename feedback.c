/*
 * feedback.c
 *
 *  Created on: Sep 6, 2015
 *      Author: najiji
 */

#include <avr/io.h>
#include "feedback.h"

/*
 * Initializes the adc to start acquring feedback
 */
void feedback_init() {
	ADCSRA |= (1<<ADEN);
}

/*
 * Updates the feedback provided
 *
 * (!) Function could be prone to noise on the receiver, especially during a
 * transition when the sample rate is very high. Has to be evaluated yet if
 * an integration based solution performs better.
 */
void feedback_update(Feedback* feedback){

	/* Select correct input and set result left align */
	ADMUX = (1<<ADLAR)|feedback->adc_pin;

	/* Start conversion */
	ADCSRA |= (1<<ADSC);

	/* Wait for conversion to finish */
	while(ADCSRA&(1<<ADSC));

	uint8_t measured_value = ADCH;

	if(measured_value < LOW_THRESHOLD){
		if(feedback->last_level == HIGH) {
			feedback->position = feedback->position+feedback->direction;
			feedback->last_level = LOW;
		}
	}
	else if(measured_value > HIGH_THRESHOLD){
		if(feedback->last_level == LOW) {
			feedback->position = feedback->position+feedback->direction;
			feedback->last_level = HIGH;
		}
	}
	/*
	 * No else, as if value between thresholds should get ignored.
	 */

	/*
	 * Fix rollover
	 */
	if(feedback->position >= FEEDBACK_POSITIONS){
		if(feedback->position == 255){
			feedback->position = FEEDBACK_POSITIONS-1;
		}
		else {
			feedback->position = 0;
		}
	}
}
