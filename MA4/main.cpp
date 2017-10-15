	//***************************************************************************//
	//**
	//**  Simple Heap implementation
	//**    Copyright 2016 - Aaron S. Crandall
	//**
	//**
	//**
	//***************************************************************************//
	
#include <iostream>
#include <string.h>
#include "Heap.h"

/**
 *  Run a series of tests to evaluate the heap object
 */
void heapTests()
{
	Heap<int> myHeap;
	myHeap.insert(890);
    myHeap.insert(567);
	myHeap.insert(456);
	myHeap.insert(921);
	myHeap.insert(678);
	myHeap.insert(123);
	myHeap.insert(234);
	myHeap.insert(345);
	myHeap.insert(750);

/*
	// This should build a heap that looks like this:
	//                    123 
	//                   /   \
	//                345     234 
	//                / \     / \
	//              678 890 567 456 
	//              / \
	//            921 750
*/
	
	
	cout << " [x] Current elements in the heap (should be low->high order): " << endl;
	myHeap.printArray();

	cout << " [x] Tree-ish form of the heap elements: " << endl;
	myHeap.printPretty();
	cout << endl;

	// Testing the insert & percolateUp behavior
	cout << " ***************** Insert testing ***********************" << endl;
	cout << " [X] Current heap order test after insert / percolateUp: " << endl;
	cout << "  [x] Heap should be:   123 345 234 678 890 567 456 921 750" << endl;
	cout << "  [t] Heap actually is: ";
	cout << myHeap.to_s();

	if( myHeap.to_s() == "123 345 234 678 890 567 456 921 750 " )
	{
		cout << "- PASS " << endl;
	}else{
		cout << "- FAIL " << endl;
	}

	myHeap.insert(101);
	cout << "  [x] Heap should be:   101 123 234 678 345 567 456 921 750 890 " << endl;
	cout << "  [t] Heap actually is: ";
	cout << myHeap.to_s();

	if( myHeap.to_s() == "101 123 234 678 345 567 456 921 750 890 " )
	{
		cout << "- PASS " << endl;
	}else{
		cout << "- FAIL " << endl;
	}
	cout << endl;


	// Testing the remove & percolateDown behavior
	cout << " ***************** Remove/Delete testing ****************" << endl;
	cout << " [X] Beginning to remove elements from the heap: " << endl;
	cout << "  [*] Once percolateDown is done, these go low->high." << endl;

	string acc = "";
	cout << "  [x] Order should be:   101 123 234 345 456 567 678 750 890 921" << endl;;
	cout << "  [t] Order actually is: ";
	while (myHeap.isEmpty() == false)
	{
		int top = myHeap.deleteMin();
		cout << top << " ";
		acc += to_string(top) + " ";
	}

	if( acc == "101 123 234 345 456 567 678 750 890 921 " )
	{
		cout << "- PASS " << endl;
	}else{
		cout << "- FAIL " << endl;
	}

	cout << endl;


	cout << " [x] Done. " << endl;
}


/**
 *  Main function for our heap and heap testing
 */
int main(int argc, char* argv[])
{
	
	if( argc > 1 && !strcmp(argv[1], "--test" ) )
	{
		cout << " [x] Running in test mode. " << endl;
		heapTests();
		cout << " [x] Program complete. " << endl;
	}
	else
	{
		cout << " [x] Running in normal mode. " << endl;
		cout << "  [!] Nothing to do in normal mode, so here's a helper: " << endl << endl;

cout << ""
""
"                                  ___.___               \n"
"                                    (_]===*             \n"
"                                    o 0                 \n"
"                                                        \n"
"                 _,-}}-._                               \n"
"                /\\   }  /\\                            \n"
"              _|(0\\\\_ _/0)                  ___|_     \n"
"             _|/  (__''__)                 |#####|      \n"
"           _|\\/    WVVVVW                  |#####|     \n"
"          \\ _\\     \\MMMM/_             .-----.###|   \n"
"        _|\\_\\     _ '---; \\_           |#####|###|   \n"
"   /\\   \\ _\\/      \\_   /   \\          |#C++#|###| \n"
"  / (    _\\/     \\   \\  |'VVV     P    |#####|###|   \n"
" (  '-,._\\_.(      'VVV /      (_/|\\_) |#####|###|    \n"
"  \\         /   _) /   _)     (_/_ _\\_)|#####|###|    \n" 
"   '....--''\\__vvv)\\__vvv)_____|_| |_|_|#####|###|____ldb\n";



		cout << endl << " You should probably run 'make test' to test your program. " << endl;
	}
	
}
