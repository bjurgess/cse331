
#ifndef CTREE_H
#define CTREE_H

#include <iostream>
using namespace std;

template<class T> class CTree
{
public:
    CTree() {m_root = 0;}
    ~CTree() {delete m_root;}

    //
    // class Node
    // The nested node class for objects in our tree.
    //

    class Node 
    {
    public:
        friend class CTree;

        Node() {m_ll = 0;  m_rl = 0;m_active = true;}
        Node(const T &t) {m_payload = t;  m_ll = 0;  m_rl = 0;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_payload;}
        const T &Data() const {return m_payload;}

    private:
        Node    *m_ll;
        Node    *m_rl;
        T       m_payload;

	bool m_active;
    };

    void Insert(const T &t) {

      if(m_root == 0)
	{
	  m_root = new Node(t);
	}
      else
	{
	  rinsert(t, m_root);
	}
      

    }
    void Preorder(std::ostream &p_str) {
      Node * curr = m_root;
      
      rpreorder(p_str, curr);
      
    }
    int Depth() {
      Node * curr = m_root;
      
      int x = rdepth(curr);
      return x;
      
    }

    const Node *Find(const T &t) const {
      Node * curr = m_root;
      
      Node *temp = rfind(t, curr);
      
      return temp;}
    Node *Find(const T &t) {
    
      Node * curr = m_root;
      
      Node *temp = rfind(t, curr);
    
      
      return temp;
      
    }

  
    void Delete(const T &t)
    {
           
      rdelete(t, m_root);
      
    }

private:
    Node *m_root;
  void rinsert( const T &t, Node *curr)
  {
        
    if( t < curr->m_payload)
      {
	if(curr->m_ll == 0) curr->m_ll = new Node(t);
	else rinsert(t,curr->m_ll);
      }
    else if( t > curr->m_payload)
      {
	if(curr->m_rl == 0) curr->m_rl = new Node(t);
	else rinsert(t, curr->m_rl);
      }
    
  }
  Node *rfind( const T &t, Node *curr)
  {
        
    if(curr == 0 ) return 0;
    else if( t < curr->m_payload ) rfind(t, curr->m_ll);
    else if( t > curr->m_payload) rfind(t, curr->m_rl);
    else return curr;
    
  }

  int rdepth( Node *curr)
  {
    if(curr == 0) return 0;
    int lheight = rdepth(curr->m_ll);
    int rheight = rdepth(curr->m_rl);
    if(lheight > rheight) return lheight + 1;
    else return rheight + 1;
  }
  
  void rpreorder( std::ostream &p_str, Node *curr)
  {
    if(curr != 0)
      {
	p_str << curr->m_payload << " ";
	rpreorder(p_str, curr->m_ll);
	rpreorder(p_str, curr->m_rl);
      }
    

  }
  
  
  void rdelete( const T &t, Node *curr)
  {
        
    if(curr != 0)
      {
	if( t < curr->m_payload){

	  
	  rdelete(t,curr->m_ll);
	}
	
	else if( t > curr->m_payload){

	  
	  rdelete(t, curr->m_rl);
	}
	
	else
	  {
	    Node * temp;
	    
	    if(curr->m_ll == 0)
	      {
		curr = curr->m_rl;
		//delete temp;
		
	      }
	    else if(curr->m_rl == 0)
	      {
		//temp = curr->m_ll;
		
		curr = curr->m_ll;
		//delete temp;
		
	      }
	    else
	      {
		T x = deletemin(curr);
		curr->m_payload = x;
		
	      }
	  }
      }
  }

  T deletemin(Node *curr)
  {
    T x;
    
    if(curr != 0)
      {
	if(curr->m_ll == 0)
	  {
	   
	    x = curr->m_payload;
	   
	    curr = curr->m_rl;
	    
	  }
	else x = deletemin(curr->m_ll);
      }
    return x;
  }
  
  
    
};


#endif
