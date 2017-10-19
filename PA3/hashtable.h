/**
 *  Basic hash table implementation
 *   Aaron S. Crandall - 2017 <acrandal@gmail.com>
 *
 */

/*
LAST UPDATED: 4:04 PM 10/19/17
Need to modify my implementation so that it uses template
 */




#ifndef __HASH_H
#define __HASH_H

#include <string>
#include <iostream>
#include <vector>
#include <ctime>     // time()
#include <cstdlib>   // srand(), rand()
#include <cmath>     // ceil(), sqrt()

using namespace std;
/*
	private:
		void rehash();
		int hash_function(KEYTYPE key);
		
	public:
		bool insert(KEYTYPE key, VALTYPE val);
		bool contains(KEYTYPE key);
		int remove(KEYTYPE key);
		VALTYPE * find(KEYTYPE key);
		VALTYPE * random();    // returns ptr to random Word in table
		int size();            // Elements currently in table
		bool empty();          // Is the hash empty?
		float load_factor();   // Return current load factor
		void clear();          // Empty out the table
		int bucket_count();    // Total number of buckets in table
*/

/*
 * Utility function to check if a number n is prime
 */
bool isPrime(int n) {
  int sqrtN = ceil(sqrt(n));
  for (int i = 2; i < sqrtN; ++i) {
    if (n % i == 0)
      return false;
  }
  return true;
}

/*
 * Utility function to find the next prime number after n
 */
unsigned int findNextPrime(int n) {
  int nextPrime = 0;
  nextPrime = ((n % 2 == 0) ? (n + 1) : (n + 2) );   // set nextPrime equal to next odd number after n
  while (isPrime(nextPrime) == false)
    n += 2;     // we can skip all even numbers obviously
  return nextPrime;
}




template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
 private:
  // Internal Data Members
  int currentNumItems;           // number of filled buckets
  vector< vector<VALTYPE> > __table;    // internal table


  // Internal Methods (Private)
  /**
   *  Rehash the table into a larger table when the load factor is too large
   */
  void rehash() {
    unsigned int newTableSize = findNextPrime(2 * __table.size());
    Hashtable newTable(newTableSize);

    // For each item in old hash table, insert in new table
    for (auto & chain : __table) {
      for (auto & item : chain) {
	newTable.insert(item.myword, item);
      }
    }
    
    swap(newTable, *this);   // requires move assignment & constructor are implemented
  }
  
  /**
   *  Function that takes the key (a string or int) and returns the hash key
   *   This function needs to be implemented for several types it could be used with!
   */
  unsigned int hash_function(int key) {
    cout << " Hashing with int type keys." << endl;
    return key % __table.size();
  }

  // Uses hash function from:
  // Data Structures & Algorithm Analysis in C++, Fourth Edition, Mark Allen Weiss
  // p. 195, figure 5.4
  unsigned int hash_function(string key) {
    cout << " Hashing with string type keys." << endl;
    unsigned int hashVal = 0;

    for (char ch : key)
      hashVal = 37 * hashVal + ch;
    
    return hashVal % __table.size();
  }
  		
 public:
  /**
   *  Basic constructor
   */
 Hashtable( int startingSize = 101 ) : currentNumItems(0), __table(startingSize) { }
  
  /**
   *  Add an element to the hash table
   */
  bool insert(KEYTYPE key, VALTYPE val) {
    // Currently unimplemented
 

    if (this->load_factor() >= 1.0)
      this->rehash();

    return true;
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
    int itemsRemoved = 0;
    if (this->contains(key)) {
      int pos = hash_function(key);    // bucket where key hashed to
      std::vector<VALTYPE>::iterator it;
      for (it = __table.at(pos).begin(); it->myword != key; ++it);    // location in vector of item to be removed
      __table.at(pos).erase(it);    // erase the item
      itemsRemoved = 1;
    }
    return itemsRemoved;
  }
  
  /**
   *  Searches the hash and returns a pointer
   *   Pointer to Word if found, or nullptr if nothing matches
   */
  VALTYPE *find(KEYTYPE key) {
    return nullptr;
  }
  
  /**
   *  Returns ptr to random word in hash table
   *  If no words are currently in table, nullptr returned
   */
  VALTYPE * random() {
    if (this->size() == 0) return nullptr;
    
    srand((unsigned)time(0));   // Seed Value
    int random_index = rand() % __table.size();
    while (__table.at(random_index).empty()) {   // Continue generating random index until we find a nonempty bucket
      random_index = rand() % __table.size();
    }
    int chain_index = rand() % __table.at(random_index).size();  // pick random value in chain
    
    return &__table.at(random_index).at(chain_index);   // return address of this value
  }

  /**
   *  Return current number of elements in hash table
   */
  int size() {
    return currentNumItems;
  }
  
  /**
   *  Return true if hash table is empty, false otherwise
   */
  bool empty() {
    return (currentNumItems == 0);
  }

  /**
   *  Calculates the current load factor for the hash
   */
  float load_factor() {
    return (float)currentNumItems / __table.size();
  }

  /**
   *  Returns current number of buckets (elements in vector)
   */
  int bucket_count() {
    return __table.size();
  }
  
  /**
   *  Deletes all elements in the hash
   */
  void clear() {
    for (auto & chain : __table)
      chain.clear();
  }
  
  void print(int maxNumElementsToPrint) {   // by default, assume all elements
    if (maxNumElementsToPrint > currentNumItems) {
      maxNumElementsToPrint = currentNumItems;
      cout << "There aren't that many entries in the dictionary, so" << endl;
      cout << "all entries will be printed instead." << endl;
    }
    // Print all entries
  }

};


#endif
