
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

// str2int
// SOURCE: https://stackoverflow.com/questions/16388510/evaluate-a-string-with-a-switch-in-c
// Allows for C++ switch statements using strings
// Converts string to a constant unsigned int to use in switch statement
constexpr unsigned int str2int(const char * str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

// Parse the line into strings based on the white space delimiter
// Push_back all tokens into "parsedLine" vector
void parseline( string line, vector<string> & parsedLine ) {
  if (!line.empty()) { // not empty
    string buffer;  // buffer to read token into
    stringstream ss(line);  // insert line into a stream
    
    while (ss >> buffer) {  // capitalizes on the fact that '>>' stops at whitespace
      if (!buffer.empty())  // if token is actually something
	parsedLine.push_back(buffer);
    }
  } 
}
  
// Utility function to remove a delimiter from a given string
// I didn't end up using this... but I'll leave it here because
// it might be useful for the future
void removeDelimiter(string & str, char delimiter) {
  std::size_t pos = str.find_first_of(delimiter, 0);
  while (pos != string::npos) {
    str.erase(pos, 1);
    pos = str.find_first_of(delimiter, 0);
  }
}

// Utility function to convert a word to all lower case letters
void convertToLowerCase(string & word) {
  int diff = 'A' - 'a';
  for (auto & letter : word) {
    if (isupper(letter))
      letter -= diff;
  }
}

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

  // help
  // ...
  void help() {

  }

  // add
  // ...
  void add(string 
  
  // load
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

  void 

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
