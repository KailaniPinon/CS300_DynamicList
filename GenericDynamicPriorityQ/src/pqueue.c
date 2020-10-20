/**************************************************************************
 File name:			pqueue.c
 Author:        Kailani Pinon
 Date:          10.09.2020
 Class:         CS300
 Assignment:    Dynamic Priority Queue List
 Purpose:       This file implements the Priority Queue ADT from pqueue.h
 *************************************************************************/

#include "../include/pqueue.h"
#include "../../GenericDynamicList/include/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char gszPQErrors[NUMBER_OF_PQ_ERRORS][MAX_ERROR_PQ_CHARS];

/**************************************************************************
 Function:			processListError

 Description: 	Process the error code passed to this routine.
 	 	 	 	 	 	 	 	Print appropriate message according to error code.

 Parameters: 		None

 Returned:			None
 *************************************************************************/
static void processPQError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszPQErrors[errorCode]);

	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function:			pqueueLoadErrorMessages

 Description:		Loads the error message strings for the error handler to use.

 Parameters: 		None

 Returned:			None
 *************************************************************************/
void pqueueLoadErrorMessages ()
{
	LOAD_PQ_ERRORS
}

/**************************************************************************
 Function:			pqueueCreate

 Description: 	If PQ can be created, then PQ exists and is empty.

 Parameters: 		psQueue	- pointer to priority queue

 Returned:			None
 *************************************************************************/
void pqueueCreate (PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processPQError ("pqueueCreate", ERROR_NO_PQ_CREATE);
	}
	else
	{
		lstCreate (&psQueue->sTheList);
	}
}

/**************************************************************************
 Function:			pqueueTerminate

 Description: 	If PQ ccan be terminated, the PQ no longer exists and is
 	 	 	 	 	 	 	 	empty.

 Parameters: 		psQueue	- pointer to priority queue

 Returned:			None
 *************************************************************************/
void pqueueTerminate (PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processPQError ("pqueueTerminate", ERROR_NO_PQ_TERMINATE);
	}
	else
	{
		lstTerminate (&psQueue->sTheList);
	}
}

/**************************************************************************
 Function:			pqueueSize

 Description: 	Returns the number of elements in the PQ.

 Parameters: 		psQueue	- pointer to priority queue

 Returned:			None
 *************************************************************************/
int pqueueSize (const PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processPQError ("pqueueSize", ERROR_INVALID_PQ);
	}
	return lstSize (&psQueue->sTheList);
}

/**************************************************************************
 Function:			pqueueIsEmpty

 Description: 	If PQ is empty, return true; otherwise, return false.

 Parameters: 		psQueue	- pointer to priority queue

 Returned:			lstIsEmpty(psQueue->sTheList)
 *************************************************************************/
bool pqueueIsEmpty (const PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processPQError ("pqueueIsEmpty", ERROR_INVALID_PQ);
	}
	return lstIsEmpty (&psQueue->sTheList);
}

/**************************************************************************
 Function:			pqueueEnqueue

 Description: 	Insert the element into the priority queue based on the
          			priority of the element.

 Parameters: 		psQueue	- pointer to priority queue
 	 	 	 	 	 	 	 	pBuffer - content in element
 	 	 	 	 	 	 	 	size		- memory size of content
 	 	 	 	 	 	 	 	priority-	index of element

 Returned:			None
 *************************************************************************/
