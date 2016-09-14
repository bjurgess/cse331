#include "Movie.h"
#include "Actor.h"

void CMovie::DeleteActor(CTree<CActor>::Node *a) 
{
    m_actors.remove(a);
}


bool CMovie::IsNoActors() 
{
    return m_actors.empty();
}
