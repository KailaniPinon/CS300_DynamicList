/**************************************************************************
 File name:			list.c
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

//*************************************************************************
// Allocation and Deallocation
//*************************************************************************
/**************************************************************************
 Function:			lstCreate

 Description: 	If the list can be created, then the list exists and is
 	 	 						empty; otherwise, ERROR_NO_LIST_CREATE if psList is NULL.

 Parameters: 		psList	- pointer to list

 Returned:			None
 *************************************************************************/
void lstCreate (ListPtr psList)
{
	if (NULL == psList)
	{
		processListError ("lstCreate", ERROR_NO_LIST_CREATE);
	}
	else
	{
		//INITIALIZE (SPECIFY) VALUES IN LIST
		//set list as empty (0)
		psList->numElements = 0;		//line 73 list.h
		//set nodes to NULL
		psList->psCurrent = NULL; 	//line 72 list.h
		psList->psFirst = NULL;			//line 71 list.h
		psList->psLast = NULL;			//line 70 list.h
	}
}

/**************************************************************************
 Function:			lstTerminate

 Description: 	If the list can be terminated, then the list no longer
 	 	 	 	 	 	 	 	exists and is empty; Free() data	pointed	to	void* and
 	 	 	 	 	 	 	 	the	ListElements. Otherwise: ERROR_NO_LIST_TERMINATE.

 Parameters: 		psList	- pointer to list

 Returned:			None
 *************************************************************************/
void lstTerminate (ListPtr psList)
{
	if (NULL == psList)
	{
		processListError ("lstTerminate", ERROR_NO_LIST_TERMINATE);
	}
	//use placeholder to assist with pointing at addresses of items
	//ListElementPtr psTempElement;


	//walk through the list, removing all items
	while (/*NULL != psTempElement &&*/ !lstIsEmpty(psList))
	{
		//start from the first item
		//psTempElement = psList->psFirst;
		//psList->psCurrent = psList->psFirst;
		lstFirst(psList);

		//if (NULL != psList->psFirst->psNext)

//VAAALGRIIIIND todo:fix
		//free (psTempElement->pData); //valgrind error, but KEEP
		//free (psTempElement);
				//ERROR HERE WHEN BEING ACCESSED BY PQ
		free (psList->psCurrent->pData);
		free (psList->psCurrent);
		psList->psCurrent->pData = NULL;
		psList->psCurrent = NULL;
		//psTempElement->pData = NULL;
		//psTempElement = NULL;
		//todo: remove old temp logic, using current directly instead

		if (lstHasNext(psList))
		{
			//psList->psFirst = psList->psFirst->psNext;
			lstNext(psList);
		}
		psList->numElements--;
	}
	psList->psCurrent = NULL;
	psList->psFirst = NULL;
	psList->psLast = NULL;
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

//*************************************************************************
// Checking number of elements in list
//*************************************************************************
/**************************************************************************
 Function:			lstSize

 Description: 	Returns the number of elements in the list
 	 	 	 	 	 	 		error code priority: ERROR_INVALID_LIST

 Parameters: 		psList	- pointer to list

 Returned:			psList->numElements
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

 Returned:			bIsEmpty - determines any items are present in the list
 *************************************************************************/
bool lstIsEmpty (const ListPtr psList)
{
	const int EMPTY_LIST = 0;
	bool bIsEmpty;

	if (NULL == psList)
	{
		processListError ("lstIsEmpty", ERROR_INVALID_LIST);
	}
	else if (EMPTY_LIST == psList->numElements)
	{
		bIsEmpty = true;
	}
	else
	{
		bIsEmpty = false;
	}
	return bIsEmpty;
}

//*************************************************************************
//												List Testing
//*************************************************************************
/**************************************************************************
 Function:			lstHasCurrent

 Description: 	Returns true if the current node is not NULL; otherwise,
 	 	 	 	 	 	 	 	false is returned

 Parameters: 		psList	- pointer to list

 Returned:			bDoesCurrentExist
 *************************************************************************/
bool lstHasCurrent (const ListPtr psList)
{
	bool bDoesCurrentExist;

	if (NULL == psList)
	{
		processListError ("lstHasCurrent", ERROR_INVALID_LIST);
	}
	if (NULL != psList->psCurrent)
	{
		bDoesCurrentExist = true;
	}
	else
	{
		bDoesCurrentExist = false;
	}
	return bDoesCurrentExist;
}

/**************************************************************************
 Function:			lstHasNext

 Description: 	Returns true if the current node has a successor;
 	 	 	 	 	 	 	 	otherwise, false is returned

 Parameters: 		psList	- pointer to list

 Returned:			bDoesNextExist
 *************************************************************************/
bool lstHasNext (const ListPtr psList)
{
	bool bDoesNextExist;

	if (NULL == psList)
	{
		processListError ("lstHasNext", ERROR_INVALID_LIST);
	}
	else if (NULL != psList->psCurrent)
	{
		//if (NULL != psList->psCurrent->psNext)
		if (psList->psCurrent != psList->psLast)
		{
			bDoesNextExist = true;
		}
	}
	else
	{
		bDoesNextExist = false;
	}
	return bDoesNextExist;
}

//*************************************************************************
//													Peek Operations
//*************************************************************************
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

 Description: 	The data value of current's successor is returned
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
	else if (NULL == pBuffer)
	{
		processListError ("lstPeekNext", ERROR_NULL_PTR);
	}
	else if (lstIsEmpty (psList))
	{
		processListError ("lstPeekNext", ERROR_EMPTY_LIST);
	}
	else if (NULL == psList->psCurrent)
	{
		processListError ("lstPeekNext", ERROR_NO_CURRENT);
	}
	else if (NULL == psList->psCurrent->psNext)
	{
		processListError ("lstPeekNext", ERROR_NO_NEXT);
	}
	else
	{
		memcpy (pBuffer, psList->psCurrent->psNext->pData, size);
	}
	return pBuffer;
}

