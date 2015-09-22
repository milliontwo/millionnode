/*
 * FIFO.c
 *
 *  Created on: 12.07.2013
 *      Author: najiji
 */

#include "FIFO.h"

void fifo_init(Fifo* list)
{
	list->head = 0;
	list->tail = 0;
}

int fifo_enqueue(Fifo* list, char item)
{
	if(list->head == FIFOSIZE) 				//FIFO recircle
		list->head = 0;						//restart at beginning
	list->data[list->head] = item;			//Assign value to storage position
	list->head++;							//increase start index
	return 1;
}

char fifo_dequeue(Fifo* list)
{
	if(list->tail == list->head) 			//FIFO empty, cannot dequeue
		return 0x00;						//FAIL value
	char value = list->data[list->tail]; 	//readout value

	list->tail++;
	if(list->tail == FIFOSIZE)				//if we reached end
		list->tail = 0;						//restart at beginning
	return value;
}

void fifo_flush(Fifo* list)
{
	list->head = 0;							//reset position
	list->tail = 0;
}

int	fifo_empty(Fifo* list)
{
	return list->tail == list->head;
}

int	fifo_length(Fifo* list)
{
	return list->head - list->tail;
}
