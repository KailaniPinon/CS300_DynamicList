/**************************************************************************
 File name: 	listDriver.c
 Author:   	 	Kailani Pinon
 Date:				10.06.2020
 Class:				CS300
 Assignment:	Generic Lists
 Purpose:			Practice implementing a singly-linked list ADT
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/list.h"
#include <limits.h>
#include <float.h>

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
 Function: 	 	printList

 Description: Prints a list of integers for debugging purposes.

 Parameters:	sTheList - the list of integers to be printed

 Returned:	 	none
 *************************************************************************/
static void printIntList (List sTheList)
{
	int i, theIntData;

	if (!lstIsEmpty (&sTheList))
	{
		printf ("         ");
		lstFirst (&sTheList);
		for (i = 0; i < lstSize (&sTheList); ++i)
		{
			lstPeek(&sTheList,  &theIntData, sizeof (int));
			lstNext (&sTheList);
			printf ("%d ", theIntData);
		}
		printf ("\n");
	}
}


void insertAndValidManyTypes(ListPtr psTheList)
{
	// int
	int maxInt = INT_MAX;

	// char
	char maxChar = CHAR_MAX;

	// double
	double maxDouble = DBL_MAX;

	// float
	float maxFloat = FLT_MAX;

	// bool
	bool bTrue = true;

	// short
	short maxShort = SHRT_MAX;

	// long long
	long long maxLongLong = LLONG_MAX;

	lstInsertAfter(psTheList, &maxInt, sizeof(int));
	lstInsertAfter(psTheList, &maxChar, sizeof(char));
	lstInsertAfter(psTheList, &maxDouble, sizeof(double));
	lstInsertAfter(psTheList, &maxFloat, sizeof(float));
	lstInsertAfter(psTheList, &bTrue, sizeof(bool));
	lstInsertAfter(psTheList, &maxShort, sizeof(short));
	lstInsertAfter(psTheList, &maxLongLong, sizeof(long long));

	lstFirst(psTheList);

	maxInt = 0;
	lstPeek(psTheList, &maxInt, sizeof(int));
	assert(INT_MAX == maxInt, "Max int correct", "Max int incorrect");
	lstNext(psTheList);

	maxChar = 0;
	lstPeek(psTheList, &maxChar, sizeof(char));
	assert(CHAR_MAX == maxChar, "Max char correct", "Max char incorrect");
	lstNext(psTheList);

	maxDouble = 0.0;
	lstPeek(psTheList, &maxDouble, sizeof(double));
	assert(DBL_MAX == maxDouble, "Max double correct", "Max double incorrect");
	lstNext(psTheList);

	maxFloat = 0.0;
	lstPeek(psTheList, &maxFloat, sizeof(float));
	assert(FLT_MAX == maxFloat, "Max float correct", "Max float incorrect");
	lstNext(psTheList);

	bTrue = false;
	lstPeek(psTheList, &bTrue, sizeof(bool));
	assert(true == bTrue, "Max TRUE correct", "Max TRUE incorrect");
	lstNext(psTheList);

	maxShort = 0;
	lstPeek(psTheList, &maxShort, sizeof(short));
	assert(SHRT_MAX == maxShort, "Max short correct", "Max short incorrect");
	lstNext(psTheList);

	maxLongLong = 0;
	lstPeek(psTheList, &maxLongLong, sizeof(long long));
	assert(LLONG_MAX == maxLongLong, "Max long long correct", "Max long long incorrect");
	lstNext(psTheList);
}

void makeBigList(ListPtr psList, int max)
{
	int i;

	// insert max nodes
	for (i = 0; i < max; ++i)
	{
		lstInsertAfter (psList, &i, sizeof (int));
	}

	assert( max == lstSize (psList), "The list size is max",
			"The list size is not max");

	assert( !lstIsEmpty (psList), "The list is NOT empty",
			"The list is empty");

	// For debugging purposes only
	 //printIntList(psList);

}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none
 Returned:	 	none
 *************************************************************************/

