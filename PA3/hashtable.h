/**
 *  Basic hash table implementation
 *   Aaron S. Crandall - 2017 <acrandal@gmail.com>
 *
 */

#ifndef __HASH_H
#define __HASH_H

#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;
/*
	private:
		void rehash();
		int hash_function(KEYTYPE key);
		
	public:
		bool insert(KEYTYPE key, VALTYPE val);
		bool contains(KEYTYPE key);
		int remove(KEYTYPE key);
		VALTYPE & find(KEYTYPE key);
		int size();            // Elements currently in table
		bool empty();          // Is the hash empty?
		float load_factor();   // Return current load factor
		void clear();          // Empty out the table
		int bucket_count();    // Total number of buckets in table
*/

template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
	private:
		/**
		 *  Rehash the table into a larger table when the load factor is too large
		 */
		void rehash() {

		}

		/**
		 *  Function that takes the key (a string or int) and returns the hash key
		 *   This function needs to be implemented for several types it could be used with!
		 */
		int hash_function(int key) {
			cout << " Hashing with int type keys." << endl;
		}

		int hash_function(string key) {
			cout << " Hashing with string type keys." << endl;
		}

		
	public:
		/**
		 *  Basic constructor
		 */
		Hashtable( int startingSize = 101 )
		{

		}

		/**
		 *  Add an element to the hash table
		 */
		bool insert(KEYTYPE key, VALTYPE val) {
			// Currently unimplemented
		}

		/**
		 *  Return whether a given key is present in the hash table
		 */
		bool contains(KEYTYPE key) {
			return false;
		}


		/**
		 *  Completely remove key from hash table
		 *   Returns number of elements removed
		 */
		int remove(KEYTYPE key) {
			// Doesn't actually remove anything yet
		}

		/**
		 *  Searches the hash and returns a pointer
		 *   Pointer to Word if found, or nullptr if nothing matches
		 */
		VALTYPE *find(KEYTYPE key) {
			return nullptr;
		}

		/**
		 *  Return current number of elements in hash table
		 */
		int size() {
			return(-1);
		}

		/**
		 *  Return true if hash table is empty, false otherwise
		 */
		bool empty() {
			return(false);
		}

		/**
		 *  Calculates the current load factor for the hash
		 */
		float load_factor() {
			//return _hash.load_factor();
			return (-1.0);
		}

		/**
		 *  Returns current number of buckets (elements in vector)
		 */
		int bucket_count() {
			return (-1);
		}

		/**
		 *  Deletes all elements in the hash
		 */
		void clear() {
			// Does nothing yet
		}

};


#endif
