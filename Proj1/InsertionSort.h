#ifndef _INSERTIONSORT_H_
#define _INSERTIONSORT_H_

#include <vector>

template<class T>
class CInsertionSort{
public:
  void Sort(std::vector<T> *p_vec){

    unsigned k;
    
    //Start your insertion sort code here
    for( unsigned i = 1; i < p_vec->size(); i++)
      {
	T tmp = p_vec->at(i);

	for( k = i; k > 0 && tmp < p_vec->at(k-1); k--)
	  {
	    (*p_vec)[k] = (*p_vec)[k-1];
	  }
	(*p_vec)[k] = tmp;
      }
    
  }
};

#endif
