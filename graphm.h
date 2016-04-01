 /*****************************************************************/
/* graphm.h
/*
/* Author: Kevin M Cain
/* Date: 01/27/2010
/*
/* Implements cost matrix with data array and node table which keeps track
/* of the path and distance info. FindShortestPath implements Dijkstra's 
/* algorithm while display functions will print info about the shortest path
/*
/*****************************************************************/
#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"

class GraphM {


public:

/* GraphM - Constructor ********************************************************************
* Preconditions: None
* Postconditions: Initializes size to zero
*/
GraphM();

/* ~GraphM - Destructor ********************************************************************
* Preconditions: None 
* Postconditions: None 
*/
~GraphM();

/* buildGraph ******************************************************************************
* Preconditions: infile must be initialized
* Postconditions: Cost matrix and data array will contain data from infile
*/
void buildGraph(istream& infile);

/* findShortestPath - Dijkstra's shortest path algorithm ***********************************
* Preconditions: T, data, and C, must be initialized, with data and C containing graph info
* Postconditions: T will contain all necessary data to determine the shortest path for each node as the source
*/
void findShortestPath();        

/* displayAll ******************************************************************************
* Preconditions: The function 'findShortestPath' must be called before this
* Postconditions: Displays all shortest path info for every node being the source
*/ 
void displayAll();              

/* display *********************************************************************************
* Preconditions: The function 'findShortestPath' must be called before this
* Postconditions: Displays output for Dijkstra's shortest path
*/
void display(const int fromNode, const int toNode); 

/* insertEdge ******************************************************************************
* Preconditions: The cost matrix must contain the valid index
* Postconditions: inserts an edge at the specified coordinates. If the the specified indexs
*                 are out of range (Greater than MAXNODES, less than 1) nothing happens
*                 returns true if successful, otherwise false. Overwrites existing edges
*/
bool insertEdge(const int fromNode, const int toNode, const int dist);

/* removeEdge ******************************************************************************
* Preconditions: The cost matrix must contain the valid index
* Postconditions: The corresponding C[fromNode][toNode] value is set to infinity.
*                 returns true if successful otherwise false
*/
bool removeEdge(const int fromNode, const int toNode);

private:

struct TableType {

	TableType() {

		path = 0; // Set to zero (all k)
		dist = INFINITY; // Set to INFINITY (all k)
		visited = false; // Set to false (all k)
	}

	bool visited; // Whether node has been visited
	int dist; // Shortest distance from source known so far
	int path; // Previous node in path of min dist
};

int size; // <-- Nodes in the graph
const static int INFINITY = INT_MAX;
const static int MAXNODES = 100;
NodeData data[MAXNODES]; // Data for graph nodes
int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path

/* Display - Displays the shortest path inline *********************************************
* Preconditions: The function 'findShortestPath' must be called before this
* Postconditions: Will display the path from one node to another node
*/
void Display(const int fromNode, const int toNode);

/* DisplayData *****************************************************************************
* Preconditions: The function 'findShortestPath' must be called before this
* Postconditions: Displays the data in sequence of the shortest path
*/
void DisplayData(const int fromNode, const int toNode);

/* GetNextV ********************************************************************************
* Preconditions: T must be initialized with values, otherwise returns 0
* Postconditions: Returns the not yet visited node with the minimum distance
*/
int GetNextV(const int source) const;

};

#endif