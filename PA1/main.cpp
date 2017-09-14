/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 * Now also doing testing & height calculations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *  * Also doing height calculations
 *
 */

#include <iostream>
#include <iomanip>
#include <queue>
#include <cstring>
#include <cmath>        // log2
#include <fstream>
#include "BST.h"
#include "TestData.h"
using namespace std;

#define NUM_TREES 7
#define SCRAMBLED_SETS 5

/*
 *  Interface to run all tests if --test is passed on command line
 */
void runTests() {
    cout << " [x] Running tests. " << endl;
    TestData *testing = new TestData();			// Create object with testing data and interfaces

    BST<int> *bst_test = new BST<int>;

	/* Should make a tree like this:
              10
         5          14
     1      7           17
                            19
                          18

   */
    int testval = testing->get_next_minitest();
    while( testval >= 0 ){
        bst_test->add( testval );
        testval = testing->get_next_minitest();
    }
    cout << " [x] Should print out in pre order: 10 5 1 7 14 17 19 18 " << endl;
    cout << " [x] Resulting print out test:      ";
    bst_test->printPreOrder();
    cout << endl;

    cout << " [x] Should print a tree height of  : 5" << endl;
    cout << " [x] Currently calculating height of: ";
    cout << bst_test->height();
    cout << endl;
    
    delete testing;
}

void initTrees(vector<BST<int> *> &treeVec, int numTrees) {
    int numTreesAdded = 0;
    while (numTreesAdded < numTrees) {
        treeVec.push_back(new BST<int>{});
        ++numTreesAdded;
    }
}

/*
 * Generate the CSV file for the project output here
 */
void genCSV() {
    cout << " [x] Generating CSV output file. " << endl;
    
    // Create/open a file for output.
    std::ofstream output;
    output.open("OutputData-BST.csv", std::ios_base::out);  // open file for output mode (it's the default, but just in case...)
    
    // Make 7 trees (sorted, balanced, scrambled[0...4])
    vector<BST<int> *> trees;
    initTrees(trees, NUM_TREES);        // seven trees total
    
    // Make test data.
    TestData *testing = new TestData{};
    
    // Output Headers
    output << "N,log_2(N),Sorted,Balanced,Scrambled #0,Scrambled #1,Scrambled #2,Scrambled #3,Scrambled #4" << endl;

    int addToBST = testing->get_next_sorted(), N = 1;
    while (addToBST >= 0) {
        output << N << ",";     // would have implemented nodesCount()... but that's just unnecessary work
        output << setprecision(3) << fixed << std::log2(static_cast<double>(N)) << ",";     // output 3 decimals points max because it looks prettier
        
        // Sorted Tree ------ index 0 of trees vector
        trees.at(0)->add(addToBST);
        output << trees.at(0)->height() << ",";
        
        // Balanced Tree ------ index 1 of trees vector
        addToBST = testing->get_next_balanced();
        trees.at(1)->add(addToBST);
        output << trees.at(1)->height() << ",";
        
        // Scrambled Trees ------ indices 2-6 of trees vector
        for (int i = 0; i < SCRAMBLED_SETS; ++i) {
            addToBST = testing->get_next_scrambled(i);      // get next scrambled from set i of scrambled sets
            trees.at(i + 2)->add(addToBST);     // i + 2, since we're referring to indices 2-6 of trees vector
            output << trees.at(i + 2)->height();     // output the height
            if (i == SCRAMBLED_SETS - 1)
                output << endl;
            else
                output << ",";
        }
        
        // Update conditional. Update N.
        addToBST = testing->get_next_sorted();      // If -1, we won't enter the loop next time.
        ++N;
    }
    
    // Close file.
    output.close();
    
    // Delete tests.
    delete testing;
}


/*
 *   Main function for execution
 */
int main( int argc, char* argv[] ) {
	if( argc > 1 && !strcmp(argv[1], "--test") )
	{
		cout << " [x] Program in test mode, doing simple tests. " << endl;
		runTests();  // testing should just do a simple tree insert set and search
	}
	else
	{
		cout << " [x] Program built and running in full CSV generation mode. " << endl;
		genCSV();
	}
	return 0;
}
