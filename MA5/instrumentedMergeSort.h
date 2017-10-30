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

// Merges two sorted lists
void merge(vector<int> & a, vector<int> tmp, int leftBegin, int rightBegin, int rightEnd, SortStats & stats) {
  // Since center + 1 is passed in as rightBegin, we take leftEnd to be rightBegin - 1;
  int leftEnd = rightBegin - 1;        // now [leftBegin, leftEnd] U [rightBegin, rightEnd] captures all of a
  // +1 ensures we're counting the number of elements rather than different bw right & left
  int numItemsBeingMerged = rightEnd - leftBegin + 1, i;

  // Go until we've reached the end of one side
  for (i = leftBegin; ++stats.compares && leftBegin <= leftEnd && rightBegin <= rightEnd; ++i) {  
    if (a[leftBegin] <= a[rightBegin]) {        // i.e. left item is smaller
      tmp[i] = a[leftBegin];      // Insert 
      ++leftBegin;    // advance iterator on left side
    } else {
      tmp[i] = a[rightBegin];
      ++rightBegin;   // advance iterator on right side
    }
  }

  // Now, exactly one of the two halves has remaining elements
  while (leftBegin <= leftEnd) {
    tmp[i] = a[leftBegin];
    ++i; ++leftBegin;    // Advance iterators
  }
  while (rightBegin <= rightEnd) {
    tmp[i] = a[rightBegin];
    ++i; ++rightBegin;
  }

  // Now, all we need to do is move tmp back to a, so we can sort again on the next recursive call
  for (int counter = 0; counter < numItemsBeingMerged; ++counter, --rightEnd) {
    a[rightEnd] = move(tmp[rightEnd]);
  }
  stats.moves += (2 * numItemsBeingMerged);  // Each call on merge requires moving numItemsBeingMerged twice 
}

void mergeSort(vector<int> & a, vector<int> & tmp, int left, int right, SortStats & stats) {
  if (left < right) {
    int center = (left + right) / 2;     // find splitting point of a; if odd,
    mergeSort(a, tmp, left, center, stats);     // sort left half
    mergeSort(a, tmp, center + 1, right, stats);        // sort right half
    merge(a, tmp, left, center + 1, right, stats);      // merge the two halves together
  }
}

void instrumentedMergeSort( vector<int> & a, SortStats & stats )
{
    clock_t time_begin = clock();       // Grab presort time

    // MA TODO: Implement Merge Sort plus logging compares and moves/swaps
    vector<int> tmp(a.size());
    mergeSort(a, tmp, 0, a.size()-1, stats);

    clock_t time_end = clock();         // Grab time when sort complete
    stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}


#endif
