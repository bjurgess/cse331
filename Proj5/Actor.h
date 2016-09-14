#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <string>
#include <list>

#include "Tree.h"

class CMovie;

class CActor
{
public:
    CActor() {}
    CActor(const std::string &m) {m_actor = m;}
    CActor(const CActor &m) {m_actor = m.m_actor;}

    bool operator<(const CActor &a) const {return m_actor < a.m_actor;}
    bool operator>(const CActor &a) const {return m_actor > a.m_actor;}
    void operator=(const CActor &a) {m_actor = a.m_actor;}

    const std::string &GetActor() const {return m_actor;}

    void AddMovie(CTree<CMovie>::Node *n) {m_movies.push_back(n);}
    const std::list<CTree<CMovie>::Node *> &GetMovies() const {return m_movies;}

    void DeleteMovie(CTree<CMovie>::Node *a);
    bool IsNoMovies();

private:
    std::string      m_actor;
    std::list<CTree<CMovie>::Node *> m_movies;
};

inline std::ostream &operator<<(std::ostream &str, const CActor &m)
{
    str << m.GetActor();
    return str;
}

#endif