int main ()
{
	List sTheList;
	int i, intValue;
	int numValues;
	int count;
	char *szData = "CS300";
	char charValue;
	long long longLongValue = LLONG_MAX;

	lstLoadErrorMessages();
	puts ("Driver Start");

	// run everything twice so you call
	// create after terminate!
	for (count = 0; count < 2 ; ++count)
	{
		lstCreate (&sTheList);
		success ("List Created");

		assert( 0 == lstSize (&sTheList), "The list size is 0",
				"The list size is not 0");


		assert( lstIsEmpty (&sTheList), "The list is empty",
				"The list is not empty");

		numValues = 10;
		for (i = 0; i < numValues; ++i)
		{
			lstInsertAfter (&sTheList, &i, sizeof (int));

			if( i+1 != lstSize (&sTheList) )
			{
				assert( i+1 == lstSize (&sTheList), "The list size correctly sized",
					"The list size is wrong");
			}
		}
	//}
	//printIntList (sTheList);

		lstFirst (&sTheList);
		i = 0;
		while(lstHasCurrent(&sTheList))
		{
			lstPeek(&sTheList, &intValue, sizeof(int));
			if (i != intValue)
			{
				assert( i == intValue, "Peek returns the correct value (int)",
						"Peek return the incorrect value (int)");
			}
			intValue += 1;
			lstUpdateCurrent(&sTheList, &intValue, sizeof(int));

			intValue = 0;

			lstPeek(&sTheList, &intValue, sizeof(int));
			if (i+1 != intValue)
			{
				assert( i+1 == intValue, "Peek returns the correct value (int)",
						"Peek return the incorrect value (int)");
			}

			++i;
			lstNext (&sTheList);
		}

		assert( ! lstIsEmpty (&sTheList), "The list is NOT empty",
				"The list is empty");

		assert( numValues == lstSize (&sTheList), "The list size is 10 ",
				"The list size is not 10");

		// For debugging purposes only
		printIntList (sTheList);

		lstFirst(&sTheList);

		assert(lstHasNext(&sTheList), "The current has a next!", "The current does not have a next");

		// should be 2
		lstPeekNext(&sTheList, &intValue, sizeof(int));
		assert(2 == intValue, "PeekNext is correct", "PeekNext is wrong");

		//error here! tryin to peek improper current after delete!
		// delete the first element!
		lstDeleteCurrent(&sTheList, &intValue, sizeof(int));

		// check new first element
		lstPeek(&sTheList, &intValue, sizeof(int));
		assert(2 == intValue, "DeleteCurrent & Peek is correct", "DeleteCurrent & Peek is wrong");

		intValue = 99;
		lstInsertBefore(&sTheList, &intValue, sizeof(int));

		// check new first element
		lstPeek(&sTheList, &intValue, sizeof(int));
		assert(99 == intValue, "InsertBefore & Peek is correct", "InsertBefore & Peek is wrong");

		lstLast(&sTheList);

		// check last element
		lstPeek(&sTheList, &intValue, sizeof(int));
		assert(numValues == intValue, "Last & Peek is correct", "Last & Peek is wrong");

		lstTerminate (&sTheList);
		success ("List Terminated");

	}

	// use char data.
	lstCreate (&sTheList);
	success ("List Created");

	numValues = strlen(szData);
	for (i = 0; i < numValues; ++i)
	{
		lstInsertBefore (&sTheList, &(szData[i]), sizeof (char));
	}

	lstFirst (&sTheList);

	for (i = numValues - 1; i >= 0; --i)
	{
		lstPeek(&sTheList, &charValue, sizeof(char));
		if (szData[i] != charValue)
		{
			assert( szData[i] == charValue, "Peek returns the correct value (char)",
					"Peek return the incorrect value (char)");
		}
		lstNext (&sTheList);
	}

	lstFirst(&sTheList);

	lstUpdateCurrent(&sTheList, &longLongValue, sizeof(long long) );

	longLongValue = 0;

	lstPeek(&sTheList, &longLongValue, sizeof(long long) );

	assert( LLONG_MAX == longLongValue,"Update Current With different size", "Update Current with different size");

	lstNext(&sTheList);
	charValue = '\0';

	lstPeek(&sTheList, &charValue, sizeof(char));
	assert( szData[numValues - 2] == charValue, "Peek after update with size change returns the correct value (char)",
				"Peek after update with size change returns the correct value (char)");


	lstTerminate(&sTheList);
	lstCreate(&sTheList);

	assert( 0 == lstSize (&sTheList), "The list size is 0",
			"The list size is not 0");


	assert( lstIsEmpty (&sTheList), "The list is empty",
			"The list is not empty");
	lstTerminate(&sTheList);

	puts ("Driver End");
	return EXIT_SUCCESS;
}
