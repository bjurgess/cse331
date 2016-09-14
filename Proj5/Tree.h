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

        Node() {m_ll = 0;  m_rl = 0;  m_height=0;  m_deleted=false;}
        Node(const T &t) {m_payload = t;  m_ll = 0;  m_rl = 0;  m_height=0;  m_deleted=false;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_payload;}
        const T &Data() const {return m_payload;}

    private:
        Node    *m_ll;
        Node    *m_rl;
        int     m_height;
        bool    m_deleted;
        T       m_payload;
    };

    void Insert(const T &t) {
      Node **curr = &m_root;
      if( (*curr) == 0 ) *curr = new Node(t);
      else rInsert( curr, t );
      
    }
    void Preorder(std::ostream &p_str) {
      Node **curr = &m_root;
      rPreorder(p_str,curr);
    }
    int Depth() {
      Node ** curr = &m_root;
      return rDepth(curr);
      
    }
  const Node *Find(const T &t) const { Find(t);}
    Node *Find(const T &t) {
      Node **curr = &m_root;
      return rFind(t, curr);
      
    }

    void Delete(const T &t)
    {
      Node ** curr = &m_root;
      rDelete(t, curr);
      
    }


private:
    Node *m_root;
  // Check Balance condition of the code
  // Return type bool
  void rInsert( Node **curr, const T &t )
  {
    if(*curr == 0)
      {
	*curr = new Node(t);
      }
    else if( t < (*curr)->m_payload )
      {
	rInsert( &(*curr)->m_ll, t );
	if( Height(&((*curr)->m_ll)) - Height(&((*curr)->m_rl)) == 2 )
	  {
	    if( t < (*curr)->m_ll->m_payload ) rotateLeftOnce( curr );
	    else rotateLeftTwice( curr );
	  }
      }
    else if( t > (*curr)->m_payload )
      {
	rInsert(&(*curr)->m_rl, t);
	if( Height(&(*curr)->m_rl) - Height(&((*curr)->m_ll)) == 2 )
	  {
	    if( (*curr)->m_rl->m_payload < t ) rotateRightOnce( curr );
	    else rotateRightTwice( curr );
	  }
      }
    
    (*curr)->m_height = max( Height(&((*curr)->m_ll)), Height(&((*curr)->m_rl))) + 1;
  }
  void rDelete(const T &t, Node **curr)
  {
    if(*curr == 0)
      return;
    else if (t<(*curr)->m_payload) rDelete(t,&(*curr)->m_ll);
    else if (t>(*curr)->m_payload) rDelete(t,&(*curr)->m_rl);
    else (*curr)->m_deleted = true;
  }
  Node * rFind(const T &t, Node **curr)
  {
    if(*curr==0) return 0;
    else if(t<(*curr)->m_payload) rFind(t, &(*curr)->m_ll);
    else if(t>(*curr)->m_payload) rFind(t, &(*curr)->m_rl);
    else if((*curr)->m_deleted) return 0;
    else return *curr;
  }
  void rPreorder( std::ostream &p_str, Node **curr)
  {
    if(&curr != 0)
      {
	if( (*curr)->m_deleted == false )
	  {
	    p_str << (*curr)->m_payload << " ";
	  }
	
	rPreorder(p_str, &(*curr)->m_ll);
	rPreorder(p_str, &(*curr)->m_rl);
      }
    
  }
  
  int rDepth( Node ** curr)
  {
    int leftd, rightd;
    
    if( *curr == 0 ) return 0;
   
    leftd = rDepth(&((*curr)->m_ll));
    rightd = rDepth(&((*curr)->m_rl));
       
    return max(leftd,rightd)+1;
    
  }
  
  
  
    
  void rotateLeftOnce( Node **curr )
  {
    Node *left = (*curr)->m_ll;
    (*curr)->m_ll = left->m_rl;
    left->m_rl = *curr;
    (*curr)->m_height = max( Height(&((*curr)->m_ll)), Height(&((*curr)->m_rl))) + 1;
    left->m_height = max( Height(&left->m_ll), (*curr)->m_height ) + 1;
    *curr = left;
  }

  void rotateRightOnce( Node **curr )
  {
    Node *right = (*curr)->m_rl;
   
    
    (*curr)->m_rl = right->m_ll;
    
       
    right->m_ll = *curr;
   
    
    (*curr)->m_height = max( Height(&((*curr)->m_rl)), Height(&((*curr)->m_ll))) + 1;
    right->m_height = max( Height(&right->m_rl), (*curr)->m_height ) + 1;
    *curr = right;
  }

  void rotateRightTwice( Node **curr )
  {
    rotateLeftOnce(&(*curr)->m_rl);
    rotateRightOnce(curr);
  }

  void rotateLeftTwice( Node **curr )
  {
    
    rotateRightOnce(&(*curr)->m_ll);
    rotateLeftOnce(curr);
  }

  // Update the height of the nodes
  int Height( Node **curr)
  {
    if(*curr == 0) return -1;
    else return (*curr)->m_height;
    
    
  }

  int max( int one, int two )
  {
    if(one < two) return two;
    else return one;
  }
  
};


#endif
