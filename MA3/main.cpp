/*
 * Binary Search Tree implementation 
 *  - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations BST
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 * Aaron Crandall - 2017 - Heavy overhaul of tests & behaviors
 *
 */

#include <iostream>
#include <cstring>	// strcmp
#include <stdlib.h> // srand, rand
#include <time.h>   // time
#include <math.h>   // pow (for exponents)

#include "BST.h"	//BST implementation

using namespace std;

void test_copy_constructor() {
    cout << " [t] Testing copy constructor" << endl;
    BST<int> * bstsrc = new BST<int>({4,2,1,3,6,5,7,9,8});
    BST<int> * bstcopy = new BST<int>(*bstsrc);      // Invoke copy constructor
    cout << "Should produce:      \t1 2 3 4 5 6 7 8 9" << endl;
    cout << "BST src  (in order): \t"; bstsrc->printInOrder(); cout << endl;
    cout << "BST copy (in order): \t"; bstcopy->printInOrder(); cout << endl;
    if( bstsrc->getRoot() == NULL || bstcopy->getRoot() == NULL )
        cout << " FAIL: one of trees is NULL " << endl;
    else if( bstsrc->getRoot() != bstcopy->getRoot() )
        cout << " PASS: Did a deep copy of tree since copy has diff root than src" << endl;
    else
        cout << " FAIL: Did a shallow copy of tree since they both point to same root" << endl;
    cout << endl;
}

void test_move_constructor() {
    cout << " [t] Testing move constructor" << endl;
    BST<int> bstsrc = BST<int>({4,2,1,3,6,5,7,9,8});
    BST<int> bstmove = std::move( bstsrc ); // Invoke move constructor
    cout << "Should produce: <nothing, it's been moved.> " << endl;
    cout << "BST src (pre order): \t"; bstsrc.printPreOrder(); cout << endl;
    cout << "Should produce:      \t4 2 1 3 6 5 7 9 8" << endl;
    cout << "BST move (pre order):\t"; bstmove.printPreOrder(); cout << endl;
    if( bstsrc.getRoot() == NULL && bstmove.getRoot() != NULL )
        cout << " PASS: src is NULL and move is != NULL " << endl;
    else
        cout << " FAIL: someone is NULL or != NULL improperly" << endl;
    cout << endl;
}


void test_copy_assignment_operator() {
    cout << " [t] Testing copy= constructor" << endl;
    BST<int> bstsrc = BST<int>({4,2,1,3,6,5,7,9,8});
    BST<int> bstcopy = BST<int>({5,6,7});
    cout << "  BST to copy over starts: \t"; bstcopy.printLevelOrder(); cout << endl;
    cout << "  Invoking copy assingment operator." << endl;

    bstcopy = bstsrc;      // Invoke copy= constructor

    cout << "Should produce:        \t1 3 2 5 8 9 7 6 4" << endl;
    cout << "BST src  (post order): \t"; bstsrc.printPostOrder(); cout << endl;
    cout << "BST copy (post order): \t"; bstcopy.printPostOrder(); cout << endl;
    if( bstsrc.getRoot() == NULL || bstcopy.getRoot() == NULL )
        cout << " FAIL: one of trees is NULL " << endl;
    else if( bstsrc.getRoot() != bstcopy.getRoot() )
        cout << " PASS: Did a deep copy of tree since copy has diff root than src" << endl;
    else
        cout << " FAIL: Did a shallow copy of tree since they both point to same root" << endl;
    cout << endl;
}
 
void test_move_assignment_operator() {
    cout << " [t] Testing move assignment operator" << endl;
    BST<int> bstsrc = BST<int>({4,2,1,3,6,5,7,9,8});
    BST<int> bstmove = BST<int>({5,6,7}); 
    bstmove = std::move( bstsrc ); // Invoke move assignment op
    cout << "Should product: <nothing, it's been moved> " << endl;
    cout << "BST src  (in order): \t"; bstsrc.printInOrder(); cout << endl;
    cout << "Should produce:      \t1 2 3 4 5 6 7 8 9" << endl;
    cout << "BST move (in order): \t"; bstmove.printInOrder(); cout << endl;
    if( bstsrc.getRoot() == NULL && bstmove.getRoot() != NULL )
        cout << " PASS: src is NULL and move is != NULL " << endl;
    else
        cout << " FAIL: someone is NULL or != NULL improperly" << endl;
    cout << endl;
}

