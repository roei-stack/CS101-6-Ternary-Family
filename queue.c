/***********
* Roei Cohen
* 325714152
* 01
* ex6
***********/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/******************
* Function Name:createQueueList
* Input: none
* Output: an initilized queue
* Function Operation: allocating 8 bytes for the 2 pointers of the queue
* if allocation failed -> return null (will indicate a fatal failure to Utils.h)
* set the first and last pointers to null (currently)
* return the queue
******************/
QList* createQueueList()
{
	QList* q = (QList *)malloc(sizeof(QList));
	if (q == NULL)
		//returning null will indicate a memory failure to 'utilities.c' which will send it to ex6.c
		return NULL;
	//setting the first and last values to null
	q->first = NULL;
	q->last = NULL;
	return q;
}

/******************
* Function Name: enQueue
* Input: a queue list and a pointer
* Output: adds the pointer to the end of the list, AND returnes the memory situation
* Function Operation: 1.allocating memory for the new chain (item)
* 2.copying values
* 3.if the list is empty -> copy the values to the first (and only) chain
* 4.otherwizs -> set the chain after the last one to item
* 5.assuming allocation went seccesfully, return MEMORY_SECCESS
******************/
int enQueue(QList* q, void* k)
{
	//allocating memory for the new chain (item)
	QItem* item = (QItem*)malloc(sizeof(QItem));
	if (item == NULL)
		return MEMORY_FAILURE;
	//copying values
	item->data = k;
	item->next = NULL;
	//empty list -> copy the values to the first (and only) chain
	if (q->first == NULL)
	{
		q->first = item;
		q->last = item;
	}
	//otherwizs -> set the chain after the last one to item
	else
	{
		q->last->next = item;
		//and set the last chain to "item"
		q->last = item;
	}
	return MEMORY_SECCESS;
}

/******************
* Function Name:deQueue
* Input:a queue list
* Output: frees the first item of the queue
* Function Operation: 1.save a pointer to the first item (CALL IT ITEM)
* 2.if the queue is empty -> return
* 3.set the first item in the qlist to the second item
* 4.set item->next to null
* 5.free the item
* 6.profit
******************/
void deQueue(QList* q)
{
	//saving a pointer to the first
	QItem* item = q->first;
	//empty list == nothing to dequeue
	if (item == NULL)
		return;
	//the first item will be the second one
	q->first = item->next;
	//disconnecting item from the list
	item->next = NULL;
	//freeing the item
	free(item);
}

/******************
* Function Name:isEmpty
* Input:a queue list(*)
* Output: 1->the list is empty, 0->the list is not empty
* Function Operation:
* 1.if the first item in the queue is NULL -> RETURN 1
* 2. return 0
******************/
int isEmpty(QList* q)
{
	//if the first value is empty, the whole list is empty
	if (q->first == NULL)
		return 1;
	//if we reached here, the queue is not empty
	return 0;
}

/******************
* Function Name:destroyQueue
* Input: a queue list
* Output: frees it (non because void)
* Function Operation: 1. check if the queue is empty, if it is->return
* 2.if its not -> remove the first item using the dequeue function, then recall the function
******************/
void destroyQueue(QList* q)
{
	//if the queue is empty, stop
	if (isEmpty(q) == 1)
	{
		//free the list block
		free(q);
		return;
	}
	//free the first current item
	deQueue(q);
	//free the next-first current item
	destroyQueue(q);
}
