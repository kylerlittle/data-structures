/**
 *  main.cpp - Hashtable based dictionary
 *   Aaron Crandall <acrandal@gmail.com> - 2017
 *   Educational use only
 *
 */


#include <iostream>
#include <cstdlib>
#include <string.h>
#include "word.h"
#include "hashtable.h"
#include "dictionary.h"
#include "testinghash.h"
#include "testingdictionary.h"


using namespace std;

/**
 *  Test mode operations
 */
void run_test_mode( bool bigtest = false ) {
	cout << " [t] Running in test mode. " << endl;

	run_hashtable_tests();              // See testinghash.h
	cout << endl << " ----------------------------------------------------------- " << endl << endl;;

	cout << " [t] Testing the dictionary class. " << endl;
	run_dictionary_tests( bigtest );    // See testingdictionary.h
}

/**
 *  Normal mode execution for general user control
 */
void run_normal_mode() {
	cout << " [x] Running in normal mode. " << endl;

	Dictionary dict;

	dict.run_ui();
}



/**
 *  Main function for test or use
 */
int main( int argc, char* argv[] )
{
	// Note: If you call this program like this: ./HashingDict --test
	//  it will call the test function and --withFuzzing will test and load a big dictionary file
    bool do_test = false;
    bool do_big_test = false;
    for( int i = 0; i < argc; ++i ) {
	    if( !strcmp(argv[i], "--test" ) ) {
            cout << " [x] Enabling test mode. " << endl;
            do_test = true;
        }
        else if( !strcmp(argv[i], "--withFuzzing" )  ) {
            cout << " [x] Enabling test and BIG test mode. " << endl;
            do_test = true;
            do_big_test = true;
        }
    }

    if( do_test ) {
        run_test_mode( do_big_test );
		cout << " [x] Testing program complete. " << endl;
        if( do_big_test )
		    cout << " [x] BIGTEST testing program complete. " << endl;
    }
	else
	{
		cout << " [x] Running in normal mode. " << endl;
		cout << "  [!] Nothing to do in normal mode so here's a helicopter: " << endl;

		cout << "        .----.-.\n       /    ( o \\\n      '|  __ ` ||\n       |||  ||| -'" << endl << endl;
		cout << "     Since that's not a helicopter, you should probably replace this code with something like \"Welcome to my dictionary program\" and go into normal running mode." << endl << endl;

		cout << endl << "     Oh, and you should probably run 'make test' to test your program. " << endl;

		run_normal_mode();
	}
    return(0);
}
