#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

#include <vector>
#include <iostream>

using namespace std;


template<class T>
class CQuickSort{
public:
  void Sort(std::vector<T> *p_vec){
    int start = 0;
    int end = (*p_vec).size() - 1;
    QuickSort(p_vec, start, end);
    
  }
  void QuickSort(std::vector<T> *p_vec, int start, int end);
 
  void swap( T& first, T& second);
  
  void median(std::vector<T> *p_vec, int start, int end);
  
};

template<class T>
void CQuickSort<T>::QuickSort(std::vector<T> *p_vec, int start, int end)
{

  if( start < end)
    {
      cout << "start: " << start << " end: " << end << endl;
      
  median(p_vec, start, end);
  
  T pivot = p_vec->at(end - 1);

  int x = start;
  int y = end-1;

  for(;;)
    {
      while(p_vec->at(++x) < pivot )
	{
	  std::cout << "x: " << x << " ";
	  
	}
      while(pivot < p_vec->at(--y))
	{
	  std::cout << "y: " << y << " ";
	  
	}


      cout << "I'm out!" << endl;
      cout << "Current x, y" << x << ' ' << y << endl;
      
      if(x <= y)
	{
	  cout << "i'm here!" << endl;
	  
	  swap(p_vec->at(x),p_vec->at(y));
	}
      else
	cout << "I'm in break!" << endl;
      
	break;
    }

  swap(p_vec->at(x),p_vec->at((end-1)));
  if(start<y)
    {
      
      QuickSort(p_vec,start, y-1);
    }
  if(end>x)
    {
      
      QuickSort(p_vec,x+1,end-1);
    }
  
    }
  
  
 
}

template<class T>
void CQuickSort<T>::swap( T& first, T& second )
{
  T temp = first;

  first = second;
  second = temp;
  
}

template<class T>
void CQuickSort<T>::median( vector<T> *p_vec, int start, int end)
{
  int center = (start + end ) / 2;

  if( p_vec->at(center) < p_vec->at(start) )
    {
      swap( p_vec->at(start), p_vec->at(center) );
    }
  if(p_vec->at(end) < p_vec->at(start) )
    {
      swap(p_vec->at(start),p_vec->at(end));
    }
  if(p_vec->at(end) < p_vec->at(center))
    {
      swap(p_vec->at(center),p_vec->at(end));
    }

  swap(p_vec->at(center),p_vec->at(end-1));
}

    

#endif
