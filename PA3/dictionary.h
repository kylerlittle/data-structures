
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
void removeDelimiters(string & str, char delimiter) {
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



/*
 * CLASS DEFINITION: Dictionary
 */
class Dictionary
{
 private:
  Hashtable<string, Word> _dict;  // Primary dictionary store

  void load(string &filename) {
    std::ifstream input;
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);  // Allows exception to be thrown if failure occurs when opening
    try {
      input.open(filename.c_str());
      string jsonLine;
      vector<string> lineVec;
      while (getline(input, jsonLine)) {
	parseline(jsonLine, lineVec);
	for (auto & token : lineVec) {
	  for (auto & delimiter : {'{','}', '[', ']', '\"', ','})
	    removeDelimiters(token, delimiter);
	  if (token == "word:" || token == "definition:" || token == "dictionary:")
	    token.clear();
	  cout << token;
	}
	cout << endl;
	lineVec.clear();
      }
      input.close();
    }
    catch (std::ios_base::failure & f) {
      cout << "Failed to open JSON file named " << filename << endl;
    }
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
      parseline(instr, line);
      if (!line.empty()) { // Check if we grabbed an empty line
	string & command = line.at(0);  // L Value Reference to first token in vector (the command)
	
	// Debugging output:
	cout << "Entered command: " << command << endl;
	
	// Switch statement is more efficient than if/else when there are a lot of items
	switch (str2int(command.c_str()))
	  {
	  case str2int("help"):
	    break;
	  case str2int("add"):
	    break;
	  case str2int("remove"):
	    break;
	  case str2int("define"):
	    break;
	  case str2int("load"):
	    this->load(line.at(1));  // 2nd string is filename
	    break;
	  case str2int("unload"):
	    break;
	  case str2int("size"):
	    break;
	  case str2int("clear"):
	    break;
	  case str2int("print"):
	    break;
	  case str2int("random"):
	    break;
	  case str2int("quit"):
	    break;
	  }
      }   // end if
    }
  }

};



#endif
