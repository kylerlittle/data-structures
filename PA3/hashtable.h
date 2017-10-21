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
#include <list>
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
    nextPrime += 2;     // we can skip all even numbers obviously
  return nextPrime;
}




template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
 private:
  // Internal Data Members
  int currentNumItems;           // number of filled buckets
  vector< list<VALTYPE> > __table;    // internal table


  // Internal Methods (Private)
  /**
   *  Rehash the table into a larger table when the load factor is too large
   */
  void rehash() {
    vector<list<VALTYPE>> oldTable = __table;    // make copy of old table

    this->clear();     // clear current table
    unsigned int newTableSize = findNextPrime(2 * __table.size());
    __table.resize(newTableSize);   // resize
    
    // For each item in old hash table, insert in new table
    for (auto & chain : oldTable) {
      for (auto & item : chain) {
	this->insert(item.myword, item);
      }
    }
  }
  
  /**
   *  Function that takes the key (a string or int) and returns the hash key
   *   This function needs to be implemented for several types it could be used with!
   */
  unsigned int hash_function(int key) {
    //    cout << " Hashing with int type keys." << endl;
    return key % __table.size();
  }

  // Uses hash function from:
  // Data Structures & Algorithm Analysis in C++, Fourth Edition, Mark Allen Weiss
  // p. 195, figure 5.4
  unsigned int hash_function(string key) {
    //    cout << " Hashing with string type keys." << endl;
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
    // Check if node already exists in table.
    VALTYPE * ptr = this->find(key);
    if (ptr != nullptr) {  // i.e. item was already in the table
      ptr->definition = val.definition;        // overwrite entry
      return false;
    }

    // Since item wasn't found, insert it into the table!
    int hashedKey = hash_function(key);
    __table.at(hashedKey).push_back(val);
    ++currentNumItems;

    // Now check if we need to rehash
    if (this->load_factor() >= 1.0)
      this->rehash();

    return true;
  }
  
  /**
   *  Return whether a given key is present in the hash table
   */
  bool contains(KEYTYPE key) {
    int hashedKey = hash_function(key);
    typename list<VALTYPE>::const_iterator it;
    for (it = __table.at(hashedKey).begin(); it != __table.at(hashedKey).end(); ++it) {
      if (key == (*it).myword)
	return true;
    }
    return false;
  }
  
  /**
   *  Completely remove key from hash table
   *   Returns number of elements removed
   */
  int remove(KEYTYPE key) {
    int itemsRemoved = 0;
    int pos = hash_function(key);    // bucket where key hashed to
    typename list<VALTYPE>::const_iterator it;
    for (it = __table.at(pos).begin(); it != __table.at(pos).end(); ++it) {
      if (key == (*it).myword) {   // if keys match
	__table.at(pos).erase(it);    // erase the item
	itemsRemoved = 1;   // removed 1 item
	--currentNumItems;    // decrement number of items in table
	break;
      }
    }
    return itemsRemoved;
  }
  
  /**
   *  Searches the hash and returns a pointer
   *   Pointer to Word if found, or nullptr if nothing matches
   */
  VALTYPE *find(KEYTYPE key) {
    // Essentially identical code to 'contains' (only differs in return type)
    // If I was writing in a different language, I could merge the two functions into one...
    int hashedKey = hash_function(key);
    typename list<VALTYPE>::iterator it;
    for (it = __table.at(hashedKey).begin(); it != __table.at(hashedKey).end(); ++it) {
      if (key == (*it).myword)
	return &(*it);      // address of the found object
    }
    return nullptr;   // not found
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
    int chain_index = rand() % __table.at(random_index).size(), i = 0;  // pick random value in chain
    typename list<VALTYPE>::iterator it;
    for (it = __table.at(random_index).begin(); it != __table.at(random_index).end(); ++it) {
      if (i == chain_index)      // walk thru list until we get to randomly selected index
	break;
      ++i;
    }
    return &(*it);   // return address of randomly selected object
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
    currentNumItems = 0;
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
