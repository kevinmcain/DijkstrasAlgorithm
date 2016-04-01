//---------------------------------------------------------------------------
// prog1.cpp
//---------------------------------------------------------------------------
// This code tests all of the basic functionality of the classes to
// perform depth-first search and Dijkstra's algorihms.
// It is not meant to do exhaustive testing. 
//
// Assumptions:
//   -- Students can follow the directions to interface with this file
//   -- Text files "data11.txt" and "data12.txt" are formatted as described 
//   -- Data file data1uwb.txt provides an additional data set for part 2;
//      it must be edited, as it starts with a description, to be used
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graph.h"
using namespace std;

int main() {
   // part 1 
   ifstream infile1("data11.txt");
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
 
   // part 2
   ifstream infile2("data12.txt");
   if (!infile2) {
      cerr << "File could not be opened." << endl;
      return 1;
   }

   //for each graph, find the shortest path from every node to all other nodes
   for(;;){
      GraphM G;
      G.buildGraph(infile2);
      if (infile2.eof()) 
         break;
      G.findShortestPath();        
      G.displayAll();              // display shortest distance, path to cout
      G.display(3,1);              // display path from node 3 to 1 to cout
      // may be other calls to display 
   }

   cout << endl;
   return 0;
}

