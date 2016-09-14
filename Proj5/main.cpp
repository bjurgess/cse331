//
//All files writen by C. Owen for CSE331 FS06
//Modified by A.W. Covert III 
//
//
// Name :        main.cpp
// Description : Demonstration program that shows how to load the data from the 
//               Internet Movie Database actors list file.  
//

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "Actors.h"
#include "Tree.h"

#include "Movie.h"
#include "Actor.h"

#include "CTAGradeHook.h"

//const char *ACTORSFILE = "\\\\samba\\cse331\\sw_test2.txt";

// Set to larger number to read more of the database or -1 to read it all.
//const int LIMIT = -1;

using namespace std;



int main(int argc, char *argv[])
{
  //
  // Get the test data file
  //

  if(argc != 4){
    cerr << "Incorrect number of comand line arguments." << endl;
    cerr << "\t<Prompt> imdbtree [Datafile] [#actors] [command file]" << endl;
    return 1;
  }

  //DO NOT REMOVE THESE LINES!
  CTAGradeHook grader;
  grader.testTree();
  /************************/

  //    cout << "Test data file name:  ";
  string
    file = argv[3],
    ACTORSFILE = argv[1];
  
  int LIMIT = atoi(argv[2]);
    
  //    getline(cin, file);

  ifstream tstr(file.c_str());
  if(!tstr)
    {
      cout << "Unable to open data file:  " << file << endl;
      cin.get();
      return 1;
    }

  //
  // Load the database data
  //

  CActors     actors;
    
  if(!actors.TreeLoad(ACTORSFILE.c_str(), LIMIT))
    {
      cin.get();
      return 1;
    }

  //
  // Process commands in the input data file
  //

  cout << endl;
  cout << "Processing commands in " << file << endl;

  while(!tstr.eof())
    {
      string line;
      getline(tstr, line);
      if(line == "")
	continue;

      if(line == "height")
	actors.PrintHeight(cout);
      else if(line == "actor-movies")
        {
	  getline(tstr, line);
	  actors.PrintActorMovies(cout, line);
        }
      else if(line == "movie-actors")
        {
	  getline(tstr, line);
	  actors.PrintMovieActors(cout, line);
        }
      else if(line == "delete-actor")
        {
	  getline(tstr, line);
	  actors.DeleteActor(line);
          cout<<"Deletion process is done"<<endl;
        }
      else if(line == "delete-movie")
        {
          cout<<"We are about to delete a movie"<<endl;
	  getline(tstr, line);
	  actors.DeleteMovie(line);
          cout<<"Deletion process is done"<<endl;
        }
      else if(line == "quit")
        {
	  break;
        }

    }
    
        
 // cin.get();
  return EXIT_SUCCESS;
}


//
// Name :         CActors::PrintHeight()
// Description :  Print the height of the movie tree.  
//

void CActors::PrintHeight(std::ostream &str)
{
  str << "Movie Tree height = " << m_movies.Depth() << endl;
}


//
// Name :         CActors::PrintActorMovies()
// Description :  Print all actors for a given movie.
//

void CActors::PrintActorMovies(std::ostream &str, const std::string &actor)
{
  // Look up the actor
  str << "Movies for actor:  " << actor << endl;
  CTree<CActor>::Node *pActor = m_actors.Find(actor);

  // Deal with a not-found situation
  if(pActor == 0)
    {
      str << "*** Actor not found" << endl;
      return;
    }

  // Iterate over all of the movie pointers for an actor and output
  const std::list<CTree<CMovie>::Node *> &movies = pActor->Data().GetMovies();
  for(std::list<CTree<CMovie>::Node *>::const_iterator i=movies.begin();  i!=movies.end();  i++)
    {
      str << "  " << (*i)->Data().GetMovie() << endl;
    }
}

//
// Name :         CActors::DeleteActor()
// Description :  Delete an actor, deleting any movies that no longer have an actor associated...
//

