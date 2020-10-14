/**************************************************************************
 File name:			pqueuedriver.c
 Author:        Kailani Pinon
 Date:          10.09.2020
 Class:         CS300
 Assignment:    Dynamic Priority Queue List
 Purpose:       This file ... todo: add purpose
 *************************************************************************/
#include "../../GenericDynamicList/include/list.h"
#include "../include/pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//todo: ADD VALGRIND
//todo: copy/paste SUCCESS, FAILURE, and ASSERT functions
//and make sure asserts adequately describe what I'm testing!!!

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

//todo: documentation for main
int main()
{
	assert (10 > 0, "test works (10 > 0)", "test failed (10>0)");

	puts("TEST: END.");
	return EXIT_SUCCESS;
}
