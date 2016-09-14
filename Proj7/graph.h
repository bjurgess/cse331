/*************************************
   Brian Jurgess
   CSE 331
   Project 7
*************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;


class Graph
{
public:
  Graph() 
  {
    
  }
  ~Graph()
  {

  }

  //
  // class Vertex
  // Used to create the vertices of the graph
  //
  class Edge;
  
class Vertex
  {
  public:
    friend class Graph;
    friend class Edge;
    Vertex() {};
    ~Vertex() {}
    Vertex(unsigned ID, string name, string type)
    {
      id = ID;
      Name = name;
      Type = type;
    }
    Vertex& operator=( const Vertex& RHS )
    {
	  id = RHS.id;
	  Name = RHS.Name;
	  Type = RHS.Type;
      
      return *this;
    }
    void addAdjacent( Graph::Edge & edge )
    {
      adjacent.push_back(edge);
    }
    
    bool operator==( const Vertex& One )
    {
      return (One.id == id && One.Name == Name && One.Type == Type );
    }
    bool operator!=( const Vertex& One )
    {
      return (One.id != id || One.Name != Name || One.Type != Type);
    }
    
    unsigned getID()
    {
      return id;
    }
    string getName()
    {
      return Name;
    }
    string getType()
    {
      return Type;
    }
    friend ostream& operator<< (ostream& out, Vertex &vertex )
    {
      out << vertex.Name;
      return out;
    }
    
    
  private:
    // Elements go here
    unsigned id;
    string Name;
    string Type;
    vector<Graph::Edge> adjacent;
  };

  //
  // class Edge
  // Used to create the edges of the graph
  //

  class Edge
  {
  public:
    friend class Graph;
    Edge() 
    {
      
    }
    ~Edge() 
    {
    }
    
    Edge( unsigned ID, Vertex * Start, Vertex * End, string name, double Distance, double Speed )
    {
      id = ID;
      start = Start;
      end = End;
      Name = name;
      distance = Distance;
      speed_limit = Speed;
    }
    friend ostream& operator<<( ostream& out, Edge &edge )
    {
      out << "Take " << edge.Name << " from " << *edge.start << " to " << *edge.end;
      
      return out;
    }
    double getDistance()
    {
      return distance;
    }

    double getSpeedlimit()
    {
      return speed_limit;
    }
    
    
    
  private:
    // Elements go here
    unsigned id;
    Vertex * start;
    Vertex * end;
    string Name;
    double distance;
    double speed_limit;
  };

  //
  //  Add Vertice to the Graph
  //
  void addVertex( string & vertex )
  {
    unsigned id;
    string Name;
    string Type;
    Vertex * a;
    unsigned pos = 0;
    unsigned pos2 = vertex.find(' ', pos);

    id = atoi( vertex.substr(pos,pos2-pos).c_str() );
        
    pos = pos2 + 1;
    pos2 = vertex.find('"', pos + 1);

    Name = vertex.substr( pos+1,(pos2)-pos-1 );
    
    pos = pos2 + 2;

    Type = vertex.substr( pos, vertex.size() - pos );
    
    a = new Vertex(id, Name, Type);

    vertices.push_back(*a);
    
    
  }

  //
  //  Add an edge to the graph
  //
  
  void addEdge( string & edge )
  {
    double id;
    Vertex * start;
    Vertex * end;
    string name;
    double distance;
    double speed;

    unsigned pos = 0;
    unsigned pos2 = edge.find(' ',pos);

    id = atoi( edge.substr(pos, pos2-pos).c_str() );

    pos = pos2 + 1;
    pos2 = edge.find(' ',pos);
    // Find the vertice in the list
    for( unsigned i = 0; i < vertices.size(); i++ )
      {
	if(vertices[i].id == atoi( edge.substr(pos,pos2-pos).c_str() ) )
	  {
	    start = &vertices[i];
	  }
      }
    
    pos = pos2 + 1;
    pos2 = edge.find(' ',pos);
    for( unsigned i = 0; i < vertices.size(); i++ )
      {
	if(vertices[i].id == atoi( edge.substr(pos,pos2-pos).c_str() ) )
	  {
	    end = &vertices[i];
	  }
      }
    
    pos = pos2 + 2;
        
    pos2 = edge.find('"',pos);

    name = edge.substr(pos, pos2-pos);
        
    pos = pos2 + 2;
        
    pos2 = edge.find( ' ', pos );

    distance = atof( edge.substr(pos, pos2-pos).c_str() );

    pos = pos2 + 1;

    speed = atof( edge.substr(pos, edge.size()-pos).c_str() );

    Edge *  a = new Edge( id, start, end, name, distance, speed );

    edges.push_back(*a);
    start->addAdjacent(*a);
    

  }

  //
  // Find the quickest path
  //
  
  vector<Edge>  quickest_path( string first, string second )
  {
    unsigned start, end;
    // Get the starting/ending id
    for( int i = 0; i < vertices.size(); i++ )
      {
	if( vertices[i].Name == first )
	  {
	    start = vertices[i].id;
	  }
	if( vertices[i].Name == second )
	  {
	    end = vertices[i].id;
	  }
      }

    
    Heap shortestHeap;
    vector<dij> shortestList;
    dij dijkstra;
    
    Vertex * v;
    vector<Edge> shorterShortestList;
    
    // Create each dijkstra struct and insert them into the heap
    for(unsigned i = 0; i < vertices.size(); i++ )
      {
	dij dijk;
		
	dijk.vertexID = vertices[i].id;
	dijk.distance = numeric_limits<double>::max();

	dijk.known = false;
	dijk.p = NULL;
	
	shortestHeap.insert(dijk);
      }

    // Decrease the starting point to distance 0
    
    shortestHeap.decreaseKey( start, 0.0 );
    // Begin dijkstra algorithm
    for( ;; )
      {

	shortestHeap.deleteMin( dijkstra );
	shortestList.push_back(dijkstra); // Add the dijkstra to a list
	
	// Iff the dijkstra is equal to the end point or max
	if( dijkstra.vertexID == end || dijkstra.vertexID == numeric_limits<int>::max())
	  break;

	// Find the vertice corresponding to the dijkstra struct
	for( unsigned j = 0; j < vertices.size(); j++ )
	  {
	    if( vertices[j].id == dijkstra.vertexID )
	      {				
		v = &vertices[j];
		break;
	      }
	  }

	// Begin checking edges
	for ( unsigned k = 0; k < v->adjacent.size(); k++ )
	  {

	    // Loop through shortestHeap array
	    for( unsigned l = 1; l < shortestHeap.array.size(); l++ )
	      {
		// If end id of vertice is equivalent to id of a dijk struct in array
		if( v->adjacent[k].end->id == shortestHeap.array[l].vertexID )
		  {
		    // If the distances added together is less than the dijk struct in array
		    if( ((dijkstra.distance + v->adjacent[k].distance)/v->adjacent[k].speed_limit < shortestHeap.array[l].distance) && !shortestHeap.array[l].known)
		      {
			// Add the edge to the dijk stuct
			shortestHeap.array[l].next = &v->adjacent[k];
			// Add the dijkstra to the dijk struct
			shortestHeap.array[l].p = dijkstra.vertexID;
			// Decrease the distance
			shortestHeap.decreaseKey( shortestHeap.array[l], (dijkstra.distance + v->adjacent[k].distance)/v->adjacent[k].speed_limit );
		 
		       			
		      }
		    break;
		    
		  }
	      }
	  }
	
      }


    // Begin to find the shortest path
    dij newDijkstra;
    
    newDijkstra = shortestList.back();
    if( newDijkstra.vertexID != numeric_limits<int>::max() )
      {
	while( newDijkstra.vertexID != start )
	  {
	    shorterShortestList.push_back(*newDijkstra.next );

	    for( int i = 0; i < shortestList.size(); i++ )
	      {
		if( shortestList[i].vertexID == newDijkstra.p )
		  {
		    newDijkstra = shortestList[i];
		    break;	
		  }
	      }	
	  }
      }
    

    return shorterShortestList;  

  }  

  //
  // Shortest path :: exactly like quickest path
  // Except using distance instead of time
  //
  vector<Edge>  shortest_path( string first, string second )
  {
    unsigned start, end;
    
    for( int i = 0; i < vertices.size(); i++ )
      {
	if( vertices[i].Name == first )
	  {
	    start = vertices[i].id;
	  }
	if( vertices[i].Name == second )
	  {
	    end = vertices[i].id;
	  }
      }
    
    Heap shortestHeap;
    vector<dij> shortestList;
    dij dijkstra;
    
    Vertex * v;
    vector<Edge> shorterShortestList;
    
    
    for(unsigned i = 0; i < vertices.size(); i++ )
      {
	dij dijk;
		
	dijk.vertexID = vertices[i].id;
	dijk.distance = numeric_limits<double>::max();

	dijk.known = false;
	dijk.p = NULL;
	
	shortestHeap.insert(dijk);
      }

    shortestHeap.decreaseKey( start, 0.0 );
    for( ;; )
      {

	shortestHeap.deleteMin( dijkstra );
	
	shortestList.push_back(dijkstra);
	
	
	if( dijkstra.vertexID == end || dijkstra.vertexID == numeric_limits<int>::max())
	  break;

	for( unsigned j = 0; j < vertices.size(); j++ )
	  {
	    if( vertices[j].id == dijkstra.vertexID )
	      {				
		v = &vertices[j];
		break;
	      }
	  }
	
	for ( unsigned k = 0; k < v->adjacent.size(); k++ )
	  {
	    	    
	    for( unsigned l = 1; l < shortestHeap.array.size(); l++ )
	      {
		
		if( v->adjacent[k].end->id == shortestHeap.array[l].vertexID )
		  {
		    
		    if( ((dijkstra.distance + v->adjacent[k].distance) < shortestHeap.array[l].distance) && !shortestHeap.array[l].known)
		      {
			shortestHeap.array[l].next = &v->adjacent[k];
			shortestHeap.array[l].p = dijkstra.vertexID;
			
			shortestHeap.decreaseKey( shortestHeap.array[l], dijkstra.distance + v->adjacent[k].distance );
		 
		       			
		      }
		    break;
		    
		  }
	      }
	  }
	
      }
        
    dij newDijkstra;
    
    newDijkstra = shortestList.back();
    if( newDijkstra.vertexID != numeric_limits<int>::max() )
      {
	while( newDijkstra.vertexID != start )
	  {
	    shorterShortestList.push_back(*newDijkstra.next );

	    for( int i = 0; i < shortestList.size(); i++ )
	      {
		if( shortestList[i].vertexID == newDijkstra.p )
		  {
		    newDijkstra = shortestList[i];
		    break;
		
		  }
	      }
	
	  }
      }
    

    return shorterShortestList;  

  }  


  
private:
  // the dijkstra struct
  struct dij
  {
    unsigned vertexID;
    double distance;
    Edge * next;
    bool known;
    unsigned p;
    
  };

  vector<Vertex> vertices;
  vector<Edge> edges;


  //
  // Class: Heap/Priority Queue
  //
  
  class Heap
  {
  public:
    friend class Graph;
    
    Heap()
    {
      array.resize(10);
      currentSize = 0;
    }
    
    Heap( const vector<dij> & items )
    {
      array.resize(items.size() + 10 );
      currentSize = items.size();

      for( unsigned i = 0; i < items.size(); i++ )
	{
	  array[i+1] = items[i];
	}
      buildHeap();

    }
    
    bool isEmpty() const
    {
      return currentSize == 0;
    }
    
    // Insert in the heap
    void insert( const dij & x )
    {
           
      if( currentSize == array.size() - 1 )
	{
	  array.resize( array.size() * 2 );
	}
      unsigned hole = ++currentSize;
      for( ; hole > 1 && x.distance < array[ hole / 2].distance; hole /= 2 )
	{
	  array[hole] = array[hole / 2 ];
	}
      array[hole] = x;
    }
    // Delete Minimum of heap & return the minimum
    void deleteMin( dij & minItem)
    {
      if( !isEmpty() )
	{
	  minItem = array[ 1 ];
	  	  
	  array[ 1 ] = array[currentSize];
	  currentSize -= 1;
	  
	  percolateDown( 1 );
	  
	  
	}
      else
	{
	  minItem.vertexID = numeric_limits<int>::max();
	}
      
      
    }
    
    void makeEmtpy()
    {
      currentSize = 0;
    }

    // Decrease the key of an ID in the heap
    void decreaseKey( unsigned id, double distance )
    {
      int hole;      
      for ( unsigned i = 1; i < array.size(); i++ )
	{	  
	  
	  if( array[i].vertexID == id )
	    {
	      
	      if( distance < array[i].distance )
		{
		  array[i].distance = distance;
		}
	      
	      hole = i;
	     	      
	      break;
	      
	    }
	}

      for( ; hole > 1 && array[hole].distance < array[ hole / 2].distance; hole /= 2 )
	{
	  dij tmp = array[hole];
	  
	  array[hole] = array[hole/2];
	  array[hole / 2] = tmp;
	  
	}
      
    }
    // Same thing, but receving a dij stuct instead of unsigned int
    void decreaseKey( dij & dijkstra, double distance)
    {
      unsigned hole;
      for( unsigned i = 1; i < array.size(); i++ )
	{
	  if( dijkstra.vertexID == array[i].vertexID ){
	    array[i].distance = distance;
	    hole = i;
	    break;
	  }
	}
      for( ; hole > 1 && array[hole].distance < array[ hole / 2].distance; hole /= 2 )
	{
	  dij tmp = array[hole];
	  
	  array[hole] = array[hole / 2];
	  array[hole /2 ] = tmp;
	  
	}
    }
    
  private:
    
    unsigned currentSize;
    vector<dij> array;  // Priority queue
    // Build the heap from scratch
    void buildHeap() {
      for( unsigned i = currentSize / 2; i > 0; i-- )
	{
	  cout << i << endl;
	  
	  percolateDown(i);
	}
    }

    // Used when deleting the min
    void percolateDown(unsigned hole )
    {
      unsigned child;

      dij Temp = array[ hole ];
      for( ; hole*2 <= currentSize; hole = child )
	{
	  child = hole * 2;
	  if( child != currentSize && array[ child + 1 ].distance < array[ child ].distance )
	    {
	      child++;
	    }
	  if( array[ child ].distance < Temp.distance )
	    {
	      array[ hole ] = array[child];
	    }
	  else
	    break;

	}
      array[ hole ] = Temp;
      
    }
    
  };
  
    
};

#endif
  
