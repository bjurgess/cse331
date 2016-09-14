
// Name :        Actors.h
// Description : Declarations for CActors, the class for storing 
//               actor data.
//

#ifndef ACTORS_H
#define ACTORS_H

#include <vector>
#include <string>
#include <iostream>

#include "Tree.h"
#include "Movie.h"

// class CActors
// Simple class that stores all of the actors and their movies.
class CActors {
public:
    bool TreeLoad(const char *p_filename, int p_limit = -1);
    bool Load(const char *p_filename, int p_limit = -1);
    
    void ActorMovie(std::string &p_actor, std::string &p_movie);

    void Preorder(std::ostream &str) {m_movies.Preorder(str);}

    void PrintHeight(std::ostream &str);
    void PrintActorMovies(std::ostream &str, const std::string &actor);
    void PrintMovieActors(std::ostream &str, const std::string &actor);
    void DeleteActor(const std::string &actor);
    void DeleteMovie(const std::string &movie);

private:
    int                 m_pass;

    void MovieCleanup(std::string &p_movie);

    CTree<CMovie>       m_movies;
    CTree<CActor>       m_actors;
};



#endif
