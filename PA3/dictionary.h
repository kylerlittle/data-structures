
/*
 *  dictionary.h -- A hash-based dictionary for searching definitions
 *   Copyright 2017 - Aaron S. Crandall <acrandal@gmail.com>
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

// LAST UPDATE: 6:03 AM 10/17/17
// then write a basic function to read input of json file
// basic file open, (getline() loop), then spit back out to screen
// then play with that to tokenize it

// SOURCE: https://stackoverflow.com/questions/16388510/evaluate-a-string-with-a-switch-in-c
// Allows for C++ switch statements using strings
// Converts string to a constant unsigned int to use in switch statement
constexpr unsigned int str2int(const char * str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

class Dictionary
{
 private:
  Hashtable<string, Word> _dict;  // Primary dictionary store

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

  // Precondition: parsedLine vector
  // Utility function called if command is "add," "remove," or "define" to clean up the vector
  // Converts the "word" to all lower case for lookup & removes any enclosing quotations on
  // the "word" or "definition"
  void cleanStrings(vector<string> parsedLine) {
    // can I use this for json format? One sec...
  }

  void load(string &filename) {
    std::ifstream input;
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);  // Allows exception to be thrown if failure opening file
    try {
      input.open(filename.c_str());
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
