/****************************************
  Brian Jurgess
  CSE 331
  Project 7
*****************************************/

#include "graph.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int main( int argc, char *argv[] )
{
  if( argc != 3 )
    {
      cerr << "*** ERROR: Incorrect number of arguments ***\n";
      cerr << "***        ----------------------------- ***\n";
      cerr << "***        proj [graph_file] [trip_File] ***" << endl;
      return 1;
    }

  Graph map;
  string
    graphFile = argv[1],
    tripFile = argv[2];

  ifstream buildGraph;

  buildGraph.open( graphFile.c_str() );
  
  
  if( !buildGraph )
    {
      cout << "Unable to open file: " << graphFile << endl;
      cin.get();
      return 1;
    }

  string line;
  getline( buildGraph, line );
  // Begin building graph
  while( line != "EDGES" )
    {
      if( line != "VERTICES" )
	{
	  if(line.empty() == true) break;
	  else if(buildGraph.eof()) break;
	  else map.addVertex(line);
	}
      getline( buildGraph, line );
    }

  if( line == "EDGES" )
    {
      while(true)
	{
	  if( line != "EDGES" )
	    {
	      if(line.empty() == true) break;
	      else if( buildGraph.eof() ) break;
	      else map.addEdge(line);
	    }
	  getline( buildGraph, line );
	}
    }
  
  buildGraph.close();


  // Begin reading in the trips file.
  
  ifstream createTrip;

  createTrip.open( tripFile.c_str() );
  string tripType;
  string destinationOne;
  string destinationTwo;
  double distance = 0;
  int time, tempTime;
  
  vector< Graph::Edge > trip;
  vector< Graph::Edge > quickestTrip;
  
  while( !createTrip.eof() )
    {
      distance = 0;
      time = 0;
      getline( createTrip, tripType );
      getline( createTrip, destinationOne );
      getline( createTrip, destinationTwo );
      // If the trip type is "trip"
      
      if( tripType == "trip" )
	{
	  trip = map.shortest_path( destinationOne, destinationTwo );

	  reverse(trip.begin(),trip.end());
	  if( !trip.empty() )
	    {
	      cout << "Trip from " << destinationOne << " to " << destinationTwo << ":" << endl;
	      
	      for( unsigned i = 0; i < trip.size(); i++ )
		{
		  distance += trip[i].getDistance();
		  tempTime = (trip[i].getDistance()/trip[i].getSpeedlimit()) * 60;
		  time += tempTime;
		  cout << trip[i] << " ( " << trip[i].getDistance() << " Miles | " << tempTime << " Minutes )"  << endl;
		}
	      cout << "Total Distance: " << distance << " miles." << endl;
	      cout << "Total Time: " << time << " minutes." << endl << endl;
	    }
	  else
	    {
	      cout << "No path could be found." << endl << endl;
	    }
	}
      // If the trip type is "quicktrip"
      else if( tripType == "quicktrip" )
	{
	  quickestTrip = map.quickest_path( destinationOne, destinationTwo );

	  reverse(quickestTrip.begin(),quickestTrip.end());
	  if( !quickestTrip.empty() )
	    {
	      cout << "Quickest Path from " << destinationOne << " to " << destinationTwo << ":" << endl;
	      
	      for( unsigned i = 0; i < quickestTrip.size();i++ )
		{
		  distance += quickestTrip[i].getDistance();
		  tempTime = (quickestTrip[i].getDistance()/quickestTrip[i].getSpeedlimit()) * 60;
		  time += tempTime;
		  cout << quickestTrip[i] << " ( " << quickestTrip[i].getDistance() << " Miles | " << tempTime << " Minutes )" << endl;
		}
	      cout << "Total Distance: " << distance << " miles. " << endl;
	      cout << "Total Time: " << time << " minutes." << endl << endl;
	    }
	  else
	    {
	      cout << "No path could be found." << endl << endl;
	    }
	}
            
    }
  createTrip.close();
  

  return 0;
  
}
