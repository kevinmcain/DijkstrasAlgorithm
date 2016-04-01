 /*****************************************************************/
/* graphl.h
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
#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"

struct EdgeNode; // forward reference for the compiler

struct GraphNode {
	
	GraphNode() { // constructor to initialize values
	
		edgeHead = NULL;
		visited = false;
	};

	EdgeNode* edgeHead;
	NodeData data;
	bool visited;
};

struct EdgeNode { //constructor to initialize values

	EdgeNode(const int adjGraphNode){
		this->adjGraphNode = adjGraphNode;
		nextEdge = NULL;
	}

	int adjGraphNode; // subscript of the adjacent graph node
	EdgeNode* nextEdge;
};

class GraphL {

public:

	/* GraphL - Contructor ***************************************************************
	* Preconditions: None	
	* Postconditions: Initializes size to zero
	*/
	GraphL();
	
	/* ~GraphL - Destructor **************************************************************
	* Preconditions: None
	* Postconditions: Calls makeEmpty, which will deallocate any dynamic memory
	*/
	~GraphL();

	/* buildGraph *************************************************************************
	* Preconditions: infile should contain formated data
	* Postconditions: if addGraphNodes succeeds adding nodes, then addEdgeNodes will be called
	*/
	void buildGraph(istream& infile);

	/* displayGraph ***************************************************************************
	* Preconditions: adjList should contain atleast one node
	* Postconditions: all graph data info will be printed to the console.
	*/
	void displayGraph();

	/* depthFirstSearch ********************************************************************
	* Preconditions: adgList should contain atleast one node.
	* Postconditions: Prints to the console the depth first odering of the graph
	*/
	void depthFirstSearch();

	int lowestCostEdge(const int u);
	void buildGraphPrim(istream& infile);

private:

	int size;
	const static int MAXNODES = 100;
	GraphNode adjList[MAXNODES];

	int T[MAXNODES][MAXNODES];

	/* addGraphNodes **********************************************************************
	* Preconditions: infile should contain correctly formated data
	* Postconditions: Array of nodes of the specified size will exist. Each
	*                 node will contain data specified in the input file
	*/
	const bool addGraphNodes(istream &infile);

	/* addEdgeNodes ***********************************************************************
	* Preconditions: infile should contain correctly formated data
	* Postconditions: linked list is appened to the edgeHead ptr of specified node
	*/
	void addEdgeNodes(istream& infile, int fromNode = 0, int toNode = 0);

	/* makeEmpty ************************************************************************
	* Preconditions: None
	* Postconditions: If a node in the array contains an edgeHead the delete EdgeList
	*                 will be called (deleteEdgeList always returns NULL). All nodes
	*                 in the array will be deleted.
	*/
	void makeEmpty();

	/* deleteEdgeList *********************************************************************
	* Preconditions: None
	* Postconditions: Any nodes that edgeHead points to will be deleted
	*/
	EdgeNode* deleteEdgeList(EdgeNode *edgeHead);

	/* dfs **********************************************************************************
	* Preconditions: v should be an existing node in the array
	* Postconditions: Prints node data to the consolem sets specified v node as visited
	*/
	void dfs(const int v);

};

#endif