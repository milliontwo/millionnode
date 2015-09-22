/*
 * FIFO.h
 *
 *  Created on: 12.07.2013
 *      Author: najiji
 */

#ifndef FIFO_H_
#define FIFO_H_
#define FIFOSIZE 20



typedef volatile struct
{
	char data[FIFOSIZE];
	int head;
	int tail;
} Fifo;


void fifo_init(Fifo* list);

int fifo_enqueue(Fifo* list, char item);

char fifo_dequeue(Fifo* list);

void fifo_flush(Fifo* list);

int	fifo_empty(Fifo* list);

int fifo_length(Fifo* list);

#endif /* FIFO_H_ */
