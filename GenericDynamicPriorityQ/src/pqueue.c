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
	printf ("Function: %s %p \n ", pszFunctionName, gszPQErrors[errorCode]);

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
		//ListPtr myList;
		lstCreate(&psQueue->sTheList);
		//lstLoadErrorMessages();
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
		//lstTerminate(psQueue->sTheList));
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
		processPQError("pqueueSize", ERROR_INVALID_PQ);
	}
	return lstSize(&psQueue->sTheList);
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
		processPQError("pqueueIsEmpty", ERROR_INVALID_PQ);
	}
	return false /*lstIsEmpty(psQueue->sTheList)*/;
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
void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority)
{
	if (NULL == psQueue)
		{
			processPQError("pqueueEnqueue", ERROR_INVALID_PQ);
		}
	else if (NULL == pBuffer)
	{
		processPQError("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}
	//else if (SOME_MAX??? <= lstSize(psQueue->sTheList)
	//{
	//	processPQError("pqueueEnqueue", ERROR_FULL_PQ);
	//}
	else
	{

	}
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
	//else if (SOME_MAX??? <= lstSize(psQueue->sTheList)
	//{
	//	processPQError("pqueueEnqueue", ERROR_FULL_PQ);
	//}
	//todo: double check make file - not linking correctly
	else
	{

	}
	return pBuffer;
}

//todo: Dequeue (NOT DONE), Peek, ChangePriority
