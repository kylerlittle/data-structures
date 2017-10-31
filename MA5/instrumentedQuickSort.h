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

// Return index of pivot
int medianOfThree(vector<int> &a, int left, int right, SortStats & stats) {
  int middle = (left + right) / 2;
  if (a[left] < a[right] && a[left] > a[middle]) {  // then left is median
    stats.compares += 1;        // had to do two comparisons to get to this point, but I'm going to call it one
    return left;
  } else if (a[right] < a[left] && a[right] > a[middle]) {  // then right is median
    stats.compares += 2;     // had to do at least 3 comparisons to get to this point (possibly 4 if no short circuiting), but call it 2
    return right;
  } else {
    stats.compares += 2;   // had to do at least 3 comparisons to get to this point (possibly 4 if no short circuiting), but call it 2
    return middle;   // otherwise, middle is median
  }
}

/*
 * This quicksort method uses the partitioning strategy to do the sort in place
 * MedianOfThree is used to find the pivot point
 * left is the leftmost index of the subarray & right is the rightmost index of the subarray
 */
void quickSort(vector<int> &a, int left, int right, SortStats & stats) {
  if (left < right) {     // continue recursing while we have greater than one element
    int pivotIndex = medianOfThree(a, left, right, stats), pivot = a[pivotIndex];
    swap(a[pivotIndex], a[right]); // move pivot to end position temporarily
    ++stats.moves;
    
    // Now partition the subarray into items smaller than pivot & larger
    int i = left, j = right - 1;
    bool stillPartitioning = true;
    while (stillPartitioning) {
      while (a[i] < pivot) { ++i; }
      while (a[j] > pivot) { --j; }
      if (++stats.compares && i < j) { // then we're not done partitioning
	swap(a[i], a[j]);   // move element larger than pivot to right & pivot smaller than pivot to left
	++stats.moves;
      } else {
	stillPartitioning = false;
      }
    }
    swap(a[i], a[right]);      // move pivot back to in between the two partitions
    ++stats.moves;
    quickSort(a, left, i - 1, stats);
    quickSort(a, i + 1, right, stats);
  }
}

void instrumentedQuickSort( vector<int> & a, SortStats & stats )
{
  clock_t time_begin = clock();       // Grab time before the sort
    
  // MA TODO: implement quicksort and track compares + moves
  quickSort(a, 0, a.size() - 1, stats);
  
  clock_t time_end = clock();         // Grab time after the sort
  stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
