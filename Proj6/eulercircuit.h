/*********************************
 *  Brian Jurgess
 *  CSE 331 Section 1
 *  Project 06
 *  eulercircuit.h
 *********************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

class Graph
{
public:
  Graph()
  {
    vertices = new vector<Vertex>;
       
  }
  ~Graph()
  {
    delete vertices;
   }
  class Vertex
  {
  public:
    friend class Graph;
    
    Vertex(int arg)
    {
      value = arg;
      visited = false;
      degree = 0;
    }

    
    // bool &operator<( Vertex v1, Vertex v2 )
    // {
    //  return v1.value < v2.value;
    //}
    
  private:
    int value;
    bool visited;
    bool degree;
    vector<Vertex> adjacent;
  };  
  
  void addVertex( string & v)
  {
    int pos1 = 0;
    int pos2 = v.find(' ', pos1);
    if( pos2 == string::npos )
      {
	pos2 = v.size();
      }
    
    int value = atoi(v.substr(pos1,pos2-pos1).c_str());
    Vertex newVertex(value);
    vertices->push_back(newVertex);
    edges.push_back(v);
        
  }
  
  void addEdges( )
  {
    
    int pos1 = 0;
    int pos2;
    int value;
    int vertex;

    for( int i = 0; i < edges.size(); i++)
      {
	pos1 = 0;
	
	pos2 = edges[i].find( ' ', pos1 );
	if( pos2 == string::npos )
	  {
	    pos2 = edges[i].size();
	  }
	vertex = atoi(edges[i].substr(pos1,pos2-pos1).c_str());
		
	pos1 = pos2 + 1;
	pos2 = edges[i].find( ' ', pos1 );
	if( pos2 == string::npos)
	  {
	    pos2 = edges[i].size();
	  }
	
	while( pos1 < edges[i].size() )
	  {
	    value = atoi(edges[i].substr(pos1, pos2-pos1).c_str());

	    vertices->at(vertex-1).adjacent.push_back(vertices->at(value-1));
	    vertices->at(vertex-1).degree++;
	    pos1 = pos2 + 1;
	    pos2 = edges[i].find(' ', pos1 );
	    if( pos2 == string::npos )
	      {
		pos2 = edges[i].size();
	      }
	  }
      }
    
  }
  
    
  vector<Vertex> DFS( int entry )
  {
    int j;
    
    for(int i = 0; i < vertices->size();i++)
      {
	vertices->at(i).visited = false;
      }
    stack<Vertex> S;
    S.push(vertices->at(entry-1));
    vector<Vertex> D;
    while(S.empty() == false)
      {
	cout << boolalpha;
	cout << S.empty() << endl;
	
	Vertex v = S.top();
	S.pop();
	cout << "V: " << v.value << endl;
	cout << "V visited: " << v.visited << endl;
	
	/*if( v.visited == false )
	  {
	    cout << "In if: " << v.value << endl;
	    
	    D.push_back(v);
	    v.visited = true;
	    }*/
	for( j = 0; j < v.adjacent.size(); j++ )
	  {
	    cout << "In for: " << v.value << endl;
	    
	    if( v.adjacent[j].visited == false )
	      {
		cout << v.adjacent[j].value << ' ' << endl;
		cout << "in Loop: " << S.empty() << endl;
	    
		S.push(v.adjacent[j]);
		cout << "In loop: " << S.empty() << endl;
	      }
	    
	  }
	j = 0;
	
	if( v.visited == false )
	  {
	    cout << "In if: " << v.value << endl;
	    D.push_back(v);
	    v.visited = true;
	  }
	
	cout << S.empty() << endl;
	
      }
    for( int l = 0; l < D.size();l++)
      {
	cout << D[l].value << endl;
      }
    

    return D;
       

  }
  bool exists(Vertex * d,int value)
  {
    for( int i = 0; i < vertices->size(); i++ )
      {
	if(value == vertices->at(i).value)
	  {
	    d = &vertices->at(i);
	    return true;
	  }
      }
    return false;
  }
  
  bool isConnected();

private:
  vector<Vertex> *vertices;
  vector<string> edges;
  
};



#endif
