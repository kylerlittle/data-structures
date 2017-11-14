/**
 *  Core graph data structure
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <list>

#include "Vertex.h"

using namespace std;

class Graph
{
	vector<Vertex*> _vertices;		// All vertices in the graph (vertex id == index)
	int _last_startingID = -1;

public:
	// Remove all vertices
	void clear() {
		_vertices.clear();
	}

	// Number of vertices in our graph
	int size() {
		return _vertices.size();
	}

	int edges_size() {
		int count = 0;
		for( auto vert : _vertices ) {
			count += vert->edges_size();
		}
		return(count);
	}

	/**
	 *  Parses a single in from a dot file
	 */
	void parseDotfileLine( string line ) {
		smatch matched;
		regex newSubGraph ("\\s*(\\S+)\\s*->\\s*(\\S+)\\s*\\[.*?weight=\"*(\\S+?)\"*\\s*\\]\\;");

		if( regex_match( line, matched, newSubGraph ) ) {
			string strconv = matched[1];
			int srcid = ::atof(strconv.c_str());
			strconv = matched[2];
			int destid = ::atof(strconv.c_str());
			strconv = matched[3];
			double weight = ::atof(strconv.c_str());
			//cout << "SrcID: " << srcid << " | DestID: " << destid << " | Edge Weight: " << weight << endl;

			// Grow set of vertices if new high id is inserted or connected to
			int growVerts = max(srcid, destid);
			for( int i = _vertices.size(); i <= growVerts; i++ ) {
				Vertex* newVert = new Vertex(i);		// Allocate the new vertex
				_vertices.push_back( newVert );		// Add vertex to the end of the list 
			}
			_vertices[srcid]->addEdge(_vertices[destid], weight);
		}
	}

	/**
	 *  Loads a single Graphviz-(limited) formatted dot file with a graph
	 */
	void loadDotFile( string filename ) {
		cout << " [d] Loading dot file: " << filename;
		ifstream ifs( filename );
		string instr;
		while (getline(ifs, instr)) {
			parseDotfileLine( instr );
		}
		cout << " - Done." << endl;
	}

	/**
	 *  Returns stringified version of graph for viewing
	 */
	string to_string( bool with_edges = false ) {
		string ret = "";
		for( auto vert : _vertices ) {
			ret += vert->to_string( with_edges ) + "\n";
		}
		return ret;
	}

	/**
    *  Returns longest path (most edges) from a given startingID
    */
	list<Vertex*> get_longest_path( int startingID ) {
		list<Vertex*> longestPath;

		for( int currDestID = 0; currDestID < size(); currDestID++ ) {
			list<Vertex*> currPath = get_path( startingID, currDestID );
			if( currPath.size() > longestPath.size() )
				longestPath = currPath;
		}
		return longestPath;
	}

	/**
	 *  Returns a list of the route from one ID to another
	 */
	list<Vertex*> get_path( int startingID, int endingID ) {
		dijkstra( startingID );	// Only runs if updated startingID

		list<Vertex*> retPath;
		stack<Vertex*> path_stack;

		Vertex* currVert = _vertices[ endingID ];
		if( !currVert->get_path() )
			return retPath;		// Returns empty path because no route

		path_stack.push(currVert);
		while( currVert->get_path() ) {
			currVert = currVert->get_path();
			path_stack.push(currVert);
		}
		while( !path_stack.empty() ) {
			currVert = path_stack.top();
			path_stack.pop();
			retPath.push_back( currVert );
		}
		return retPath;
	}

	/**
	 *  Returns a string of the route for a given path
	 */
	string path_to_string( list<Vertex*> path ) {
		if( !path.empty() )
			return path_to_string( path.front()->getId(), path.back()->getId() );
		else
			return "Empty path";
	}

	/**
	 *  Returns a string of the route from one ID to another
	 */
	string path_to_string( int startingID, int endingID ) {
		list<Vertex*> path = get_path( startingID, endingID );

		string ret = "Route from " + std::to_string(startingID);
		ret += " to " + std::to_string(endingID);
		ret += " (weight = " + std::to_string(_vertices[ endingID ]->getPathWeight()) + ") : ";

		if( !path.empty() ) {
			while( !path.empty() ) {
				Vertex* currVert = path.front();
				path.pop_front();
				ret += std::to_string( currVert->getId() );
				if( !path.empty() ) {
					ret += " -> ";
				}
			}
		} else {
			ret += "No path found ";
		}

		return ret;
	}

	/**
	 *  Get ID's weight
	 */
	double get_vertice_path_weight( int id ) {
		return _vertices[ id ]->getPathWeight();
	}

	/**
	 *  Undo a run of Dijkstra's
	 */
	void reset_vertices() {
		for( auto vert : _vertices ) {
			vert->setPathWeight( std::numeric_limits<double>::infinity() );
			vert->unset_known();
			vert->set_path( nullptr );
		}
	}

	// Dijkstra MA: IMPLEMENT
	void dijkstra( int startingID ) {
		if( startingID == _last_startingID ) {
			 	// This is just to save time in finding paths
			return; // Already did this graph with that starting ID!
		}
		_last_startingID = startingID;
		reset_vertices(); // If you're doing a new startingID, clear out old dijkstra's results

		// This builds a priority queue sorted by the path weights of the vertices in it (min heap)
		priority_queue<Vertex*, vector<Vertex*>, PathWeightComparer> dijkstra_queue{};

		// End of hints - Dijkstra's Algorithm Goes here:

	}
	// DONE WITH MA

};

#endif