//*************************************************************************
//							Updating current
//*************************************************************************
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
	//puts ("Current switched to first!");
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
		if (psList->psCurrent != psList->psLast)
		{
			psList->psCurrent = psList->psCurrent->psNext;
			//puts ("Current switched to next!");
		}
		else
		{
			psList->psCurrent->psNext = NULL;
			psList->psCurrent = NULL;
			//printf ("Whoopsies! Current extended past Last. Current is now NULL.\n"); //QUIT?
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
	else if (true == lstIsEmpty (psList))
	{
		processListError ("lastLast", ERROR_EMPTY_LIST);
	}
	else
	{
		psList->psCurrent = psList->psLast;
		//puts ("Current switched to last!");
	}
}

//*************************************************************************
//									Insertion, Deletion, and Updating
//*************************************************************************
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
	else
	{
		//new space for brand new element to insert
		ListElementPtr psNewElement;
		psNewElement = (ListElementPtr) malloc (sizeof(*psNewElement));
		psNewElement->pData = malloc (size);
		memcpy (psNewElement->pData, pBuffer, size);
		psNewElement->psNext = NULL;

//		ListElement sNewElement;
//		//sNewElement = *psTempElement;
//		sNewElement.psNext = psTempElement->psNext;
//		sNewElement.pData = psTempElement->pData;
//		free (psTempElement->pData);
//		free (psTempElement);

		if (!lstHasCurrent (psList)) //if empty
		{
			//psList->psCurrent = psList->psFirst = psList->psLast = &sNewElement;
			psList->psCurrent = psList->psFirst = psList->psLast = psNewElement;
			//puts ("INSERTING FIRST ITEM INTO LIST!");
		}
		else if (psList->psFirst == psList->psLast) //if only 1 item
		{
				//point first to new item
				//set current and last to new item
				//psList->psFirst->psNext = psList->psLast = psList->psCurrent = &sNewElement;
				psList->psFirst->psNext = psList->psLast = psList->psCurrent = psNewElement;
				//puts ("INSERTING 2ND ITEM INTO LIST!");
		}
		else //if more than 1 item and starting at end
		{
			if (psList->psCurrent == psList->psLast && psList->psCurrent != psList->psFirst)
			{
				//point current to new item
				//set current and last to new item
				//psList->psCurrent->psNext = &sNewElement;
				psList->psCurrent->psNext = psNewElement;
				//psList->psCurrent = psList->psLast = &sNewElement;
				psList->psCurrent = psList->psLast = psNewElement;
				//first untouched
			}
			else if (psList->psCurrent == psList->psFirst)
			{
				//sNewElement.psNext = psList->psFirst->psNext;		//set second to next (attempt 2)
				psNewElement->psNext = psList->psFirst->psNext;	//set second to next
				//psList->psFirst->psNext = &sNewElement;						//set next to (attempt 2)
				psList->psFirst->psNext = psNewElement;					//set next to
				//psList->psCurrent = &sNewElement;								//attempt 2
				psList->psCurrent = psNewElement;
			}
			else //if starting in middle
			{
				//sNewElement.psNext = psList->psCurrent->psNext;
				psNewElement->psNext = psList->psCurrent->psNext;
				//psList->psCurrent->psNext = &sNewElement;
				psList->psCurrent->psNext = psNewElement;
				//psList->psCurrent = &sNewElement;
				psList->psCurrent = psNewElement;
			}
		}
		psList->numElements++;
	}
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
		if (NULL != psList->psCurrent)
		{
			ListElementPtr psTempListElement;
			psTempListElement = (ListElementPtr) malloc (sizeof(ListElement));
			psTempListElement = psList->psCurrent;
			psTempListElement->psNext = psList->psCurrent->psNext;
			//lstFirst (psList);

			//puts ("ATTEMPTING TO REMOVE CURRENT");

			if (psList->psFirst == psList->psLast) //if only 1 item
			{
				lstTerminate (psList);
			}
			else if (psList->psCurrent == psList->psLast
					&& psList->psLast != psList->psFirst) //if at end of list
			{
				//use placeholder to assist with pointing at addresses of items
				//ListElementPtr psTempElement;
				psTempListElement = psList->psLast;

				//start from the first item
				lstFirst (psList);

				//walk to element that precedes last
				do
				{
					lstNext (psList);
				} while (psList->psCurrent->psNext != NULL);

				//set last to current
				psList->psLast = psList->psCurrent;
			}
			else if (psList->psCurrent == psList->psFirst &&
			NULL != psList->psFirst->psNext) //if first->next exists
			{
				//use placeholder to assist with pointing at addresses of items
				//ListElementPtr psTempElement;
				psTempListElement = psList->psFirst;

				//move to item proceeding first
				lstNext (psList);
				psList->psFirst = psList->psCurrent;
			}
			else //if starting in middle
			{
				//use placeholder to assist with pointing at addresses of items
				//ListElementPtr psTempElement;
				psTempListElement = psList->psCurrent;

				//walk to element that precedes last, but start from beginning
				lstFirst (psList);

				do
				{
					lstNext (psList);
				} while (psList->psCurrent->psNext != psTempListElement);

				//connect current's preceding element with current's proceeding element
				psList->psCurrent->psNext = psTempListElement->psNext;

				//safeguard and erase address associations with initial last
				free (psTempListElement->pData);
				free (psTempListElement);
				psTempListElement->pData = NULL;
				psTempListElement = NULL;
			}
		}
		--(psList->numElements);
	}
	return pBuffer;
}
//todo: figure out why freeing doesn't resolve malloc issues??? but down to 4 valgrind errors :o

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
	else if (lstIsEmpty (psList) && NULL == psList)
	{
		processListError ("lstInsertBefore", ERROR_NO_CURRENT);
	}
	else
	{
		//new space for brand new element to insert
		ListElementPtr psNewListElement;
		psNewListElement = (ListElementPtr) malloc (sizeof(ListElement));
		psNewListElement->pData = malloc (size);
		memcpy (psNewListElement->pData, pBuffer, size);

		if (!lstHasCurrent (psList)) //if empty
		{
			psList->psCurrent = psList->psFirst = psList->psLast = psNewListElement;
			//puts ("INSERTING FIRST ITEM INTO LIST!");
		}
		else if (psList->psFirst == psList->psLast && psList->psCurrent != psList->psLast)
		//if only 1 item
		{
			//point new item to first
			//set current and last to new item
			psNewListElement->psNext = psList->psLast = psList->psCurrent =
					psList->psFirst;
			psList->psFirst = psNewListElement;
			//puts ("INSERTING 2ND ITEM INTO LIST!");
		}
		else //if more than 1 items
		{
			if (psList->psCurrent == psList->psLast && psList->psCurrent != psList->psFirst)
			{
				psNewListElement->psNext = psList->psLast;

				//walk thru list and stop at element preceding last
				//in order to connect it to the new element
				lstFirst(psList);
				do
				{
					lstNext(psList);
				} while (psList->psCurrent->psNext != psList->psLast);

				//connect next to new element
				psList->psCurrent->psNext = psNewListElement;
			}
			else if (psList->psCurrent == psList->psFirst)
			{
				psNewListElement->psNext = psList->psFirst;
				psList->psFirst = psNewListElement;
			}
			else //if starting in middle
			{
				//set new's next to current
				psNewListElement->psNext = psList->psCurrent;

				//walk thru list and stop at element preceding current
				do
				{
					lstNext(psList);
				} while (psList->psCurrent->psNext != psNewListElement->psNext);

				//reroute current's next to new element
				psList->psCurrent->psNext = psNewListElement;
			}
		}
			psList->psCurrent = psNewListElement;
			(psList->numElements)++;

			//free (psNewListElement->pData);
			//free (psNewListElement);
	}
}

/**************************************************************************
 Function:			lstUpdateCurrent

 Description: 	The value of pBuffer is copied into the current element.
 	 	 	 	 	 	 	 	A new value writes over previous data information.
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
	else
	{
		//free current data information that we want to overwrite
		//free (psList->psCurrent->pData); //valgrind errors: invalid read of size 2

		//re-allocate space for new pData
		//ListElementPtr psTempListElement;
		//psTempListElement = (ListElementPtr) malloc (sizeof(ListElement)); //valgrind error 400 bytes lost
		//psTempListElement->pData = malloc (size);
		//memcpy (psTempListElement->pData, pBuffer, size);

		//valgrind update
		//instead of using temp, just replaced current directly (no need to allocate new space for temp)
		psList->psCurrent->pData = malloc (size);
		memcpy (psList->psCurrent->pData, pBuffer, size);

		//set pData to new element
		//memcpy(psList->psCurrent->pData, psTempListElement->pData, size); //valgrind error invalid write of size 2
	}

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

//todo: fix valgrind errors if possible
//todo: fix makefile on pqueuedriver
//todo: FINISH Q and PQ!!!
//todo: FINISH AIRPORT!
//46 with 56.25% weight

