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


class Dictionary
{

	private:
		Hashtable<string, Word> _dict;  // Primary dictionary store

	void parseline( string line ) {
		//cout << " [d] Parsing line: " << line << endl;
        cout << endl;
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
			cout << endl << " --debug-- Entered command: " << instr << endl;
			parseline(instr);
			// call function based on line contents
			// print results

			cout << "Enter command: ";
		}
		cout << endl;
	}

};



#endif
