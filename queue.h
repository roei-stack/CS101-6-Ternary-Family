/***********
* Roei Cohen
* 325714152
* 01
* ex6
***********/

#ifndef _QUEUE_H
#define _QUEUE_H

// A linked list (LL) node to store a queue entry 
typedef struct QItem
{
	void* data;
	struct QItem* next;
}QItem;

// The queue, front stores the front node of LL and rear stores the 
// last node of LL 
typedef struct QList
{
	struct QItem *first, *last;
}QList;

//i added these so i can easily indicate a memory error to ex6.c
#define MEMORY_SECCESS 1
#define MEMORY_FAILURE 0

QList* createQueueList();
//q - the queue list, k- the Item (element)
int enQueue(QList* q, void* k);
void deQueue(QList* q);
// retutn 1 if empty and zero if not empty
int isEmpty(QList* q);
void destroyQueue(QList* q);

#endif
