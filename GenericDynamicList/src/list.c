/**************************************************************************
 File name:		list.c
 Author:        Kailani Pinon
 Date:          10.05.2020
 Class:         CS300
 Assignment:    Dynamic List
 Purpose:       This file implements the List ADT from list.h
 *************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/list.h"

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

/**************************************************************************
 Function:			processAndPrintListError

 Description: 	Process the error code passed to this routine.
 	 	 	 	 	 	 	 	Print appropriate message according to error code.

 Parameters: 		None

 Returned:			None
 *************************************************************************/
static void processListError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszListErrors[errorCode]);

	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function:			lstLoadErrorMessages

 Description:		Loads the error message strings for the error handler to
 	 	 	 	 	 	 	 	use No error conditions. LOAD_LIST_ERRORS is a macro
								defined in the list.h header file.

 Parameters: 		None

 Returned:			None
 *************************************************************************/
void lstLoadErrorMessages ()
{
	LOAD_LIST_ERRORS
}

/**************************************************************************
 Function:			lstCreate

 Description: 	If the list can be created, then the list exists and is
 	 	 						empty; otherwise, ERROR_NO_LIST_CREATE if psList is NULL.

 Parameters: 		psList	- pointer to list

 Returned:			None
 *************************************************************************/
void lstCreate (ListPtr psList)
{
	//if psList is null, then process and print error
	//otherwise don't do anything else
	if (NULL == psList)
	{
		processListError ("lstCreate", ERROR_NO_LIST_CREATE);
	}
	//Completely new list. Set size to zero.
	psList->numElements = 0;
	psList->psCurrent = NULL;
	psList->psFirst = NULL;
	psList->psLast = NULL;
}

/**************************************************************************
 Function:			lstInsertAfter

 Description: 	If the list is not empty, insert the new element as the
 	 	 	 	 	 	 	 	successor of the current element and make the inserted
 	 	 	 	 	 	 	 	element the current element; otherwise, insert element and
 	 	 	 	 	 	 	 	make it current.
 	 	 	 	 	 	 	 	error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
 	 	 	 	 	 	 	 	ERROR_NO_CURRENT

 Parameters: 		psList	- pointer to list
 	 	 	 	 	 	 	 	pBuffer	- void pointer to buffer
 	 	 	 	 	 	 	 	size		- size requested to malloc

 Returned:			None
 *************************************************************************/
void lstInsertAfter (ListPtr psList, const void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processListError ("lstInsertAfter", ERROR_INVALID_LIST);
	}
	else if (NULL == pBuffer)
	{
		processListError ("lstInsertAfter", ERROR_NULL_PTR);
	}
	else if (!lstIsEmpty (psList) && NULL == psList->psCurrent)
	{
		processListError ("lstInsertAfter", ERROR_NO_CURRENT);
	}
	ListElementPtr psNewListElement;
	psNewListElement = (ListElementPtr) malloc (sizeof(ListElement)); //VALGRIND ERROR
	psNewListElement->pData = malloc (size);
	memcpy (psNewListElement->pData, pBuffer, size);
	psNewListElement->psNext = NULL;

	if (NULL == psList->psFirst) //if empty
	{
		psList->psCurrent = psNewListElement;
		psList->psFirst = psList->psCurrent ;
		psList->psLast = psList->psCurrent ;
	}
	else if (psList->psFirst == psList->psLast) //if only 1 item
	{
		psList->psFirst->psNext = psNewListElement;
		psList->psCurrent = psNewListElement;
		psList->psLast = psList->psCurrent;
	}
	else //if more than 2 items
	{
		if (psList->psCurrent == psList->psLast)
		{
			psList->psCurrent = psNewListElement;
			psList->psLast->psNext = psList->psCurrent;
		}
		else
		{
			psNewListElement->psNext = psList->psCurrent->psNext;
			psList->psCurrent->psNext = psNewListElement;
			psList->psCurrent = psNewListElement;
		}
	}
	psList->numElements++;

//	psNewListElement->pData = NULL;
//	free (psNewListElement->pData);
	psNewListElement = NULL;
	free (psNewListElement);
}

/**************************************************************************
 Function:			lstDeleteCurrent

 Description: 	The current element is deleted and its successor and
				  			predecessor become each others successor and predecessor. If
								the deleted element had a predecessor, then make it the new
 								current element; otherwise, make the first element current if
								it exists. The value of the deleted element is returned.
        				error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
					      ERROR_EMPTY_LIST, ERROR_NO_CURRENT

 Parameters: 		psList	- pointer to list
 	 	 	 	 	 	 	 	pBuffer	- void pointer to buffer
 	 	 	 	 	 	 	 	size		- size requested to malloc

 Returned:			pBuffer
 *************************************************************************/
