/***************************************************************************
 *
 *  Sorting algorithms and counting work - Insertion sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented insertionsort
 *
 */

#ifndef __INSTRUMENTEDIS_H
#define __INSTRUMENTEDIS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedInsertionSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();           // Grab starting time before sort


	// MA TODO: implement insertion sort plus logging compares, moves/swaps
	for (int i = 0; i < a.size(); ++i) {
	  int j = i;
	  while (j > 0 && ++stats.compares && a.at(j-1) > a.at(j)) {  // shortcircuit if ith item becomes the first item
	    ++stats.moves;
	    swap(a.at(j-1), a.at(j));  // continue swapping while ith item isn't sorted (or at beginning, which is sorted)
	    --j;
	  }
	}

	clock_t time_end = clock();             // Grab ending time after sort
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
