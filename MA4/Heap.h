//***************************************************************************//
//**
//**  Simple Heap implementation - With solution
//**    Copyright 2016 - Aaron S. Crandall
//**
//**
//***************************************************************************//

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <stdexcept>      // std::out_of_range
#include <math.h>         // pow()
using namespace std;


template<typename T>
class Heap
{

private:
	vector<T> _items;    // Main vector of elements for heap storage

	/**
	 *  Used to take unsorted data and heapify it
	 */
	void buildHeap()
	{
		for (unsigned int i = _items.size() / 2; i >= 0; i--)
		{
			percolateDown(i);
		}
	}

/*********************************************************************/
/********************* Microassignment zone *************************/

	/**
	 *  Percolates the item specified at by index down 
     *   into its proper location within a heap.
	 *  Used for dequeue operations and array to heap conversions
	 *  MA TODO: Implement percolateDown!
	 */
	void percolateDown(int index)
	{

	}

	/**
	 *  Percolate up from a given index to fix heap property
	 *  Used in inserting new nodes into the heap
	 *   MA TODO: Implement percolateUp
	 */
	void percolateUp( int current_position )
	{

	}

/************************** Microassigment zone DONE *********************/

public:
	/**
	 *  Default empty constructor
	 */
	Heap()
	{
	}

	/**
	 *  Constructor with a vector of elements
	 */
	Heap(const vector<T> &unsorted)
	{
		for (unsigned int i = 0; i < unsorted.size(); i++)
		{
			_items.push_back(unsorted[i]);
		}
		buildHeap();
	}

	/**
	 *  Adds a new item to the heap
	 */
	void insert(T item)
	{
		unsigned int current_position = size(); // Get index location
		_items.push_back(item);                 // Add data to end
		percolateUp( current_position );        // Adjust up, as needed
	}


	/** 
	 * Returns the top-most item in our heap without 
	 *  actually removing the item from the heap
	 */
	T& getFirst()
	{
		if( size() > 0 )
			return _items[0];
		else
			throw std::out_of_range("No elements in Heap.");
	}


	/**
	 *  Removes minimum value from heap and returns it to the caller
	 */
	T deleteMin()
	{
		int last_index = size() - 1;             // Calc last item index
		int root_index = 0;                      // Root index (for readability)

		T min_item = _items[root_index];         // Keep item to return
		_items[root_index] = _items[last_index]; // Move last item to root
		_items.erase(_items.end() - 1);          // Erase last element entry

		percolateDown(0);                        // Fix heap property
		return min_item;

	}


	/**
	 *  Returns true if heap is empty, else false
	 */
	bool isEmpty() const
	{
		return _items.size() == 0;
	}


	/**
	 *  Returns current quantity of elements in heap (N)
	 */
	int size() const
	{
		return _items.size();
	}

	/**
	 *  Return heap data in order from the _items vector
	 */
	string to_s() const
	{
		string ret = "";
		for(unsigned int i = 0; i < _items.size(); i++)
     	{
			ret += to_string(_items[i]) + " ";
		}
		return ret;
	}

	/**
	 *  Print out the data in order from the _items vector
	 */
	void print() const
	{
		for(int i = 0; i < _items.size(); i++)
     	{
			cout << _items[i] << " ";
		}

	}

	/**
	 *  Print out the data with array index details from the _items vector
	 */
	void printArray() const
	{
		for(unsigned int i = 0; i < _items.size(); i++)
		{
			cout << "  [x] Heap element [" << i << "]. key=" 
			     << _items[i] << endl;
		}
	}

	/**
 	 *  Print out the tree by levels (kinda pretty?)
 	 */
	void printPretty() const
	{
		int rownum = 1;
		cout << "   [x] Row #" << rownum  << " -    ";
		for( unsigned int i = 0; i < _items.size(); i++ )
		{
			cout << _items[i] << " ";
			if( pow(2, rownum) - 1 == i + 1 )
			{
				rownum++;
				cout << endl << "   [x] Row #" << rownum  << " -    ";
			}
		}
		cout << endl;
	}
};

#endif
