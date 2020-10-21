/**************************************************************************
 File name:			pqueuedriver.c
 Author:        Kailani Pinon
 Date:          10.09.2020
 Class:         CS300
 Assignment:    Dynamic Priority Queue List
 Purpose:       Practice creating a priority queue ADT based on list ADT
 *************************************************************************/
#include "../../GenericDynamicList/include/list.h"
#include "../include/pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	szStr - the message to print
 Returned:	 	none
 *************************************************************************/
static void success (char * szStr)
{
	printf ("SUCCESS: %s\n", szStr);
}

/**************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	szStr - the message to print
 Returned:	 	none
 *************************************************************************/
static void failure (char * szStr)
{
	printf ("FAILURE: %s\n", szStr);
	exit (EXIT_FAILURE);
}

/****************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 	 	 	 	 	 	 	failure

 Parameters:	szStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void assert (bool bExpression, char *pTrue, char *pFalse)
{
	if (bExpression)
	{
		success (pTrue);
	}
	else
	{
		failure (pFalse);
	}
}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the priority queue

 Parameters:	none

 Returned:	 	EXIT_SUCCESS
 *************************************************************************/
int main ()
{

	PriorityQueue sMyQueue;
	//todo: make a second list and test;
	PriorityQueueElement sMyPQElement; //an item to insert to queue/list
	int queueSize = 0, myPriority;

	//only needs to load once
	lstLoadErrorMessages ();
	//initializes sMyQueue;
	pqueueCreate (&sMyQueue);

	queueSize = pqueueSize (&sMyQueue);
	assert (queueSize == 0, "The size of the queue is 0",
			"The size of the queue is not 0");
	myPriority = 2;
	pqueueEnqueue (&sMyQueue, &sMyPQElement, sizeof(PriorityQueueElement),
			myPriority);
	queueSize = pqueueSize (&sMyQueue);
	assert (queueSize == 1,
			"1 Priority Queue Element has been added to the list.",
			"1 Priority Queue Element was not successfully added to the list.");

	myPriority = 1;
	pqueueEnqueue (&sMyQueue, &sMyPQElement, sizeof(PriorityQueueElement),
			myPriority);
	queueSize = pqueueSize (&sMyQueue);
	assert (queueSize == 2,
			"2nd Priority Queue Element has been added to the list.",
			"2nd Priority Queue Element was not successfully added to the list.");

	myPriority = 0;
	pqueueEnqueue (&sMyQueue, &sMyPQElement, sizeof(PriorityQueueElement),
			myPriority);
	queueSize = pqueueSize (&sMyQueue);

	pqueuePeek (&sMyQueue, &sMyPQElement, sizeof(PriorityQueueElement),
			&myPriority);
	assert (0 == myPriority, //valgrind error: use of uninitialized value
	"Priority is 0.", "Priority isn't 0.");

	//lstFirst(&(sMyQueue.sTheList));
	assert (2 == myPriority, //valgrind error: use of uninitialized value
	"First item in list is now current. Priority is 2.",
			"First item in list did not change to current. Priority is NOT 2.");

	//BREAKS HERE//

	//I don't think dequeue is working either - todo: fix???
	pqueueDequeue (&sMyQueue, &sMyPQElement, sizeof(PriorityQueueElement),
			&myPriority);
	assert (1 == myPriority, "'sMyPQElement->priority' match 'myPriority'.",
			"'sMyPQElement->priority' DOESN'T match 'myPriority'.");

	queueSize = pqueueSize (&sMyQueue);
	assert (queueSize == 2, "The size of the queue is 2",
			"The size of the queue is not 2");

	//pqueueTerminate(&(sMyQueue->sTheList));
	//error: invalid type argument
	//
	puts ("TEST: END.");
	return EXIT_SUCCESS;
}
