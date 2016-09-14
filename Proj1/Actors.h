
// Name :        Actors.h
// Description : Declarations for CActors, the class for storing 
//               actor data.
//

#ifndef ACTORS_H
#define ACTORS_H

#include <vector>
#include <string>

#include "moviepointer.h"

// class CActors
// Simple class that stores all of the actors and their movies.
class CActors {
public:
    bool Load(const char *p_filename, int p_limit = -1);
    
    int GetNumActors() const {return m_actors.size();}
    std::vector<CMoviePointer> *GetMovies();
private:
    void MovieCleanup(std::string &p_movie);
    
    // class CActor
    // Class to store an actor and his movies.
    class CActor {
    public:
        void SetActor(const std::string &p_actor) {m_actor = p_actor;}
        void AddMovie(const std::string &p_movie) {m_movies.push_back(p_movie);}
        
        const std::string &GetActor() const {return m_actor;}
        const std::vector<std::string> &GetMovies() const {return m_movies;}
		const std::string *GetMovie(const unsigned i) const {return &m_movies.at(i);}
        
    private:
        std::string               m_actor;
        std::vector<std::string> m_movies;        
    };
      
    // The list of all actors
    std::vector<CActor> m_actors;
};



#endif
