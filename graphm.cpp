 /*****************************************************************/
/* graphm.cpp
/*
/* Author: Kevin M Cain
/* Date: 01/27/2010
/* 
/* Implements cost matrix with data array and node table which keeps track
/* of the path and distance info. FindShortestPath implements Dijkstra's 
/* algorithm while display functions will print info about the shortest path
/*
/*****************************************************************/
#include "graphm.h"

/* GraphM - Constructor ********************************************************************
* Preconditions: None
* Postconditions: Initializes size to zero
*/
GraphM::GraphM() {

	this->size = 0;
}

/* ~GraphM - Destructor ********************************************************************
* Preconditions: None 
* Postconditions: None 
*/
GraphM::~GraphM() {

}

/* buildGraph ******************************************************************************
* Preconditions: infile must be initialized
* Postconditions: Cost matrix and data array will contain data from infile
*/
void GraphM::buildGraph(istream& infile) {          
   
	infile >> this->size; // <-- Read the number of nodes	

	if (size + 1 > MAXNODES) return;

	if (infile.eof()) return; // <-- Stop if no more data

   	infile.get(); // <-- Read end-of-line character
   	
	// Builds the array of node data and sets all cost matrix values to INFINITY
	for (int i=1; i <= size; i++) {

		data[i].setData(infile);

		for (int j = 1; j <= size; j++)
		{
			C[i][j] = INFINITY;
		}
    }

	int v, w, dist;

	// Fills the cost matrix with edge information along with distance of each edge
	for (;;) { 
		
		infile >> v >> w >> dist;
		if (v > size || v < 0 || w > size || w < 0 ) continue; 
		if (v ==0 && w ==0 && dist ==0) return; 
		C[v][w] = dist;
   } 
}

/* display *********************************************************************************
* Preconditions: The function 'findShortestPath' must be called before this
* Postconditions: Displays output for Dijkstra's shortest path
*/
void GraphM::display(const int fromNode, const int toNode) {

	if (fromNode > size || toNode > size)
	{
		cout << "One or both of the nodes specifed does not exist" << endl << endl;
		return;
	}

	if (T[fromNode][toNode].path == 0) {
		cout << "There is no path from node " << fromNode << " to node " << toNode << endl << endl;
	}
	else {

		cout << "Path for " << fromNode << " to " << toNode	
			 << "  Distance  " << T[fromNode][toNode].dist << "	 ";
		Display(fromNode, toNode);
		cout << endl << endl;
		DisplayData(fromNode, toNode);
		cout << endl;
	}
}

/* Display - Displays the shortest path inline *********************************************
* Preconditions: The function 'findShortestPath' must be called before this
* Postconditions: Will display the path from one node to another node
*/
void GraphM::Display(const int fromNode, const int toNode) {

	if (toNode == 0) return;
	Display(fromNode, T[fromNode][toNode].path);
	cout << toNode << " ";
}

/* DisplayData *****************************************************************************
* Preconditions: The function 'findShortestPath' must be called before this
* Postconditions: Displays the data in sequence of the shortest path
*/
void GraphM::DisplayData(const int fromNode, const int toNode) {

	if (toNode == 0) return;
	DisplayData(fromNode, T[fromNode][toNode].path);
	cout << data[toNode] << endl;
}

/* displayAll ******************************************************************************
* Preconditions: The function 'findShortestPath' must be called before this
* Postconditions: Displays all shortest path info for every node being the source
*/ 
void GraphM::displayAll() {

	cout << "Description			From node	To node	 Dijkstra's Path" << endl;

	for (int source = 1; source <= size; source++) {
		cout << data[source] << endl;
		for (int i = 1; i <= size; i++) {
			
			if ( source == i ) continue;

			cout << "				" << source << "		" << i << "	 ";

			if (T[source][i].path == 0) {

				cout << "---";

			} else
			{
				cout << T[source][i].dist << "         ";
				Display(source, i);
			}
			cout << endl;
		}
	}
	cout << endl;
}

