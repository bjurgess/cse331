//
// Name :         RevList.h
// Description :  Simple doubly linked list with reversing feature.
//

#ifndef REVLIST_H
#define REVLIST_H

#include <iostream>

using namespace std;


template<class T> class CRevList
{

public:
  // Constructor.  Sets to an empty list.
  CRevList() 
  {
    Num = 0;
    reverse_flag = false;
    m_head = new Node;
    
    m_head->m_next = NULL;
    m_head->m_prev = NULL;
    
    
  }

  // Destructor.  Deletes everything in the list.
  ~CRevList()
  {
    Clear();
    
  }

  // Copy constructor.  Copies another list.
  CRevList(const CRevList &b)
  {
    Node * curr;

    reverse_flag = false;
    Num=0;
    m_head = new Node;
    

    curr = b.m_head->m_next;

    for(unsigned i = 0; i< Num; i++)
      {
	PushBack(curr->m_payload);
	curr = curr->m_next;
      }
    

    
  }

  // Assignment operator.  Copies another list.
  void operator=(const CRevList &b);

  // Clear the list.
  void Clear()
  {
    if(m_head->m_next != NULL)
      {
	Node * prev;
	Node * curr = m_head->m_next;

	while(curr != NULL)
	  {
	    prev = curr;
	    curr = curr->m_next;
	    delete prev;
	  }
	Num = 0;
	m_head->m_next = NULL;
	m_head->m_prev = NULL;
	
      }
    
  }


  //
  // class Node
  // The nested node class for objects in our linked list.
  //
  // YOU MAY NOT MODIFY THIS CLASS!
  class Node 
  {
  public:
    friend class CRevList;
  
    Node() {m_next = 0;  m_prev = 0;}
    Node(const T &t) {m_payload = t;  m_next = 0;  m_prev = 0;}
  
    T Data() {return m_payload;}
    const T Data() const {return m_payload;}
  
  private:
    Node    *m_next;
    Node    *m_prev;
    T       m_payload;
  };
  
  // Determines if the list is empty
  bool IsEmpty() const { return (Num==0); }

  //methods to add data to the front or the back of the list
  void PushFront(const T &t) {
    Node * Temp = new  Node;  // Create new node with pointer Temp

    Temp->m_payload = t;   // Place t into node

    switch(reverse_flag)    // Handle reverse condition
      {
      case 0:
	Temp->m_next = m_head->m_next;
	
	if(m_head->m_next != NULL)
	  {
	    m_head->m_next->m_prev = Temp;
	  }
	else
	  m_head->m_prev = Temp;

	m_head->m_prev->m_next = Temp;
	Temp->m_prev = m_head->m_prev;
	m_head->m_next = Temp;
	Num++;
	
	break;

      case 1:
	Temp->m_prev = m_head->m_prev;

	if(m_head->m_prev != NULL)
	  {
	    m_head->m_prev->m_next = Temp;
	  }
	else
	  m_head->m_next = Temp;

	Temp->m_next = m_head->m_next;
	m_head->m_prev = Temp;
	m_head->m_next->m_prev = Temp;
	Num++;
	
	break;
	

      }
    
    
  }
  void PushBack(const T &t) {
    Node * Temp = new Node; // Create new node

    Temp->m_payload = t; // Place t into node payload

    switch(reverse_flag) // Handle reverse condition
      {
      case 0:
	Temp->m_prev = m_head->m_prev;

	if(m_head->m_prev != NULL)
	  {
	    m_head->m_prev->m_next = Temp;
	  }
	else
	  {
	    m_head->m_next = Temp;
	    Temp->m_prev = Temp;
	    
	  }
	

	Temp->m_next = m_head->m_next;
	m_head->m_next->m_prev = Temp;
	m_head->m_prev = Temp;
	Num++;
	
	break;

      case 1:
	
	if(m_head->m_next != NULL)
	  {
	    Temp->m_next = m_head->m_next;
	    
	    m_head->m_next->m_prev = Temp;
	  }
	else
	  m_head->m_prev = Temp;

	m_head->m_prev->m_next = Temp;

	Temp->m_prev = m_head->m_prev;;

	m_head->m_next = Temp;
	Num++;
	
	break;
	
      }
    
	
    
  }
  void PopFront() {
    Node * curr;  // Pointer to the current node

    switch(reverse_flag) // Handle reverse condition
      {
      case 0:
	curr = m_head->m_next;
	if(curr != NULL)
	  {
	    if(curr->m_next != curr)
	      {
		curr->m_next->m_prev = curr->m_prev;
		m_head->m_next = curr->m_next;
		
	      }

	    else
	      {
		m_head->m_next = NULL;
		m_head->m_prev = NULL;
	      }
	    Num--;
	    
	  }
	break;

      case 1:
	curr = m_head->m_prev;

	if(curr != NULL)
	  {
	    if(curr->m_prev != curr)
	      {
		curr->m_prev->m_next = curr->m_next;
		m_head->m_prev = curr->m_prev;
	      }
	    else
	      {
		m_head->m_next = NULL;
		m_head->m_prev = NULL;
	      }
	    Num--;
	    
	  }
	break;

      }
    
	    
	    
  }
  void PopBack() {
    Node * curr;

    switch(reverse_flag) // Handle reverse condition
      {
      case 0:
	curr = m_head->m_prev;

	if(curr != NULL)
	  {
	    if(curr->m_prev != curr)
	      {
		curr->m_prev->m_next = curr->m_next;
		m_head->m_prev = curr->m_prev;
	      }
	    else
	      {
		m_head->m_next = NULL;

		m_head->m_prev = NULL;
	      }
	    Num--;
	    
	  }
	break;

      case 1:
	curr = m_head->m_next;
	if(curr != NULL)
	  {
	    if(curr->m_next != curr)
	      {
		curr->m_next->m_prev = curr->m_prev;
		m_head->m_next = curr->m_next;
		
	      }

	    else
	      {
		m_head->m_next = NULL;
		m_head->m_prev = NULL;
	      }
	    Num--;
	    
	  }
	break;

      }
    
    	
  }

  //Get a pointer to the first node in the list
  const Node *Begin() const { Begin(); }
  Node *Begin() {
    if(reverse_flag == false)
      {
	return m_head->m_next;
      }
    else
      return m_head->m_prev;
    

  }

  //get a pointer to the last node in the list
  const Node *End() const { End(); }
  Node *End() {
    if(reverse_flag == false)
      {
	return m_head->m_prev;
      }
    else
      return m_head->m_next;
    

  }

  //get a pointer to node next in the list
  const Node *Next(const Node *n) const {
    if(reverse_flag == false)
      {
	return n->m_next;
      }
    else
      return n->m_prev;
    

  }
  Node *Next(const Node *n) {
    if(reverse_flag == false)
      return n->m_next;
    else
      return n->m_prev;
    

  }

  //Find a node with the specified key
  const Node *Find(const T &t) const {
    Node * curr = m_head->m_next;

    while( (curr != NULL) && (curr->m_payload) != t )
      {
	curr = curr->m_next;
      }

    return curr;
    
  }
  Node *Find(const T &t) {
    Node * curr = m_head->m_next;

    while( (curr != NULL) && (curr->m_payload) != t )
      {
	curr = curr->m_next;
      }

    return curr;
    
  }

  //Delete the given node
  void Delete(Node *n){
    if(n != NULL)
      {
	
	if( (n->m_next) == n)
	  {

	    
	    m_head->m_next = NULL;
	    m_head->m_prev = NULL;
	  }
	else
	  {
	    n->m_prev->m_next = n->m_next;
	    n->m_next->m_prev = n->m_prev;
	    if( m_head->m_next == n )
	      {
		m_head->m_next = n->m_next;
	      }
	    if( m_head->m_prev == n )
	      {
		m_head->m_prev = n->m_prev;
	      }
	    
	  }
	delete n;
	Num--;
	
      }
    

  }

  //Reverse the list in O(1) time
  void Reverse() {
    if(reverse_flag == false)
      {
	reverse_flag = true;
      }
    else
      {
	reverse_flag = false;
      }
    

  }

  

private:

  //NOTE: you may add any private member variables or 
  //      methods you need to complete the implementation

  Node  *  m_head;             // Head node
  unsigned Num;
  bool reverse_flag; // Number of items in list
 
  
  
};

// Assignment operator.  Copies another list.
template<class T> void CRevList<T>::operator=(const CRevList<T> &b)
{
  Clear();

  Node * curr = b.m_head->m_next;

  for(unsigned i = 0; i<Num;i++)
    {
      PushBack(curr->m_payload);
      curr = curr->m_next;
    }
  
  
}

//template<class T> (CRevList<T>::Node *) CRevList<T>::Begin1() {return m_reverse ? m_head.m_prev : m_head.m_next;}


#endif
