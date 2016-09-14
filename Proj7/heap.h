#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template <typename T >
class heap
{

public:
  bool isEmpty() const;
  const T& findMin() const;

  void insert( const T & x );
  void deleteMin();
  void makeEmpty();
  


private:
  int currentSize;
  vector<T> array;

  void buildHeap();
  void percolateDown( int hole );
  

};

#endif
