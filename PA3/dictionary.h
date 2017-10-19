
/*
 *  dictionary.h -- A hash-based dictionary for searching definitions
 *   Copyright 2017 - Kyler Little
 */

#ifndef __DICT_H
#define __DICT_H

#include "hashtable.h"
#include "word.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cctype>


/*
LAST UPDATED: 7:37 PM 10/17/17
I have the json file completely tokenized now. However, I'm not satisified.
One, I can improve the removeDelimiters function to remove more than one delimiter
Two, in 'parseline,' I would like to add the entire definition of a word as an entry
rather than individual words. This will save time in printing even if it makes it less extensible.
 */


/*
 * UTILITY FUNCTIONS
 * These functions are not a part of the class definition; however, they are used by the class.
*/

/* str2int */
// SOURCE: https://stackoverflow.com/questions/16388510/evaluate-a-string-with-a-switch-in-c
// Allows for C++ switch statements using strings
// Converts string to a constant unsigned int to use in switch statement
constexpr unsigned int str2int(const char * str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

/* parseline */
// Parse the line into 0-3 strings
// Push_back all tokens into "parsedLine" vector
// If 'line' is not empty, token #1 is assumed to be a command
// If a second token is present, it is assumed to be a word or filename
// If a third token is present, it is assumed to be a word definition
void parseline( string line, vector<string> & parsedLine ) {
  if (!line.empty()) { // not empty
    string buffer;  // buffer to read token into
    stringstream ss(line);  // insert line into a stream

    // Grab command (first word)
    ss >> buffer;
    if (!buffer.empty())  // if token is actually something
      parsedLine.push_back(buffer);

    // Grab second argument (either a word or filename)
    ss >> buffer;
    if (!buffer.empty())
      parsedLine.push_back(buffer);

    // If there is a third argument, it's the definition of a word we're adding
    getline(ss, buffer);
    if (!buffer.empty())
      parsedLine.push_back(buffer);
  } 
}

/* removeDelimiter */
// Utility function to remove a delimiter from a given string
// Makes one pass through the str, but 'erase' has to recopy string each time delimiter found...
// If I reuse this code, make the big O a lot better
void removeDelimiter(string & str, char delimiter) {
  std::size_t pos = str.find_first_of(delimiter, 0);
  while (pos != string::npos) {
    str.erase(pos, 1);
    pos = str.find_first_of(delimiter, 0);
  }
}

/* convertToLowerCase */
// Utility function to convert a word to all lower case letters
void convertToLowerCase(string & word) {
  int diff = 'A' - 'a';
  for (auto & letter : word) {
    if (isupper(letter))
      letter -= diff;
  }
}

/* parseJSONline */
// Utility function to parse a json file line
// Precondition: Format of each block is "string" : "string", "string" : "string"
// Could be extended to use for more complex JSON files
// The function grabs the "word" entry and "definition" entries from the json line &
// places them into word.myword & word.definition respectively
void parseJSONline(string & jLine, Word & word) {
  int counter = 0;
  while (!jLine.empty()) {  // while we haven't parsed the entire line
    size_t start, end;
    start = jLine.find_first_of('\"'); 
    end = jLine.find_first_of('\"', start + 1);
    if (start != string::npos && end != string::npos) {
      if (counter == 1)  // this is the "word" value
	word.myword = jLine.substr(start + 1, end - start - 1);  // +1 to start str after opening quote; -1 to end before closing quote
      else if (counter == 3)
	word.definition = jLine.substr(start + 1, end - start - 1);
      ++counter;
      jLine = jLine.substr(end + 1);
    } else {
      break;  // No reason to keep parsing
    }
  }
}



/*
 * CLASS DEFINITION: Dictionary
 */
class Dictionary
{
 private:
  Hashtable<string, Word> _dict;  // Primary dictionary store

  /* help */
  // Prints out information about the commands which run the user interface
  void help() {
    cout << "*** Command Help ***" << endl;
    cout << "add [word] [definition]" << endl;
    cout << "--> adds word and its definition to internal dictionary; if already exists, overwrites" << endl;
    cout << "remove [word]" << endl;
    cout << "--> removes word from internal dictionary" << endl;
    cout << "define [word]" << endl;
    cout << "--> prints out word's definition if found in internal dictionary" << endl;
    cout << "load [filename]" << endl;
    cout << "--> loads JSON file of words/definitions into internal dictionary" << endl;
    cout << "unload [filename]" << endl;
    cout << "--> removes all words in JSON file from internal dictionary (if found)" << endl;
    cout << "size" << endl;
    cout << "--> prints current number of words in internal dictionary" << endl;
    cout << "clear" << endl;
    cout << "--> removes all words from internal dictionary" << endl;
    cout << "print || print [#words]" << endl;
    cout << "--> prints all words or user-entered maximum number of words from internal dictionary" << endl;
    cout << "random" << endl;
    cout << "--> prints randomly selected word from the internal dictionary" << endl;
    cout << "quit" << endl;
    cout << "--> exits program" << endl;
  }

  /* add */
  // removes any enclosing quotation marks from word and definition
  // converts word to all lower case letters
  // adds word & corresponding Word objection to internal dictionary
  void add(string & word, string & definition) {
    removeDelimiter(word, '\"');
    removeDelimiter(definition, '\"');
    convertToLowerCase(word);
    Word wordObj(word, definition);
    _dict.insert(word, wordObj);    // if word is already in table, insert will handle this
  }

  /* remove */
  // ...
  void remove(string & word) {
    removeDelimiter(word, '\"');
    convertToLowerCase(word);
    // REMOVE
  }

  /* define */
  // ...
  void define(string & word) {

  }
  
  /* load */
  // ...
  void load(string &filename) {
    std::ifstream input;
    if (input) {  // file opened successfully
      input.open(filename.c_str());
      cout << "Successfully opened JSON file named: " << filename << endl;
      string jsonLine;
      while (getline(input, jsonLine)) {
	Word word;
	parseJSONline(jsonLine, word);
	convertToLowerCase(word.myword);
	if (!word.myword.empty())  // if word isn't empty, add it to the hash table
	  _dict.insert(word.myword, word);
      }
    } else {
      cout << "Failed to open JSON file named " << filename << endl;
    }
    input.close();
  }

  /* unload */
  // ...
  void unload(string & filename) {

  }

  /* size */
  // ...
  void size() {
    // Add method to hashtable to keep track of this... (will need for load factor anyways)
  }

  /* clear */
  // ...
  void clear() {

  }

  /* print */
  // ...
  void print(string & maxWordNum) {
    // Convert number to an integer using stoi first...
  }

  /* random */
  // ...
  void random() {
    // Use random number generator (mod by Tablesize) to generate random index
    // Continue doing so while there is no word at that index
  }

 public:
  Dictionary()	// Default constructor
    { }

  /**
   *  Run the main dictionary user interface
   */
  void run_ui() {
    // print out header
    cout << "+------------------------------------------+" << endl;
    cout << "|-- Welcome to the best dictionary evar! --|" << endl;
    cout << "+------------------------------------------+" << endl;
    
    string instr;
    cout << " Enter command (^D or EOF quits): ";
    
    // read in user input until eof
    while (getline(cin, instr)) {
      // Variables to be Used
      vector<string> line;
      bool userWouldLikeToQuit = false;
      parseline(instr, line);
      if (!line.empty()) { // Check if we grabbed an empty line
	string & command = line.at(0);  // L Value Reference to first token in vector (the command)
	
	// Debugging output:
	cout << "Entered command: " << command << endl;
	
	// Switch statement is more efficient than if/else when there are a lot of items
	switch (str2int(command.c_str()))
	  {
	  case str2int("help"):
	    this->help();
	    break;
	  case str2int("add"):
	    this->add(line.at(1), line.at(2));  // 2nd and 3rd strings are word & def'n respectively
	    break;
	  case str2int("remove"):
	    this->remove(line.at(1));     // 2nd string is word to remove
	    break;
	  case str2int("define"):
	    this->define(line.at(1));     // 2nd string is word to define
	    break;
	  case str2int("load"):
	    this->load(line.at(1));  // 2nd string is filename
	    break;
	  case str2int("unload"):
	    this->unload(line.at(1));    // 2nd string is filename
	    break;
	  case str2int("size"):
	    this->size();
	    break;
	  case str2int("clear"):
	    this->clear();
	    break;
	  case str2int("print"):
	    this->print(line.at(1));    // 2nd string (if present) is number of words to print
	    break;
	  case str2int("random"):
	    this->random();  
	    break;
	  case str2int("quit"):
	    userWouldLikeToQuit = true;
	    break;
	  }
	if (userWouldLikeToQuit)
	  break;   // break out of loop
      }   // end if
    }  // end while
  }  // end run_ui

};



#endif
