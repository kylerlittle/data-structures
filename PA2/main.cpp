/*
 *  main.cpp - AVL Tree testing
 *   Aaron Crandall - 2017
 *   Educational use only
 */


#include <iostream>
#include <cstdlib>
#include <string.h>
#include "AvlTree.h"
#include "AvlTreeTesting.h"
using namespace std;

/*
 *  Main function for test or use
 */
int main( int argc, char* argv[] )
{
	int retState = 0;
	// Note: If you call this program like this: ./avltree --test
	//  it will call the test function
    bool is_test_mode = false;
    bool is_fuzzing_test_mode = false;
    for( int i = 0; i < argc; i++ ) {
	    if( !strcmp(argv[i], "--test" ) ) {
		    cout << " [x] Enabling test mode. " << endl;
            is_test_mode = true;
        } else if( !strcmp(argv[i], "--withFuzzing" ) ) {
            cout << " [x] Enabling fuzzing tests. " << endl;
            is_fuzzing_test_mode = true;
        }
    }
    if( is_test_mode || is_fuzzing_test_mode ) {
		retState = avlTreeTests( is_fuzzing_test_mode );          // From AvlTreeTesting.h
	}
	else
	{
		cout << " [x] Running in normal mode. " << endl;
		cout << "  [!] Nothing to do in normal mode so here's a helicopter: " << endl;
		cout << "   ___.___\n     (_]===*\n     o 0" << endl;
		cout << endl << " You should probably run 'make test' to test your program. " << endl;
		cout << "  This program also has a fuzzing test with 'make bigtest' to test your program. " << endl;
	}
    cout << " [x] Program complete. " << endl;
	return(retState);
}
