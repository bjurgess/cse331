//
//All file writen by C. Owen for CSE331
//Modified by A.W. Covert III 
//
// Name :        main.cpp
// Description : Demonstration program that shows how to load the data from the 
//               Internet Movie Database actors list file.  
// Notice :      Running this program as is will require about 250MB of memory.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "Actors.h"
#include "InsertionSort.h"
#include "moviepointer.h"

//const char *ACTORSFILE = "actors.list.sm.txt";

using namespace std;

string actorsfile;


int main(int argc, char *argv[])
{
  // Create the class that will hold all of our actors
  CActors     actors;
  time_t	t1, t2;
  if(argc != 3){
      cerr << "ERROR: incorrect number of command line arguments." << endl;
      cerr << "\t<prompt>insertsort [numtosort] [datafile]" << endl;
      return 0;
  }

  
  unsigned increment = atoi(argv[1]);

  if(increment < 1) {
      cerr << "ERROR: invalid number of records" << endl;
      return 0;
  }

  actorsfile = argv[2];
  
  double ti = 0.0;

  while(ti < 600){
    if(!actors.Load(actorsfile.c_str(), increment)){
	cin.get();
	return 1;
    }
        
    cout << "There are " << actors.GetNumActors() << " actors" << endl;
    
    std::vector<CMoviePointer> *movies = actors.GetMovies();

	
    CInsertionSort<CMoviePointer> iSort;

    t1 = time(0);
    iSort.Sort(movies);
    t2 = time(0);
		
    ti = difftime(t2,t1);

    std::cout << "Increment: " << increment << std::endl;
    std::cout << "Time passed: " << ti << std::endl;
    std::cout << "Movies: " << movies->size() << std::endl;
    increment += 10;
    std::cout << "----------------------" << endl;
    
    //    for(unsigned i = 0; i < movies->size(); i++) std::cout << movies->at(i).GetMovie() << std::endl;

    //    ti = 601;
  }
  cin.get();
  return EXIT_SUCCESS;
}


