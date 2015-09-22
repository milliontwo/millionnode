/*
 * bus.c
 *
 *  Created on: Sep 10, 2015
 *      Author: najiji
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "i2c.h"
#include "FIFO.h"

/* global module scoped i2c properties */
I2C i2c;

/* Helper function to reset received and transmitted data to prepare for next transmission */
void _i2c_reset() {
	fifo_flush(&(i2c.rxbuf));
	fifo_flush(&(i2c.txbuf));
	i2c.is_general_call = 0;
}

void i2c_init(uint8_t address, void (*prepare_tx)(Fifo* rxbuff, Fifo* txbuff, uint8_t is_general_call), void (*handle_rx)(Fifo* rxbuff, uint8_t is_general_call)){
	i2c.handle_rx = handle_rx;
	i2c.prepare_tx = prepare_tx;
	_i2c_reset();


	/* Enable AVR I2C Hardware with global call */
	TWAR = (address << 1)|1;
	TWCR |= (1<<TWEA)|(1<<TWEN)|(1<<TWIE);
	sei();
}



/*
 * I2C Interrupt
 */
ISR(TWI_vect){
	switch(TW_STATUS){
		/* Own Address received. Master awaits data */
		case TW_ST_SLA_ACK:
			fifo_flush(&i2c.txbuf);
			i2c.prepare_tx(&(i2c.rxbuf), &(i2c.txbuf), 0);
			TWDR = fifo_dequeue(i2c.txbuf);
			break;

		/* Transmitted data to master. Ack received */
		case TW_ST_DATA_ACK:
			TWDR = fifo_dequeue(i2c.txbuf);
			break;

		/* Transmitted data to master. Nack received */
		case TW_ST_DATA_NACK:	/* intentional fallthrough as same behaviour */
		case TW_ST_LAST_DATA:
			break;

		/* Own address received. Master wants to send data */
		case TW_SR_SLA_ACK:
			fifo_flush(&(i2c.rxbuf));
			i2c.is_general_call = 0;
			break;

		/* General call received. Master wants to send data */
		case TW_SR_GCALL_ACK:
			fifo_flush(&(i2c.rxbuf));
			i2c.is_general_call = 1;
			break;

		/* Data from master received. Ack returned */
		case TW_SR_DATA_ACK: /* intentional fallthrough */


		/* Data from master received. Nack returned */
		case TW_SR_DATA_NACK: /* intentional fallthrough */


		/* Data from general call received. ACK returned */
		case TW_SR_GCALL_DATA_ACK: /* intentional fallthrough */


		/* Data from general call received. Nack returned */
		case TW_SR_GCALL_DATA_NACK:
			fifo_enqueue(&(i2c.rxbuf), TWDR);
			break;

		/* Stop (or repeated start) while in Receive mode */
		case TW_SR_STOP:
			i2c.handle_rx(&(i2c.rxbuf), i2c.is_general_call);
			break;

		/* No bus information available */
		case TW_NO_INFO:
			break;

		/* Error on bus */
		case TW_BUS_ERROR:
		default:
			break;
	}
}