void CActors::DeleteActor(const std::string &actor)
{
  // Look up the actor in the actors tree.
  CTree<CActor>::Node *pActor = m_actors.Find(actor);
  if(pActor == 0)
    {
      cout << "*** Actor not found" << endl;
      return;
    }

  // Iterate over the movies for this actor.

  const std::list<CTree<CMovie>::Node *> &movies = pActor->Data().GetMovies();
  for(std::list<CTree<CMovie>::Node *>::const_iterator i=movies.begin();  i!=movies.end();  i++)
    {
      // Delete actor from movie
      (*i)->Data().DeleteActor(pActor);

      // Delete the movie if actor no longer exists
      if((*i)->Data().IsNoActors())
        {
	  string movie = (*i)->Data().GetMovie();
	  m_movies.Delete(movie);
        }
    }

  // Finally, delete the actor from the actors tree.
  m_actors.Delete(actor);
}

//
// Name :         CActors::PrintMovieActors()
// Description :  Print all actors for a given movie.
//

void CActors::PrintMovieActors(std::ostream &str, const std::string &movie)
{
  // Look up the movie.
  str << "Actors for movie:  " << movie << endl;
  CTree<CMovie>::Node *pMovie = m_movies.Find(movie);

  if(pMovie == 0)
    {
      str << "*** Movie not found" << endl;
      return;
    }

  // Iterate over the movies, printing the actors...
  const std::list<CTree<CActor>::Node *> &actors = pMovie->Data().GetActors();
  for(std::list<CTree<CActor>::Node *>::const_iterator i=actors.begin();  i!=actors.end();  i++)
    {
      str << "  " << (*i)->Data().GetActor() << endl;
    }
}

//
// Name :         CActors::DeleteMovie()
// Description :  Delete a movie, deleting all actors that no longer have any movies associated with them.
//

void CActors::DeleteMovie(const std::string &movie)
{
  CTree<CMovie>::Node *pMovie = m_movies.Find(movie);
  if(pMovie == 0)
    {
      cout << "*** Movie not found" << endl;
      return;
    }

  const std::list<CTree<CActor>::Node *> &actors = pMovie->Data().GetActors();
  for(std::list<CTree<CActor>::Node *>::const_iterator i=actors.begin();  i!=actors.end();  i++)
    {
      // Delete movie from actor
      (*i)->Data().DeleteMovie(pMovie);

      // Delete the actor if movie no longer exists
      if((*i)->Data().IsNoMovies())
        {
	  string actor = (*i)->Data().GetActor();
	  m_actors.Delete(actor);
        }
    }

  m_movies.Delete(movie);
}



//
// Name :         CActors::TreeLoad()
// Description :  This is the main data loading function.
//

bool CActors::TreeLoad(const char *p_filename, int p_limit)
{
  //
  // Pass 1:  Load the actors and movies
  //

  m_pass = 1;
  if(!Load(p_filename, p_limit))
    return false;

  cout << "All actors and movies loaded" << endl;

  cout << "Actor Tree depth = " << m_actors.Depth() << endl;
  cout << "Movie Tree depth = " << m_movies.Depth() << endl;

  //
  // Pass 2:  Create all of the cross-references....
  //

  m_pass = 2;
  if(!Load(p_filename, p_limit))
    return false;

  return true;
}



//
// Name :         CActors::ActorMovie()
// Description :  During the load operation, ActorMovie is called once for each actor/movie combination.
//

void CActors::ActorMovie(std::string &p_actor, std::string &p_movie)
{
  //cout << p_actor << ":" << p_movie << endl;

  if(m_pass == 1)
    {
      //
      // Pass 1:  Loading the actors and movies into the trees.
      //

      CActor a(p_actor);
      m_actors.Insert(a);

      CMovie m(p_movie);
      m_movies.Insert(m);
    }
  else if(m_pass == 2)
    {
      // 
      // Pass 2:  Cross references
      //

      //
      // Find the movie and the actor in the tree
      //

      CTree<CActor>::Node *pActor = m_actors.Find(p_actor);
      CTree<CMovie>::Node *pMovie = m_movies.Find(p_movie);

      // Create the cross references...
      pActor->Data().AddMovie(pMovie);
      pMovie->Data().AddActor(pActor);
    }
}