void *lstDeleteCurrent (ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processListError ("lstDeleteCurrent", ERROR_INVALID_LIST);
	}
	else if (NULL == pBuffer)
	{
		processListError ("lstDeleteCurrent", ERROR_NULL_PTR);
	}
	else if (lstIsEmpty (psList))
	{
		processListError ("lstDeleteCurrent", ERROR_EMPTY_LIST);
	}
	else if (NULL == psList->psCurrent)
	{
		processListError ("lstDeleteCurrent", ERROR_NO_CURRENT);
	}
	else
	{
		printf ("current: %p\n", psList->psCurrent);

			ListElementPtr psTempListElement;
			psTempListElement = (ListElementPtr) malloc (sizeof(ListElement));
			psTempListElement = psList->psCurrent;
			psTempListElement->psNext = psList->psCurrent->psNext;
			lstFirst(psList);

			for (int i = 0; i < psList->numElements; i++)
			{
				if (psList->psCurrent->psNext != psTempListElement)
				{
				lstNext(psList);
				//for testing purposes (REMOVE)
				//if cn (current next) is not present, then at end of list
				//OR alternatively next not properly updated/implemented :(
				puts ("lstDeleteCurrent:");
				printf ("address of next: %p\naddress of temp: %p\n", psList->psCurrent->psNext, psTempListElement);
				}
				else
				{
					//walk never completing? current->nxt never matching temp? b4 list ends?
					puts ("WALK COMPLETE!");
					psList->psCurrent->psNext = psTempListElement->psNext;
					psList->psCurrent = psTempListElement->psNext;
					free (psTempListElement);
					psTempListElement = NULL;
				}
			}
		//ISSUES HERE. LEFT OFF! FIX!
	}
	return pBuffer;
}

/**************************************************************************
 Function:			lstInsertBefore

 Description: 	If the list is not empty, insert the new element as the
          			predecessor of the current element and make the inserted
          			element the current element; otherwise, insert element
          			and make it current.
          			error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
								ERROR_NO_CURRENT

 Parameters: 		psList	- pointer to list
 	 	 	 	 	 	 	 	pBuffer	- void pointer to buffer
 	 	 	 	 	 	 	 	size		- size requested to malloc

 Returned:			pBuffer
 *************************************************************************/
void lstInsertBefore (ListPtr psList, const void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processListError ("lstInsertBefore", ERROR_INVALID_LIST);
	}
	else if (NULL == pBuffer)
	{
		processListError ("lstInsertBefore", ERROR_NULL_PTR);
	}
	else if (!lstIsEmpty (psList) && NULL == psList->psCurrent)
	{
		processListError ("lstInsertBefore", ERROR_NO_CURRENT);
	}
	else
	{
		ListElementPtr psTempListElement;
		psTempListElement = (ListElementPtr) malloc (sizeof(ListElement));
		psTempListElement->pData = malloc (size);
		memcpy (psTempListElement->pData, pBuffer, size);
		psTempListElement->psNext = psList->psCurrent;

		if (psList->psFirst != psList->psCurrent)
		{
			ListElementPtr psOriginalListCurrent = (ListElementPtr) malloc
														(sizeof(ListElementPtr));
			psOriginalListCurrent->pData = malloc (size);
			memcpy (psOriginalListCurrent->pData, psList->psCurrent->pData,
					size);
			psOriginalListCurrent = psList->psCurrent;
			//set current to first
			lstFirst (psList);
			//move along list until current->next = intialCurrentTemp
			int counter = 0;
			do
			{
				lstNext (psList);
				counter++;
			} while (psList->psCurrent->psNext != psOriginalListCurrent
					&& counter < psList->numElements);

			psList->psCurrent->psNext = psTempListElement;
			psList->psCurrent = psTempListElement;
		}
		else if (psList->psFirst == psList->psCurrent) //if first == current
		{
			psTempListElement->psNext = psList->psFirst;
			psList->psCurrent = psTempListElement;
		}
	}
	psList->numElements++;
}

/**************************************************************************
 Function:			lstUpdateCurrent

 Description: 	The value of pBuffer is copied into the current element
            		error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
					      ERROR_EMPTY_LIST, ERROR_NO_CURRENT

 Parameters: 		psList	- pointer to list
 	 	 	 	 	 	 	 	pBuffer	- void pointer to buffer
 	 	 	 	 	 	 	 	size		- size requested to malloc

 Returned:			None
 *************************************************************************/
