/*
 *  AvlTreeTesting.h - Testing our AVL implementation
 *   Aaron Crandall - 2017
 */


#include "AvlTree.h"
#include <iostream>
#include <string.h>


/*****************************************************************************/
// Do lots of random inserts and deletes. This is a fuzzing test
void test_BigTreeFuzzing() {
  /* BIGGER test of your AVL tree! */
    cout << "  [t] Big Tree Fuzzing test."; 
    vector<int> incVals;
    AvlTree<int> bigTree;
    srand (time(NULL));
    for( int i = 0; i < 3000; i++ ) {
        int newVal = rand() % 900000; // Generate new integer to insert into tree
        bool skip = false;
        for( int j = 0; j < incVals.size(); j++ ){ // Very dumb search!
        if( incVals[j] == newVal ){
            skip = true;
            j = incVals.size();
        }
        }
        if( !skip ){
            bigTree.insert(newVal);
            incVals.push_back(newVal);
        }

        if( i % 3 == 0 ){   // Delete a random element every 3 inserts
            int remIndex = rand() % incVals.size();
            bigTree.remove( incVals[remIndex] );
            incVals.erase(incVals.begin() + remIndex);
        }
    }
    cout << " - fuzzing test complete. " << endl;
}


void test_empty() {
    AvlTree<int> myTree;
    cout << "  [t] Testing isEmpty() interface";
    if( myTree.isEmpty() ) {
        cout << " - Pass" << endl;
    } else {
        cout << " - Fail" << endl;
    }
}


void test_size() {
    AvlTree<int> myTree;
    cout << "  [t] Testing size() interface..." << endl;;
    cout << "   [t] size() when empty: " << myTree.size() << " - ";
    (myTree.size() == 0) ? cout << "Pass" : cout << "Fail";
    cout << endl;

    vector<int> vals = { 10, 5, 23, 3, 7, 30, 1 };   // Give us some data!
    myTree.insert( vals ); 
    cout << "   [t] size() with " << vals.size() << " values: " << myTree.size() << " - ";
    (vals.size() == myTree.size()) ? cout << "Pass" : cout << "Fail";
    cout << endl;

    myTree.remove( 10 );    // Remove the root, what about now?
    cout << "   [t] size() with " << vals.size() - 1<< " values: " << myTree.size() << " - ";
    (vals.size() - 1  == myTree.size()) ? cout << "Pass" : cout << "Fail";
    cout << endl;
}


void test_height() {
    AvlTree<int> myTree;
    vector<int> vals = { 10, 5, 23, 3, 7, 30, 1 };   // Give us some data!
    cout << "  [t] Testing tree heights" << endl;
    cout << "   [t] Height of empty: " << myTree.height() << " - ";
    (myTree.height() == -1) ? cout << "Pass" : cout << "Fail";    cout << endl;

    myTree.insert(vals);
    cout << "   [t] Height of filled (3): " << myTree.height() << " - ";
    (myTree.height() == 3) ? cout << "Pass" : cout << "Fail";    cout << endl;
}


void test_prints() {
    AvlTree<int> myTree;
    vector<int> vals = { 10, 5, 23, 3, 7, 30, 1 };   // Give us some data!
    myTree.insert(vals);
    cout << "  [t] Testing tree print orders: " << endl;

    cout << "   [t] In Order: \t";
    myTree.printInOrder();
    cout << endl;

    cout << "   [t] Pre Order:\t";
    myTree.printPreOrder();
    cout << endl;

    cout << "   [t] Post Order:\t";
    myTree.printPostOrder();
    cout << endl;
}


void test_insert()
{
    AvlTree<int> myTree;
    cout << "  [t] Testing tree basic inserts: " << endl;
    myTree.insert(20);
    myTree.insert(10);
    myTree.insert(5);      // Forces right rotate
    cout << "   [t] Should be: \t10 5 20" << endl;
    cout << "   [t] Pre Order: \t";
    myTree.printPreOrder();
    cout << endl;

    myTree.insert(30);
    myTree.insert(40);     // Forces left rotate
    cout << "   [t] Should be: \t10 5 30 20 40" << endl;
    cout << "   [t] Pre Order: \t";
    myTree.printPreOrder();
    cout << endl;

    myTree.insert(15);     // Forces Right-Left double rotate
    cout << "   [t] Should be: \t20 10 5 15 30 40" << endl;
    cout << "   [t] Pre Order: \t";
    myTree.printPreOrder();
    cout << endl;

    myTree.insert(13);
    myTree.insert(14);     // Forces Left-Right double rotate
    cout << "   [t] Should be: \t20 10 5 14 13 15 30 40" << endl;
    cout << "   [t] Pre Order: \t";
    myTree.printPreOrder();
    cout << endl;
}


void test_contains() {
    AvlTree<int> myTree;
    vector<int> vals = { 10, 5, 23, 3, 7, 30, 1 };   // Give us some data!
    myTree.insert( vals );
    cout << "  [t] Testing contains:" << endl;
    cout << "   [t] Searching for: 7 (is in tree)";
    (myTree.contains(7)) ? cout << " - pass" : cout << " - fail"; cout << endl;

    cout << "   [t] Searching for: 15 (not in tree)";
    (!myTree.contains(15)) ? cout << " - pass" : cout << " - fail"; cout << endl;
}

/**
 *  Testing the remove() function
 */
void test_remove() {
    AvlTree<int> myTree;
    vector<int> vals = { 10, 5, 23, 3, 7, 30, 1 };   // Give us some data!
    myTree.insert( vals );
    cout << "  [t] Testing remove():" << endl;
    cout << "   [t] Searching for: 7 (is in tree)";
    (myTree.contains(7)) ? cout << " - pass" : cout << " - fail"; cout << endl;

    cout << "   [x] Removing 7 from tree. " << endl;
    myTree.remove(7);
    cout << "   [t] Searching for: 7 (is not in tree)";
    (!myTree.contains(7)) ? cout << " - pass" : cout << " - fail"; cout << endl;

}


/*
 *  Testing features of your AVL Tree implementation
 */
int avlTreeTests( bool fuzzing )
{
    cout << " [x] Starting AVL tree test. " << endl;
    test_empty();            // empty() interface working?
    test_size();             // size() interface working properly?
    test_height();           // height() working properly?
    test_prints();           // Print: preorder, postorder, inorder, levelorder
    test_insert();           // Insert test
    test_contains();         // Testing contains interface
    test_remove();           // Test of removing nodes via remove()
    if( fuzzing ) test_BigTreeFuzzing();   //Big tree fuzzing test

    return(0);
}
