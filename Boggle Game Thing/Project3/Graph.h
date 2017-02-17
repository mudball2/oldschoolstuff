#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include "SLList.h"
#include "DynArray.h"

template<typename Type>
class Graph
{
public:
	struct Edge
	{
		unsigned int toVertex;
		//Vertex *dest;
		//double cost;
	};
	struct Vertex
	{
	
		Type element;
		SLList<Edge> edges;
/*
		Vertex *prev;*/
		//int scratch;
		//double dist;

		/////////////////////////////////////////////////////
		// Function : addEdge
		// Parameters : toVertex - the index of the vertex we
		//                         are adjacent to
		/////////////////////////////////////////////////////
		void addEdge(const unsigned int& toVertex)
		{
			Edge temp; 
			temp.toVertex = toVertex;
			edges.addHead(temp);
		}
	};
private:
	DynArray<Vertex> vertices;
public:
	/////////////////////////////////////////////////////
	// Function : constructor
	/////////////////////////////////////////////////////
	Graph();

	/////////////////////////////////////////////////////
	// Function : destructor
	/////////////////////////////////////////////////////
	~Graph();

	///////////////////////////////////////////////////////
	//// Function : assignment operator
	///////////////////////////////////////////////////////
	//Graph<Type>& operator=(const Graph<Type>& assign);

	///////////////////////////////////////////////////////
	//// Function : copy constructor
	///////////////////////////////////////////////////////
	//Graph(const Graph& copy);

	/////////////////////////////////////////////////////
	// Function : addVertex
	// Parameters : value - the data to store in this vertex
	// Return : unsigned int - the index this vertex was added
	//                         at
	/////////////////////////////////////////////////////
	unsigned int addVertex(const Type& value);

	/////////////////////////////////////////////////////
	// Function : operator[]
	// Parameters : index - the index in the graph to access
	// Return : Vertex& - the vertex stored at the specified
	//                    index
	/////////////////////////////////////////////////////
	Vertex& operator[](const unsigned int& index);

	/////////////////////////////////////////////////////
	// Function : size
	// Return : unsigned int - the number of vertices in the
	//                         graph
	/////////////////////////////////////////////////////
	unsigned int size() const;

	/////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the graph and readies it for re-use
	/////////////////////////////////////////////////////
	void clear();

	/////////////////////////////////////////////////////
	// Function : printBreadthFirst
	// Parameters : startVertex - the vertex to start the 
	//                            traversal at
	// Notes : prints contents of the graph in depth order
	//         (from closest to farthest)
	/////////////////////////////////////////////////////
	void printBreadthFirst(const unsigned int& startVertex);
};

/////////////////////////////////////////////////////
// Function : constructor
/////////////////////////////////////////////////////
template<typename Type>
Graph<Type>::Graph()
{

}

/////////////////////////////////////////////////////
// Function : destructor
/////////////////////////////////////////////////////
template<typename Type>
Graph<Type>::~Graph()
{
	clear();
}

///////////////////////////////////////////////////////
//// Function : assignment operator
///////////////////////////////////////////////////////
//template<typename Type>
//Graph<Type>& Graph<Type>::operator=(const Graph<Type>& assign)
//{
//	if(this != &assign)
//	{
//		this->clear();
//
//	}
//	return *this;
//}
//
///////////////////////////////////////////////////////
//// Function : copy constructor
///////////////////////////////////////////////////////
//template<typename Type>
//Graph<Type>::Graph(const Graph& copy)
//{
//	//Might need to set some nullptrs.
//
//	*this = copy;
//}

///////////////////////////////////////////////////////
//// Function : addEdge
//// Parameters : toVertex - the index of the vertex we
////                         are adjacent to
///////////////////////////////////////////////////////
//template<typename Type>
//void Graph<Type>::addEdge(const unsigned int& toVertex)
//{
//	Edge temp = toVertex;
//	edges.addHead(temp);
//}

/////////////////////////////////////////////////////
// Function : addVertex
// Parameters : value - the data to store in this vertex
// Return : unsigned int - the index this vertex was added
//                         at
/////////////////////////////////////////////////////
template<typename Type>
unsigned int Graph<Type>::addVertex(const Type& value)
{
	Vertex temp;
	temp.element = value;
	vertices.append(temp);

	return vertices.size() - 1;
}

/////////////////////////////////////////////////////
// Function : operator[]
// Parameters : index - the index in the graph to access
// Return : Vertex& - the vertex stored at the specified
//                    index
/////////////////////////////////////////////////////
template<typename Type>
typename Graph<Type>::Vertex& Graph<Type>::operator[](const unsigned int& index)
{
	return vertices[index];
}

/////////////////////////////////////////////////////
// Function : size
// Return : unsigned int - the number of vertices in the
//                         graph
/////////////////////////////////////////////////////
template<typename Type>
unsigned int Graph<Type>::size() const
{
	return vertices.size();
}

/////////////////////////////////////////////////////
// Function : clear
// Notes : clears the graph and readies it for re-use
/////////////////////////////////////////////////////
template<typename Type>
void Graph<Type>::clear()
{
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices.clear();
	}
}

/////////////////////////////////////////////////////
// Function : printBreadthFirst
// Parameters : startVertex - the vertex to start the 
//                            traversal at
// Notes : prints contents of the graph in depth order
//         (from closest to farthest)
/////////////////////////////////////////////////////
template<typename Type>
void Graph<Type>::printBreadthFirst(const unsigned int& startVertex)
{
	queue<unsigned int> q;
	q.push(startVertex);

	int *sizeOfGraph = new int [vertices.size()];
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		sizeOfGraph[i] = -1;
	}

	sizeOfGraph[startVertex] = 0;

	while(!q.empty())
	{

	//	Breadth-First (start)
	 //	{
	//    Enqueue (start)
	 //           So long as queue not empty do:
		//	Dequeue a node
		//	Enqueue all of its Edge Nodes that 	haven’t been visited yet
		//	Display node
	  //}
		unsigned int pIndex;
		pIndex = q.front();

		q.pop();

		SLLIter<Edge> iter(vertices[pIndex].edges);

		for(iter.begin(); !iter.end(); ++iter)
		{
			if(sizeOfGraph[iter.current().toVertex] == -1)
			{
				q.push(iter.current().toVertex);
				sizeOfGraph[iter.current().toVertex] = sizeOfGraph[pIndex] + 1;
			}
		}
		cout << vertices[pIndex].element << ' ' << sizeOfGraph[pIndex] << endl;
	
	}
	delete [] sizeOfGraph;
}



#endif