/* findShortestPath - Dijkstra's shortest path algorithm ***********************************
* Preconditions: T, data, and C, must be initialized, with data and C containing graph info
* Postconditions: T will contain all necessary data to determine the shortest path for each node as the source
*/
void GraphM::findShortestPath() {

	for (int source = 1; source <= size; source++) {

		T[source][source].dist = 0;

		for (int i = 1; i < size; i++) { // <-- For each node ( v )

			int v = GetNextV(source);
			T[source][v].visited = true; // <-- Mark v as visited
			
			for ( int w = 1; w <= size; w++) { // <-- For each node ( w ) adjacent to v

				// If node has been visited or there's no adjacent node then continue
				if ( T[source][w].visited || C[v][w] == INFINITY ) continue;

				if ( T[source][v].dist + C[v][w] < T[source][w].dist)
				{
					T[source][w].dist = T[source][v].dist + C[v][w];
					T[source][w].path = v;
				}			
			}
		}
	}
}

/* GetNextV ********************************************************************************
* Preconditions: T must be initialized with values, otherwise returns visited
* Postconditions: Returns the not yet visited node with the minimum distance
*/
int GraphM::GetNextV(const int source) const
{
	// I know, I know muito ineficiente, meu primeiro plano era melhor
	int lowest = INFINITY;
	int nextV = source;
	for (int i = 1; i <= size; i++)
	{
		if ( T[source][i].visited ) continue;
		if ( T[source][i].dist < lowest )
		{
			lowest = T[source][i].dist;
			nextV = i;
		}
	}
	return nextV;
}

/* insertEdge ******************************************************************************
* Preconditions: The cost matrix must contain the valid index
* Postconditions: inserts an edge at the specified coordinates. If the the specified indexs
*                 are out of range (Greater than MAXNODES, less than 1) nothing happens
*                 returns true if successful, otherwise false. Overwrites existing edges
*/
bool GraphM::insertEdge(const int fromNode, const int toNode, const int dist)
{
	if (fromNode > size || toNode > size || fromNode < 1 || toNode < 1) 
	{
		cout << "Unable to insert edge from node " << fromNode << " to node " << toNode << endl; 
		return false;
	}
	C[fromNode][toNode] = dist;
	return true;
}

/* removeEdge ******************************************************************************
* Preconditions: The cost matrix must contain the valid index
* Postconditions: The corresponding C[fromNode][toNode] value is set to infinity
*/
bool GraphM::removeEdge(const int fromNode, const int toNode)
{
	if (fromNode > size || toNode > size || fromNode < 1 || toNode < 1)
	{
		cout << "Unable to remove edge from node " << fromNode << " to node " << toNode << endl; 
		return false;
	}
	C[fromNode][toNode] = INFINITY;
	return true;
}





/* findShortestPath - Dijkstra's shortest path algorithm
* Preconditions: T, data, and C, must be initialized, with data and C containing graph info
* Postconditions: T will contain all necessary data to determine the shortest path for each node as the source
*/
//void GraphM::findShortestPath() {
//
//	int v, nextv;
//
//	for (int source = 1; source <= size; source++) {
//
//		T[source][source].dist = 0;
//		v = source;
//
//		for (int i = 1; i < size; i++) { // <-- For each node (v)
//
//			T[source][v].visited = true;// <-- Mark v as visited
//
//			int lowest = INFINITY;
//
//			// For each node (w) adjacent to v
//			for ( int w = 1; w <= size; w++) {
//
//				// If node has been visited or there's no adjacent node, continue
//				if ( T[source][w].visited || C[v][w] == INFINITY ) continue;
//
//				if ( T[source][v].dist + C[v][w] < T[source][w].dist)
//				{
//					T[source][w].dist = T[source][v].dist + C[v][w];
//					T[source][w].path = v;
//				}
// 
//				// Maintain that the nextv will have the lowest distance
//				if ( T[source][w].dist < lowest )
//				{
//					lowest = T[source][w].dist;
//					nextv = w;
//				}
//			}
//
//			v = nextv; // <-- The next v will be the lowest 
//		}
//	}
//}