void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer, int size,
		int priority)
{
	if (NULL == psQueue)
	{
		processPQError ("pqueueEnqueue", ERROR_INVALID_PQ);
	}
	else if (NULL == pBuffer)
	{
		processPQError ("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}
	//create a queue element to store priority and data value
	PriorityQueueElementPtr psNewPQElement;
	psNewPQElement = (PriorityQueueElementPtr) malloc
									 (sizeof(PriorityQueueElement));
	psNewPQElement->pData = malloc (size);

	PriorityQueueElement psNewElement;

	//store appropriate arguments into new element
	memcpy (psNewPQElement->pData, pBuffer, size);
	psNewPQElement->priority = priority;

	if (pqueueIsEmpty (psQueue)) //list empty
	{
		lstInsertAfter (&(psQueue->sTheList), &psNewPQElement, size);
		lstFirst (&(psQueue->sTheList)); //current assigned to new node
		puts ("FIRST ITEM ADDED!");
	}
	else if (!(pqueueIsEmpty (psQueue)) && !lstHasNext (&(psQueue->sTheList)))
	//if only 1 item, insert item after first
	{
		//unsure, but I don't think next is being updated
		lstInsertAfter (&(psQueue->sTheList), &psNewPQElement, size);
	}
	else
	{
		lstFirst (&(psQueue->sTheList));
		do
		{
			lstPeek(&(psQueue->sTheList), &psNewElement, sizeof(PriorityQueueElement));
			//psNewElement.priority
			//place element in list
			lstNext (&psQueue->sTheList);

		} while (psNewElement.priority > priority); //
		//zero highest priority/precedence

		lstNext (&psQueue->sTheList);
	}
	//use peek to find priority
}

/**************************************************************************
 Function:			pqueueDequeue

 Description: 	Remove the element from the front of the non-empty queue.

 Parameters: 		psQueue	- pointer to priority queue
 	 	 	 	 	 	 	 	pBuffer - content in element
 	 	 	 	 	 	 	 	size		- memory size of content
 	 	 	 	 	 	 	 	priority-	index of element

 Returned:			None
 *************************************************************************/
void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
														int size, int  *pPriority)
{
	if (NULL == psQueue)
		{
			processPQError("pqueueEnqueue", ERROR_INVALID_PQ);
		}
	else if (NULL == pBuffer)
	{
		processPQError("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}
	else
	{
		lstFirst(&psQueue->sTheList);
		lstDeleteCurrent(&psQueue->sTheList, pBuffer, size);
	}
	return pPriority;
}

/**************************************************************************
 Function:			pqueuePeek

 Description: 	The priority and value of the first element is returned through
								the argument list

 Parameters: 		psQueue	- pointer to priority queue
 	 	 	 	 	 	 	 	pBuffer - content in element
 	 	 	 	 	 	 	 	size		- memory size of content
 	 	 	 	 	 	 	 	priority-	index of element

 Returned:			priority
 *************************************************************************/
void* pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
		 	 	 	 	 	 	 	int *priority)
{
	lstFirst(&psQueue->sTheList);
	*(int*)pBuffer = *priority; //???
	lstPeek(&psQueue->sTheList, pBuffer, size);
	//malloc space for pqelement*, point to buffer
	//FIX?
	//how to access PriorityQueueElement inside of pBuffer inside of list?
	//psQueue->sTheList->psCurrent->pData->priority;

	//So current = first
	//Element is stored in first

	//create a queue element to store priority and data value
	PriorityQueueElementPtr psTempPQElement;
	psTempPQElement = (PriorityQueueElementPtr) malloc
									 (sizeof(PriorityQueueElement));
	psTempPQElement->pData = malloc (size);

	//store appropriate arguments into new element
	memcpy (psTempPQElement->pData, pBuffer, size);
	//psNewPQElement->priority = //priorityOfCurrent???;

	return pBuffer;
}

/**************************************************************************
 Function:			pqueueChangePriority

 Description: 	The priority of all elements is increased by the amount in
 	 	 	 	 	 	 	 	change error code priority: ERROR_INVALID_PQ

 Parameters: 		psQueue	- pointer to priority queue
 	 	 	 	 	 	 	 	pBuffer - content in element
 	 	 	 	 	 	 	 	size		- memory size of content
 	 	 	 	 	 	 	 	priority-	index of element

 Returned:			priority
 *************************************************************************/
void pqueueChangePriority (PriorityQueuePtr psQueue, int change)
{
	for (int i = 0; i < lstSize(&psQueue->sTheList); i++)
	{
			//todo: priority + change
		//psQueue->//somehow access element with pointer + change;
	}
}

