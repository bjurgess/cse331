#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
#include <list>

#include "Tree.h"

class CActor;

class CMovie
{
public:
    CMovie() {}
    CMovie(const std::string &m) {m_movie = m;}
    CMovie(const CMovie &m) {m_movie = m.m_movie;}

    bool operator<(const CMovie &a) const {return m_movie < a.m_movie;}
    bool operator>(const CMovie &a) const {return m_movie > a.m_movie;}
    void operator=(const CMovie &a) {m_movie = a.m_movie;}

    const std::string &GetMovie() const {return m_movie;}

    void AddActor(CTree<CActor>::Node *n) {m_actors.push_back(n);}
    const std::list<CTree<CActor>::Node *> &GetActors() const {return m_actors;}

    void DeleteActor(CTree<CActor>::Node *a);
    bool IsNoActors();

private:
    std::string      m_movie;
    std::list<CTree<CActor>::Node *> m_actors;
};

inline std::ostream &operator<<(std::ostream &str, const CMovie &m)
{
    str << m.GetMovie();
    return str;
}

#endif
