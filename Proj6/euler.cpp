/**********************************
  Brian Jurgess
  CSE 331
  Project 6

********************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "eulercircuit.h"
#include <list>;				\
  

using namespace std;

int main(int argc, char *argv[])
{
  if( argc != 2 )
    {
      cerr << "Incorrect number of command line arguments." << endl;
      cerr << "\t <Prompt> euler [adjacency list file]" << endl;
      return 1;
    }
  Graph myGraph;
  
  string adjacency_file = argv[1];

  ifstream instream;

  instream.open(adjacency_file.c_str());

  string test;

  for(;;)
    {
      getline(instream, test);
      if(test.empty() == true)
	{
	  break;
	}
      myGraph.addVertex(test);
      if(instream.eof())
	{
	  break;
	}
    }
  instream.close();

  myGraph.addEdges();

  vector<Graph::Vertex> dfs;
  dfs = myGraph.DFS(3);

  //cout << dfs << endl;
  
  
  return 0;
  

}
