#ifndef _DUPLICATESREMOVE_H_
#define _DUPLICATESREMOVE_H_

#include <vector>

template<class T>
class CDuplicatesRemove{
public:
  void DuplicatesRemove(std::vector<T> *p_vec){

    int count = 0;
    
    int j = 1;

    for(int i =0; i < p_vec->size(); i++)
      {
	if(p_vec->at(i) == p_vec->at(j))
	  {
	    count++;
	  }
	else if(count > 0)
	  {
	    p_vec->at(j-count) = p_vec->at(j);
	  }
	j++;
	
      }

    if( j == p_vec->size() && count > 0 && count < j )
      {
	p_vec->erase(p_vec->end()-count,p_vec->end());
      }
    
	
  }  
};

#endif
