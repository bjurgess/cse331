#include "Actor.h"
#include "Movie.h"


void CActor::DeleteMovie(CTree<CMovie>::Node *a) 
{
    m_movies.remove(a);
}


bool CActor::IsNoMovies() 
{
    return m_movies.empty();
}