/* Testing in,pre,post,level order tree traversals */
void test_tree_traversal_ordering() {
    cout << " [t] Executing tree traversal tests. " << endl;
    BST<int> * bst = new BST<int>({4,2,1,3,6,5,7,9,8});

    cout << "Should produce:\t1 2 3 4 5 6 7 8 9" << endl;
    cout << "Inorder: \t";
    bst->printInOrder();
    cout << endl << endl;

    cout << "Should produce:\t1 3 2 5 8 9 7 6 4" << endl;
    cout << "Postorder: \t";
    bst->printPostOrder();
    cout << endl << endl;

    cout << "Should produce:\t4 2 1 3 6 5 7 9 8" << endl;
    cout << "Preorder: \t";
    bst->printPreOrder();
    cout << endl << endl;

    cout << "Should produce:\t4 2 6 1 3 5 7 9 8" << endl;
    cout << "Levelorder: \t";
    bst->printLevelOrder();
    cout << endl << endl;

    vector<int> testLvL{4,2,6,1,3,5,7,9,8};
    vector<int> & retLvL = bst->returnLevelOrder();
    if( testLvL == retLvL ) {
        cout << " PASS: returnLevelOrder returned proper vector." << endl;
    } else {
        cout << " FAIL: did not return proper level order vector." << endl;
    }
    cout << endl;

    return;
}

void test_tree_features() {
    cout << " [t] Testing features of the BST. " << endl;
    BST<int> * bst = new BST<int>({4,2,1,3,6,5,7,9,8});
    cout << "Contains (7): \t";
    (bst->contains(7)) ? cout << " True - [PASS] " : cout << " False - [FAIL]";
    cout << endl;
    cout << "Contains (10): ";
    (bst->contains(10)) ? cout << " True - [FAIL] " : cout << " False - [PASS]";
    cout << endl;
    cout << "Nodes count (9): " << bst->nodesCount();
    if( bst->nodesCount() == 9 )
        cout << "\t[PASS]";
    else
        cout << "\t[FAIL]";
    cout << endl;
    cout << "Height (5): " << bst->height();
    if( bst->height() == 5 )
        cout << "\t\t[PASS]";
    else
        cout << "\t\t[FAIL]";
    cout << endl;
    cout << "Max path:  ";
    bst->printMaxPath();
    cout << endl;
    cout << "Should be: 4 6 7 9 8";
    cout << endl << endl;
}

/*
 * run_tests - Execute tests to evaluate BST
 */
void run_tests() {
	cout << " [t] Starting tests." << endl;

    test_tree_features();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment_operator();
    test_move_assignment_operator();
    test_tree_traversal_ordering();

	cout << " [t] ending tests." << endl;
	return;
}

/*
 * run big test - LOTS of data in your tree!
 */
void run_big_test() {
    cout << " [t] Beginning BIG tree test! " << endl;
    srand (time(NULL));  // Initialize random seed
    BST<int> bst = BST<int>();
    int tree_size = pow(2.0, 20.0);
    cout << endl << "  [t] Testing tree of size (2^20): " << tree_size << endl;
    cout << "Node # / Of #'s (\% done) : Value Inserted " << endl;
    for( int i = 1; i < tree_size + 1; i++ ) {
        int val = rand() % tree_size + 1;
        cout << "\r" << i << " / " << tree_size << " (" << 100.0*i / tree_size << "%)"  << "  :  " << val;
        bst.add(val);
    }

    cout << endl << endl;
    cout << "Nodes count (" << tree_size << "): " << bst.nodesCount();
    if( bst.nodesCount() == tree_size )
        cout << "\t[PASS]";
    else
        cout << "\t[FAIL]";
    cout << endl;
    cout << "Height: " << bst.height() << endl;
    cout << "Max path:  ";
    bst.printMaxPath();
    cout << endl << endl;

    cout << " [t] BIG tree test done!" << endl;
    return;
}


/*
 * Main function - includes enabling test mode
 */
int main( int argc, char* argv[] ) {
	bool is_test_mode = false;
	bool is_BIG_test_mode = false;
	for( int i = 0; i < argc; i++ ) {
		if( !strcmp(argv[i], "--test" ) ) {
			cout << " [t] Enabling test mode. " << endl;
			is_test_mode = true;
		} else if ( !strcmp(argv[i], "--bigtest" ) ) {
			cout << " [t] Enabling BIG test mode. " << endl;
			is_BIG_test_mode = true;
        }
	}

	if( is_test_mode || is_BIG_test_mode ) {
		run_tests();
        if( is_BIG_test_mode )
            run_big_test();
	}else{
		cout << " [x] Running main program - nothing to do!" << endl;
        cout << "     Since it's quiet, here's a flower..." << endl << endl;
        cout << ""
"              __/)\n"
"           .-(__(=:\n"
"        |\\ |    \\)\n"
"ejm97   \\ ||\n"
"         \\||\n"
"          \\|\n"
"           |\n"
"        \n";
	}

    return 0;
}