void lstUpdateCurrent (ListPtr psList, const void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processListError ("lstUpdateCurrent", ERROR_INVALID_LIST);
	}
	else if (NULL == pBuffer)
	{
		processListError ("lstUpdateCurrent", ERROR_NULL_PTR);
	}
	else if (lstIsEmpty (psList))
	{
		processListError ("lstUpdateCurrent", ERROR_EMPTY_LIST);
	}
	else if (!lstIsEmpty (psList) && NULL == psList->psCurrent)
	{
		processListError ("lstUpdateCurrent", ERROR_NO_CURRENT);
	}
	ListElementPtr psTempListElement;
	psTempListElement = (ListElementPtr) malloc (sizeof(ListElement));
	psTempListElement->pData = malloc (size);
	memcpy (psTempListElement->pData, pBuffer, size);

	psList->psCurrent = psTempListElement;

	free (psTempListElement->pData);
	psTempListElement->pData = NULL;
	free (psTempListElement);
	psTempListElement = NULL;
}

/**************************************************************************
 Function:			lstReverse

 Description: 	he value of pBuffer is copied into the current element
            		error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
			          ERROR_EMPTY_LIST, ERROR_NO_CURRENT
 Parameters: 		psList	- pointer to list

 Returned:			None
 *************************************************************************/
void lstReverse (ListPtr psList)
{
	//todo!
	//incomplete
	//use insert before
}

/**************************************************************************
 Function:			lstTerminate

 Description: 	If the list can be terminated, then the list no longer
 	 	 	 	 	 	 	 	exists and is empty; otherwise, ERROR_NO_LIST_TERMINATE

 Parameters: 		psList	- pointer to list

 Returned:			None
 *************************************************************************/
void lstTerminate (ListPtr psList)
{
	if (NULL == psList)
	{
		processListError ("lstTerminate", ERROR_NO_LIST_TERMINATE);
	}
//	psList->psCurrent = NULL;
//	free (psList->psCurrent);
//	psList->psFirst = NULL;
//	free (psList->psFirst);
//	psList->psLast = NULL;
//	free (psList->psLast);

	//can't be current? if current, then why not also first and last?
	//not pData. Similar to reasoning from previous line? Then release
	//for first, last, and current.
	//not next. Same reasoning above?

	//note: only 2 frees go here?
	free (psList);
	//free (psList);
	//Do we literally mean a second psList free for some reason? Why
	psList = NULL;
}

/**************************************************************************
 Function:			lstSize

 Description: 	Returns the number of elements in the list
 	 	 	 	 	 	 		error code priority: ERROR_INVALID_LIST

 Parameters: 		psList	- pointer to list

 Returned:			size (length) of the list
 *************************************************************************/
int lstSize (const ListPtr psList)
{
	if (NULL == psList)
	{
		processListError ("1stSize", ERROR_INVALID_LIST);
	}
	return psList->numElements;
}

/**************************************************************************
 Function:			lstIsEmpty

 Description: 	If list is empty, return true; otherwise, return false.
								error code priority: ERROR_INVALID_LIST

 Parameters: 		psList	- pointer to list

 Returned:			isEmpty - determines if psList is NULL or not
 *************************************************************************/
bool lstIsEmpty (const ListPtr psList)
{
	bool isEmpty = false;
	const int EMPTY_LIST = 0;
	if (NULL == psList)
	{
		processListError ("lstIsEmpty", ERROR_INVALID_LIST);
	}
	else if (EMPTY_LIST == psList->numElements)
	{
		isEmpty = true;
	}
	return isEmpty;
}

/**************************************************************************
 Function:			lstFirst

 Description: 	If the list is not empty, current is changed to the first
 	 	 	 	 	 	 	 	element error code priority: ERROR_INVALID_LIST,
 	 	 	 	 	 	 	 	ERROR_EMPTY_LIST

 Parameters: 		psList	- pointer to list

 Returned:			None
 *************************************************************************/
void lstFirst (ListPtr psList)
{
	if (NULL == psList)
	{
		processListError ("lstFirst", ERROR_INVALID_LIST);
	}
	else if (lstIsEmpty (psList))
	{
		processListError ("lstFirst", ERROR_EMPTY_LIST);
	}
	//not adding anything new: just setting address of current to first
	psList->psCurrent = psList->psFirst;
}

/**************************************************************************
 Function:			lstNext

 Description: 	If the list is not empty, current is changed to the
								successor of the current element
           	 	 	error code priority: ERROR_INVALID_LIST,
								ERROR_EMPTY_LIST, ERROR_NO_CURRENT

 Parameters: 		psList	- pointer to list

 Returned:			None
 *************************************************************************/
void lstNext (ListPtr psList)
{
	if (NULL == psList)
	{
		processListError ("lstNext", ERROR_INVALID_LIST);
	}
	else if (lstIsEmpty (psList))
	{
		processListError ("lstNext", ERROR_EMPTY_LIST);
	}
	else if (NULL == psList->psCurrent)
	{
		processListError ("lstNext", ERROR_NO_CURRENT);
	}
	else
	{
		if (NULL != psList->psFirst && psList->psFirst != psList->psLast
				&& psList->psCurrent != psList->psLast) //if more than 1 item
		{
			psList->psCurrent = psList->psCurrent->psNext;
		}
	}
}

