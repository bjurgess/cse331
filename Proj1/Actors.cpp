//
// Name :        Actors.cpp
// Description : Implementation for the CActors class.
// Author :      Charles B. Owen
//

#include <fstream>
#include <iostream>

#include "Actors.h"

using namespace std;

//
// Name :        Load()
// Description : Load the actors into the vector of actors data.
// Parameters :  p_filename - The file to read the actor data from.
//               p_limit - Optional limit on how much data to load.
//

bool CActors::Load(const char *p_filename, int p_limit)
{
    // Open the file as a stream...
    ifstream actors(p_filename);
    if(!actors)
    {
        cerr << "Unable to open " << p_filename << endl;
        return false;
    }

    // Now we need to skip until we see "THE ACTORS vector"
    // followed by a line that starts with a dash
    
    bool foundheader = false;       // Use to indicate first hit
    while(true)
    {
        string line;
        getline(actors, line);
        if(actors.eof())
        {
            cerr << "Premature end of file on actors data file" << endl;
            return false;
        }

        // This is the text header
        if(line == "THE ACTORS LIST")
        {  
            foundheader = true;
        }
        
        // This is right before the data
        if(foundheader && line[0] == '-')
            break;     
    }
   
    // Now we load the actor data one actor at a time.  Note that the
    // data is tab delimited.
    
    int cnt = 0;
    while(true)
    {
        // Get the actor delimited by tab
        string actor;
        getline(actors, actor, '\t');
        
        // This is our end of file indication
        if(actor[0] == '-')
            break;
        
        // Get the movies.  Each is delimited by a return.
        // The first must be there, any additional ones will
        // be on the next lines.  A blank line indicates we are done.
        string movie;
        getline(actors, movie);
        
        MovieCleanup(movie);
        
        CActor actorStruct;
        
        actorStruct.SetActor(actor);
        actorStruct.AddMovie(movie);
       
        cnt++;
        if(p_limit > 0 && cnt > p_limit)
            break;
                
        while(true)
        {
            getline(actors, movie);
            if(movie.empty())
                break;
               
            MovieCleanup(movie);
                 
            actorStruct.AddMovie(movie);
        }
        
        m_actors.push_back(actorStruct);
    }
   
    return true;
}

//
// Name :        MovieCleanup()
// Description : When we read the movie data, it may have optional junk on the end.
//               To save space we delete the junk.  Also delete any tab 
//               characters on the front of the title.
// Parameters :  p_movie - in/out movie title we'll clean up.
//

void CActors::MovieCleanup(string &p_movie)
{
    int len = p_movie.length();
    bool done = false;
    
    while(!done)
    {
        // Each time through this loop, len will be 
        // set to the new length of the string.
        // As an example, if we delete all trailing space,
        // len will be set to the first space character
        // after the last non-space character.

        switch(p_movie[len-1])
        {
            case ' ':
                // Find the trailing space starting point
                for(len -= 2;  len>=0;  len--)
                    if(p_movie[len] != ' ')
                        break;   
                len++; 
                break;
                
            case '>':
                // Find matching <
                for(len -= 2;  len>=0;  len--)
                    if(p_movie[len] == '<')
                        break;    
                 break;
                
            case ']':
                // Find matching [
                for(len -= 2;  len>=0;  len--)
                    if(p_movie[len] == '[')
                        break;    
                 break;
                
            case ')':
                // Find matching (
                for(len -= 2;  len>=0;  len--)
                    if(p_movie[len] == '(')
                        break;    
                 break;
                
            default:
                // Some other character ends this movie.  We are done.
                done = true;
                break;   
        }
        
    }
    
    // Delete the trailing junk...
    p_movie.erase(len);
    
    // Count the leading tabs
    int cnt;
    for(cnt = 0;  cnt < len;  cnt++)
        if(p_movie[cnt] != '\t')
            break;
    
    if(cnt > 0)
        p_movie.erase(0, cnt);
}


std::vector<CMoviePointer> *CActors::GetMovies()
{
	std::vector<CMoviePointer> *retVec = new std::vector<CMoviePointer>;
	std::vector<CActor>::iterator i = m_actors.begin();
	const std::vector<std::string>::iterator j;

	while(i != m_actors.end()){
		for(unsigned g = 0; g < i->GetMovies().size(); g++){
			CMoviePointer cmp((*i->GetMovie(g)));
			retVec->push_back(cmp);
		}
		i++;
	}

	return retVec;
}