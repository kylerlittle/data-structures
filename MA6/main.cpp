/*
 *  Dijkstra's Algorithm 
 *   Aaron S. Crandall, 2017 - <acrandal@gmail.com>
 */

#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <string.h>
#include "Graph.h"
#include "Vertex.h"

using namespace std;

/**
 *  Test the graph algorithm with the graph from the class textbook
 *  Graph may be found on page 394 and in bookGraph.png
 */
void run_BookGraphTest()
{
	cout << " [d] Testing Book graph (small graph) tests." << endl;

	Graph graph{};
	graph.loadDotFile( "bookGraph.dot" );
	cout << "  [d] Current graph structure from book's graph: " << endl;
	cout << "  [x] Book Graph vertices: " << graph.size() << endl;
	cout << "  [x] Book Graph edges: " << graph.edges_size() << endl;
	cout << "   [d] k = known  || pw = path weight || p = parent node " << endl;
	cout << graph.to_string( true ) << endl;

	cout << "  [d] ** Starting Dijkstra Here From ID #1 **" << endl;
	cout << "   [d] Resulting graph status: " << endl;

	int startingID = 1;
	graph.dijkstra( startingID );
	cout << graph.to_string( ) << endl;

	cout << "  [d] Showing routes in book's graph (with edges): " << endl;
	vector<double> correct = 
		{std::numeric_limits<double>::infinity(), 0, 2, 3, 1, 3, 6, 5};
	for( int destid = 0; destid < graph.size(); destid++ ) {
		if( graph.get_vertice_path_weight( destid ) == correct[ destid ] ) {
			cout << "    Pass | ";
		} else {
			cout << "    Fail | ";
		}
		cout << graph.path_to_string( 1, destid ) << endl;
	}
	cout << endl;

	correct = {std::numeric_limits<double>::infinity(), 9, 0, 5, 3, 5, 8, 7};
	for( int destid = 0; destid < graph.size(); destid++ ) {
		if( graph.get_vertice_path_weight( destid ) == correct[ destid ] ) {
			cout << "    Pass | ";
		} else {
			cout << "    Fail | ";
		}
		cout << graph.path_to_string( 2, destid ) << endl;
	}

	cout << endl;
	cout << "  [d] Longest Path to ID #1 is (1,4,7,6): " << endl;
	cout << "         | " << graph.path_to_string( graph.get_longest_path( 1 ) ) << endl;

	cout << " [d] Book graph tests complete. " << endl;
}

/**
 *  Test the graph algorithm with the graph from the class textbook
 *  Graph may be found on page 394 and in bookGraph.png
 */
void run_MouseBrainGraphTest() {
	cout << endl << "--------------------------------------------------" << endl;
	cout << " [d] Running Big Test with Mouse Brain Graph" << endl;

	Graph graph{};
	graph.loadDotFile( "MouseBrainGraph.dot" );
	//cout << graph.to_string( ) << endl;
	cout << "  [x] Mouse Brain vertices: " << graph.size() << endl;
	cout << "  [x] Mouse Brain edges: " << graph.edges_size() << endl;

	cout << "  [d] Current graph structure from ID #1 to brain verts: " << endl;
	int startingID = 1;
	graph.dijkstra( startingID );
	cout << graph.to_string( ) << endl;

	cout << endl;
	cout << "  [d] Longest Path to ID #1 is: " << endl;
	cout << "   | Could be (0.000055): 1, 42, 110, 65, 13, 137, 119, 8, 61, 74" << endl;
	cout << "   | " << graph.path_to_string( graph.get_longest_path( 1 ) ) << endl;

	cout << endl;
	cout << "  [d] Longest Path to ID #80 is: " << endl;
	cout << "   | Could be (0.000242): 80, 59, 202, 209, 148, 164, 21, 106, 181, 12, 82, 46" << endl;
	cout << "   | " << graph.path_to_string( graph.get_longest_path( 80 ) ) << endl;

	return;
}


/**
 *  Test mode operations
 */
void run_test_mode( bool bigtest = false ) {
	cout << " [t] Running in test mode. " << endl;
	run_BookGraphTest();

	if( bigtest )
		run_MouseBrainGraphTest();
	cout << " [t] All tests complete. " << endl;
}


/**
 *  Normal mode execution for general user control
 */
void run_normal_mode() {
	cout << "  [!] Nothing to do in normal mode so here's a hat: " << endl;

cout <<""
"       _.-'`'-._\n"
"    .-'    _    '-.\n"
"     `-.__  `\\_.-'\n"
"       |  `-``\\|\n"
" jgs   `-.....-A\n"
"               #\n"
"               #\n";
	cout << endl;
	cout << " Oh, and you should probably run 'make test' to test your program. \n"
" To run the mouse brain graph, use 'make bigtest', which takes about 15 sec for me. \n"
" You'll find images of the graphs we're using in:\n"
"     bookGraph.png\n"
"     MouseBrainGraph.png (currently being built - fingers crossed)\n"
"\n"
" Both built using: neato -Tpng bookGraph.dot -o bookGraph.png\n"
" Both built using: neato -Tpng MouseBrainGraph.dot -o MouseBrainGraph.png\n";
}




/**
 *  Main function for test or use
 */
int main( int argc, char* argv[] )
{
	int retState = 0;

	// Note: If you call this program like this: ./Dijkstra --test
	//  it will call the test function
	if( argc > 1 && !strcmp(argv[1], "--bigtest" )  )
	{
		run_test_mode( true );
		cout << " [x] BIGTEST testing program complete. " << endl;
	}
	else if( argc > 1 && !strcmp(argv[1], "--test" ) )
	{
		run_test_mode( );
		cout << " [x] Testing program complete. " << endl;
	}
	else
	{
		cout << " [x] Running in normal mode. " << endl;

		run_normal_mode();
	}
}

