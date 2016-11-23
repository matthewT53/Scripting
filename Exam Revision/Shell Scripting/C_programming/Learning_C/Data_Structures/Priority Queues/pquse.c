/*
	Name: Matthew Ta
	Date: 29/9/2015
	Description: User of the priority queue ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "priorityQueue.h"

#define MAX 10
#define PRIORITY 1000

int main(void)
{
	PQueue q = newPQueue(); // create a new priority queue
	int i = 0, value = 0;

	srand(time(NULL));

	for (i = 0; i < MAX; i++){
		joinPQueue(q, i, rand() % PRIORITY);
	}

	printf("[BEFORE REORDER]:\n");
	showPQueue(q);
	reorder(q, 5, rand() % PRIORITY);
	printf("[AFTER REORDER]:\n");
	showPQueue(q);	
	deletePQueue(q);

	printf("Testing the PQueue ADT:\n");
	q = newPQueue();
	joinPQueue(q, 0, 100);
	joinPQueue(q, 1, 120);
	joinPQueue(q, 2, 150);
	joinPQueue(q, 3, 180);
	joinPQueue(q, 4, 190);
	printf("[BEFORE REORDER]:\n");
	showPQueue(q);
	reorder(q, 4, 80);
	printf("[AFTER REORDER]:\n");
	showPQueue(q);
	value = leavePQueue(q);
	assert(value == 3);
	deletePQueue(q);
	printf("Passed first test.\n");

	printf("Testing when re-ordering two nodes with the same value.\n");
	q = newPQueue();
	joinPQueue(q, 0, 100);
	joinPQueue(q, 1, 120);
	joinPQueue(q, 0, 250);
	joinPQueue(q, 3, 180);
	joinPQueue(q, 4, 190);
	printf("[BEFORE REORDER]:\n");
	showPQueue(q);
	reorder(q, 4, 80);
	printf("[AFTER REORDER]:\n");
	showPQueue(q);
	value = leavePQueue(q);
	assert(value == 0);
	deletePQueue(q);
	printf("Passed second test.\n");

	printf("Testing when unique values have same priorities.\n");
	q = newPQueue();
	joinPQueue(q, 0, 100);
	joinPQueue(q, 1, 100);
	joinPQueue(q, 0, 100);
	joinPQueue(q, 3, 100);
	joinPQueue(q, 4, 100);
	printf("[BEFORE REORDER]:\n");
	showPQueue(q);
	reorder(q, 4, 100);
	printf("[AFTER REORDER]:\n");
	showPQueue(q);
	value = leavePQueue(q);
	assert(value == 0);
	deletePQueue(q);
	printf("Passed third test.\n");

	printf("Testing when priorities are in ascending order.\n");
	q = newPQueue();
	joinPQueue(q, 0, 100);
	joinPQueue(q, 1, 120);
	joinPQueue(q, 2, 140);
	joinPQueue(q, 3, 160);
	joinPQueue(q, 4, 180);
	printf("[BEFORE REORDER]:\n");
	showPQueue(q);
	reorder(q, 4, 190);
	printf("[AFTER REORDER]:\n");
	showPQueue(q);
	value = leavePQueue(q);
	assert(value == 4);
	deletePQueue(q);
	printf("Passed fourth test.\n");

	printf("Testing when priorities are in descending order.\n");
	q = newPQueue();
	joinPQueue(q, 0, 190);
	joinPQueue(q, 1, 180);
	joinPQueue(q, 2, 170);
	joinPQueue(q, 3, 160);
	joinPQueue(q, 4, 150);
	printf("[BEFORE REORDER]:\n");
	showPQueue(q);
	reorder(q, 4, 100);
	printf("[AFTER REORDER]:\n");
	showPQueue(q);
	value = leavePQueue(q);
	assert(value == 0);
	deletePQueue(q);
	printf("Passed fifth test.\n");

	printf("Passed all tests, you are Awesome!.\n");
	return EXIT_SUCCESS;
}
