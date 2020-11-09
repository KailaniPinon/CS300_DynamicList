/**************************************************************************
 File name: 	airport.h
 Author:   	 	Kailani Pinon
 Date:				08.26.2020
 Class:				CS300
 Assignment:	
 Purpose:		
 *************************************************************************/
#ifndef INCLUDE_AIRPORT_H_
#define INCLUDE_AIRPORT_H_
#include "../../GenericDynamicList/include/list.h"
#include "../../GenericDynamicPriorityQ/include/pqueue.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
//makefile

//*************************************************************************
// Constants
//*************************************************************************
#define NO_FUEL 0 //all fuel depleted

//*************************************************************************
// User-defined types
//*************************************************************************
typedef struct Airplane
{
	int fuelRemaining;
	int tickPriority;
	bool bHasFuel;
	bool bIsGrounded;

} Airplane;

typedef struct Runway
{
		int priority = 0;
		bool bIsOccupied;
		bool bCanTakeOff;
} Runway;

typedef struct Airspace
{
		//pq list - to store data for each turn/tick/round
		PriorityQueue airspace;
		bool bCanTakeOff;
} Airspace;

typedef struct outputPerTick
{
		int totalTime;
		int totalTakeoffs;
		int planesLanding;
		int fuelRemaining;
		int crashes;
		int queueTakeoff;
		int lengthsLanding;

} outputPerTick;

typedef struct outputTotal
{
		//const int MAX_TICKS = 10000
		//outputPerTick[MAX_TICKS] outputTotalTicks;
}outputTotal;

void landAirplane (Airplane);
//results:	Airplane element assigned to a runway

int calcAverage (int); //used to find average for output

#endif /* INCLUDE_AIRPORT_H_ */
