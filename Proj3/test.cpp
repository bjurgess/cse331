/*************************************
testing RevList.h
*************************************/

#include <iostream>
#include <iomanip>
#include "RevList.h"

using namespace std;


int main()
{
  CRevList<unsigned> A;



  for(unsigned i=0; i<10; i++)
    {
      A.PushBack(i);
    }

  CRevList<unsigned>::Node * curr = A.Begin();

  while(curr != A.End())
    {
      cout << curr->Data() << endl;
      curr = A.Next(curr);
    }

  A.Reverse();
  
  curr = A.Begin();
  CRevList<unsigned>::Node * old = NULL;

  cout << " Reversed: " << endl;

  cout << "Begin: " << curr->Data() << endl;
  

  while (curr != A.End())
    {
      cout << "In reverse loop: " << endl;
      
      cout << curr->Data() << endl;
      curr = A.Next(curr);
    }

  curr = A.Begin();
  
  while(!A.IsEmpty())
    {
      old = curr;
      
      curr = A.Next(curr);


      A.Delete(old);

    }

  curr = A.Begin();

  cout << "We are here" << endl;
  
  while(curr != A.End())
    {
      cout << "in here" << endl;
      
      cout << curr->Data() << endl;
    }

  
  
  
  


}