/**************************************************************************
 Function:			lstLast

 Description: 	If the list is not empty, current is changed to last
								if it exists
          			error code priority: ERROR_INVALID_LIST,
								ERROR_EMPTY_LIST

 Parameters: 		psList	- pointer to list

 Returned:			None
 *************************************************************************/
void lstLast (ListPtr psList)
{
	if (NULL == psList)
	{
		processListError ("lstLast", ERROR_INVALID_LIST);
	}
	if (lstIsEmpty (psList))
	{
		processListError ("lastLast", ERROR_EMPTY_LIST);
	}
	psList->psCurrent = psList->psLast;
}

/**************************************************************************
 Function:			lstPeek

 Description: 	The value of the current element is returned
 	 	 	 	IMPORTANT: Do not change current
 	 	 	 	error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
 	 	 	 	ERROR_EMPTY_LIST, ERROR_NO_CURRENT

 Parameters: 		psList	- pointer to list
 	 	 	 	 	 	 	 	pBuffer	- pointer to content stored in current node
								size		- size requested to malloc

 Returned:			pBuffer
 *************************************************************************/
void *lstPeek (const ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processListError ("lstPeek", ERROR_INVALID_LIST);
	}
	else if (NULL == pBuffer)
	{
		processListError ("lstPeek", ERROR_NULL_PTR);
	}
	else if (lstIsEmpty (psList))
	{
		processListError ("lstPeek", ERROR_EMPTY_LIST);
	}
	else if (!lstIsEmpty (psList) && NULL == psList->psCurrent)
	{
		processListError ("lstPeek", ERROR_NO_CURRENT);
	}
	else
	{
		memcpy (pBuffer, psList->psCurrent->pData, size);
	}
	return pBuffer;
}

/**************************************************************************
 Function:			lstPeekNext

 Description: 	The value of the current element is returned
 	 	 	 	 	 	 	 	IMPORTANT: Do not change current
 	 	 	 	 	 	 	 	error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
								ERROR_EMPTY_LIST, ERROR_NO_CURRENT

 Parameters: 		psList	- pointer to list
 	 	 	 	 	 	 		pBuffer - pointer to content stored in current node
 	 	 	 	 	 	 		size		- size requested to malloc

 Returned:			pBuffer
 *************************************************************************/
void *lstPeekNext (const ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processListError ("lstPeekNext", ERROR_INVALID_LIST);
	}
	if (NULL == pBuffer)
	{
		processListError ("lstPeekNext", ERROR_NULL_PTR);
	}
	if (lstIsEmpty (psList))
	{
		processListError ("lstPeekNext", ERROR_EMPTY_LIST);
	}
	if (NULL == psList->psCurrent)
	{
		processListError ("lstPeekNext", ERROR_NO_CURRENT);
	}
	if (NULL == psList->psCurrent->psNext)
	{
		processListError ("lstPeekNext", ERROR_NO_NEXT);
	}
	//pBuffer is just an address? And we want the actual content?
	memcpy (&pBuffer, psList->psCurrent->psNext->pData, size);
	//alternatively:
	//tried to return ...->psNext->pData, but that doesn't update pBuffer
	//return psList->psCurrent->psNext->pData;
	return pBuffer;
}

/**************************************************************************
 Function:			lstHasCurrent

 Description: 	Returns true if the current node is not NULL; otherwise,
 	 	 	 	 	 	 	 	false is returned

 Parameters: 		psList	- pointer to list

 Returned:			pBuffer
 *************************************************************************/
bool lstHasCurrent (const ListPtr psList)
{
	bool isCurrentExisting;

	if (NULL == psList)
	{
		processListError ("lstHasCurrent", ERROR_INVALID_LIST);
	}
	if (NULL != psList->psCurrent)
	{
		isCurrentExisting = true;
	}
	else
	{
		isCurrentExisting = false;
	}
	return isCurrentExisting;
}

/**************************************************************************
 Function:			lstHasNext

 Description: 	Returns true if the current node is not NULL; otherwise,
 	 	 	 	 	 	 	 	false is returned

 Parameters: 		psList	- pointer to list

 Returned:			pBuffer
 *************************************************************************/
bool lstHasNext (const ListPtr psList)
{
	bool isNextExisting;
	if (NULL == psList)
	{
		processListError ("lstHasNext", ERROR_INVALID_LIST);
	}
	if (NULL == psList->psCurrent->psNext)
	{
		isNextExisting = false;
	}
	else
	{
		isNextExisting = true;
	}
	return isNextExisting;
}
