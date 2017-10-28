/***************************************************************************
 *
 *  Sorting algorithms and counting work - Quicksort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented quicksort
 *
 */

#ifndef __INSTRUMENTEDQS_H
#define __INSTRUMENTEDQS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedQuickSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();       // Grab time before the sort


    // MA TODO: implement quicksort and track compares + moves


	clock_t time_end = clock();         // Grab time after the sort
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
