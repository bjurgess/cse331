#ifndef _MOVIEPOINTER_H_
#define _MOVIEPOINTER_H_

class CMoviePointer
{
public:
    CMoviePointer() {m_movie = NULL;}
    CMoviePointer(const std::string &p_movie) {m_movie = &p_movie;}

    bool operator<(const CMoviePointer &b) {return *m_movie < *(b.m_movie);}
    bool operator==(const CMoviePointer &b) {return *m_movie == *(b.m_movie);}

    const std::string &GetMovie() const {return *m_movie;}

private:
    const std::string *m_movie;
};

#endif