//---------------------------------------------------------------------------
// main.cpp
// 
// Authors: Kevin M Cain
//---------------------------------------------------------------------------
// 
// 
//
// Assumptions: The text file named "" exists within the execution directory.
//              The input data file has correctly formatted data.
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"

using namespace std;

int main()
{

	GraphL graph;

		// create file object and open the datafile
	ifstream infile1("data12.txt");
	if (!infile1) {
		cerr << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, display graph and find the depth-first search ordering
	for (;;) {
		GraphL G;
		G.buildGraph(infile1);
		if (infile1.eof()) 
			break;
		G.displayGraph();
		G.depthFirstSearch();    // find and display depth-first ordering to cout
	}


	//// create file object and open the datafile
	//ifstream infile1("data11.txt");
	//if (!infile1) {
	//	cerr << "File could not be opened." << endl;
	//	return 1;
	//}

	////for each graph, display graph and find the depth-first search ordering
	//for (;;) {
	//	GraphL G;
	//	G.buildGraph(infile1);
	//	if (infile1.eof()) 
	//		break;
	//	G.displayGraph();
	//	G.depthFirstSearch();    // find and display depth-first ordering to cout
	//}

	//ifstream infile2("data12.txt");
	//if (!infile2) {
	//	cerr << "File could not be opened." << endl;
	//	return 1;
	//}

	//for each graph, find the shortest path from every node to all other nodes
	//for(;;){
	//	GraphM G;
	//	G.buildGraph(infile2);
	//	if (infile2.eof()) 
	//		break;
	//	G.findShortestPath();        
	//	G.displayAll();              // display shortest distance, path to cout
	//	G.display(1,4);              // display path from node 3 to 1 to cout
	//	// may be other calls to display 
	//}

	cout << endl;
	return 0;

}