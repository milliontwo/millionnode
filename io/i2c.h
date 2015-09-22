/*
 * bus.h
 *
 *  Created on: Sep 10, 2015
 *      Author: najiji
 */

#ifndef BUS_H_
#define BUS_H_

#include "FIFO.h"

/*
 * Size of incoming and outgoing buffer.
 */
#define BUFSIZE 5

/*
 * Struct that holds all the definitions for the bus
 */
typedef struct {
	volatile Fifo 	rxbuf;
	volatile Fifo 	txbuf;
	void (*prepare_tx)(Fifo* rxbuff, Fifo* txbuff, uint8_t is_general_call);
	void (*handle_rx)(Fifo* rxbuff, uint8_t is_general_call);
	uint8_t is_general_call;
} I2C;


/*
 * Initializes the bus and enables interrupts
 * requires functions to prepare the tx buff prior to transmission and functions to handle rx buff after reception.
 *
 * The footprint of the functions looks as follows:
 *
 * prepare_tx(Fifo* rxbuff, Fifo* txbuff, uint8_t is_general_call)
 * handle_rx(Fifo* rxbuff, uint8_t is_general_call)
 *
 * where is_general_call is != 0 if the last reception was a general call
 */
void i2c_init(uint8_t address, void (*prepare_tx)(Fifo* rxbuff, Fifo* txbuff, uint8_t is_general_call), void (*handle_rx)(Fifo* rxbuff, uint8_t is_general_call));



#endif /* BUS_H_ */
