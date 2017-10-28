/***************************************************************************
 *
 *  Sorting algorithms and counting work - Merge sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented mergesort
 *
 */

#ifndef __INSTRUMENTEDMS_H
#define __INSTRUMENTEDMS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedMergeSort( vector<int> & a, SortStats & stats )
{
    clock_t time_begin = clock();       // Grab presort time


	// MA TODO: Implement Merge Sort plus logging compares and moves/swaps


    clock_t time_end = clock();         // Grab time when sort complete
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}


#endif
