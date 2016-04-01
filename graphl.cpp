 /*****************************************************************/
/* graphl.cpp
/*
/* Author: Kevin M Cain
/* Date: 01/26/2010
/* 
/* This implements an adjacency list, which represents a graph that is built from 
/* an input stream. The buildgraph function assumes that the input stream has 
/* correctly formated data. Other functions include performing a depth first search
/* and printing all graph data to the console. 
/*
/*****************************************************************/
#include "graphl.h"

//GraphL::lowestCostEdge(int) {
//
//}
//void GraphL::buildGraphPrim(istream& infile) {
//
//	infile >> this->size; // <-- Read the number of nodes	
//	if (size + 1 > MAXNODES) return;
//	if (infile.eof()) return; // <-- Stop if no more data
//   	infile.get(); // <-- Read end-of-line character
//
//	int v, w, dist;
//
//	for (;;) { 
//		
//		infile >> v >> w >> dist;
//		if (v > size || v < 0 || w > size || w < 0 ) continue; 
//		if (v ==0 && w ==0 && dist ==0) return; 
//
//		T[v][w] = 
//	
//}

/* GraphL - Contructor ***************************************************************
* Preconditions: None	
* Postconditions: Initializes size to zero
*/
GraphL::GraphL() {

	size = 0;
}

/* ~GraphL - Destructor **************************************************************
* Preconditions: None
* Postconditions: Calls makeEmpty, which will deallocate any dynamic memory
*/
GraphL::~GraphL()
{
	makeEmpty();
}

/* buildGraph *************************************************************************
* Preconditions: infile should contain formated data
* Postconditions: if addGraphNodes succeeds adding nodes, then addEdgeNodes will be called
*/
void GraphL::buildGraph(istream& infile) {

	makeEmpty();

	if (addGraphNodes(infile)) addEdgeNodes(infile);
}

/* addGraphNodes **********************************************************************
* Preconditions: infile should contain correctly formated data
* Postconditions: Array of nodes of the specified size will exist. Each
*                 node will contain data specified in the input file
*/
const bool GraphL::addGraphNodes(std::istream &infile){

	infile >> size; // <-- Read the number of nodes
	if (infile.eof()) return false; // <-- Stop if no more data
	if (size > MAXNODES - 1) return false; // <-- Size must not exceed the MAXNODES
   	infile.get(); // <-- Read end-of-line character
	for (int i=1; i <= size; i++)
	{
		adjList[i].data.setData(infile);
    }
	return true;
}

/* addEdgeNodes ***********************************************************************
* Preconditions: infile should contain correctly formated data
* Postconditions: Linked list is appened to the edgeHead ptr of specified node
*/
void GraphL::addEdgeNodes(std::istream &infile, int fromNode, int toNode) {
		
	for (;;) {

		infile >> fromNode >> toNode;

		// Prevent NULL reference or index outside of bounds exceptions
		if (fromNode > size || fromNode < 0 || toNode > size || toNode < 0 ) continue; 
		if (fromNode ==0 && toNode ==0) return; // <-- End of edge data

		EdgeNode *edgePtr = adjList[fromNode].edgeHead; // capture list if one exists
		adjList[fromNode].edgeHead = new EdgeNode(toNode);
		adjList[fromNode].edgeHead->nextEdge = edgePtr;
		edgePtr = NULL; // <-- Boas practicas
   } 
}

/* makeEmpty ************************************************************************
* Preconditions: None
* Postconditions: If a node in the array contains an edgeHead the delete EdgeList
*                 will be called (deleteEdgeList always returns NULL). All nodes
*                 in the array will be deleted.
*/
void GraphL::makeEmpty() {

	for (int i = 1; i <= size ; i++ ) { 
	
		adjList[i].data = NodeData();
		adjList[i].visited = false;

		if ( adjList[i].edgeHead == NULL ) continue;

		adjList[i].edgeHead = deleteEdgeList(adjList[i].edgeHead);
	}
}

/* deleteEdgeList *********************************************************************
* Preconditions: None
* Postconditions: Any nodes that edgeHead points to will be deleted
*/
EdgeNode * GraphL::deleteEdgeList(EdgeNode *edgeHead) {

	if (edgeHead == NULL) return NULL;
	edgeHead->nextEdge = deleteEdgeList(edgeHead->nextEdge);
	delete edgeHead;
	return NULL;
}

/* depthFirstSearch ********************************************************************
* Preconditions: adgList should contain atleast one node.
* Postconditions: Prints to the console the depth first odering of the graph
*/
void GraphL::depthFirstSearch() {

	cout << endl << "Depth-first ordering: ";
	for (int i = 1; i <= size ; i++ ) 
	{
		if ( !adjList[i].visited ) dfs(i);
	}
	cout << endl << endl;
}

/* dfs **********************************************************************************
* Preconditions: v should be an existing node in the array
* Postconditions: Prints node data to the consolem sets specified v node as visited
*/
void GraphL::dfs(const int v) {
	
	adjList[v].visited = true; // <-- Mark v as visited
		
	cout << v << " "; // <-- Display gives depth-first order
	
	// For each vertex w adjacent to v, if w is not visited then dfs
	EdgeNode *cur = adjList[v].edgeHead;
	while (cur != NULL)
	{
		if ( !adjList[cur->adjGraphNode].visited ) {

			dfs(cur->adjGraphNode);
		}
		cur = cur->nextEdge;
	}
}

/* displayGraph ***************************************************************************
* Preconditions: adjList should contain atleast one node
* Postconditions: all graph data info will be printed to the console.
*/
void GraphL::displayGraph() {

	cout << "Graph: " << endl;
	for (int i = 1; i <= size ; i++ ) { 
		cout << "Node " << i << "       " << adjList[i].data << endl;
		EdgeNode *cur = adjList[i].edgeHead;
		while (cur != NULL)
		{
			cout << "   edge " << i << " " << cur->adjGraphNode << endl;
			cur = cur->nextEdge;
		}
	}
}




///// The following data is code from my initial implementation of adjList, which was
///// the following declaration 'GraphNode *adjList[MAXNODES];' - An array of pointers
///// I concluded that this was not necessary so I removed the code and placed it here

///// addGraphNodes ------------------------------------------------------------------
 
/// adjList[i] = new GraphNode();
/// adjList[i]->data.setData(infile);

///// addEdgeNodes --------------------------------------------------------------------

/// EdgeNode *edgePtr = adjList[fromNode]->edgeHead;
/// adjList[fromNode]->edgeHead = new EdgeNode(toNode);
/// adjList[fromNode]->edgeHead->nextEdge = edgePtr;
/// edgePtr = NULL; // <-- Boas practicas

///// makeEmpty -----------------------------------------------------------------------

/// if (!(adjList[i]) == NULL && !adjList[i]->edgeHead == NULL )
///			adjList[i]->edgeHead = deleteEdgeList(adjList[i]->edgeHead);
/// if (!(adjList[i]) == NULL ){
///			delete adjList[i];
///			adjList[i] = NULL; }

///// depthFirstSearch ----------------------------------------------------------------

///	for (int i = 1; i <= size ; i++ ) 
///	{
///		if ( !(adjList[i]) == NULL && !adjList[i]->visited ){		
///			dfs(i);
///		}
///	}

///// dfs -----------------------------------------------------------------------------

/// adjList[v]->visited = true; // <-- Mark v as visited	
/// EdgeNode *cur = adjList[v]->edgeHead;
/// while (cur != NULL)
/// {
///	if ( !adjList[cur->adjGraphNode]->visited ) {
///		dfs(cur->adjGraphNode);
///	}
///	cur = cur->nextEdge; }