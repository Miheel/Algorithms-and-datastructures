/*
* Name: Mikael leuf
* Course: Datastrukturer och algoritmer, dt046g
* Date: 2021-05-06
* Lab: Grafer 1
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>


template<class Matrix, class Vertices, class Node>
class Graph
{
public:
	Graph(Matrix &matrix, Vertices &vertices);
	~Graph() = default;

	/**
	* finds the shortest path between two nodes
	*
	* @param startNode
	* @param endNode
	*/
	void dijkstra(Node startNode, Node endNode);

	/**
	* Finds the vertex in the vertices set with the minimum distace that hasn't been visited alredy
	*
	* @return the verttex with the minimum distance
	*/
	Node minDist();

	/**
	* look through a adjacencymatrix from a sourcenode to every other node
	* if all the nodes can be reached
	*
	* @param srcNode to begin the search
	* @return if the all the nodes can be reached
	*/
	bool depthFirst(Node srcNode);

	/**
	* look through a adjacencymatrix from a sourcenode to every other node
	* if all the nodes can be reached 
	*
	* @param srcNode to begin the search
	* @return if the all the nodes can be reached 
	*/
	bool breadthFirst(Node srcNode);

	/**
	* repares a adjacency matrix by filling in missing conections and making the matrix symetrix
	* @param srcNode
	*/
	void makeSymetric();

private:

	/**
	* Prints the shortest path and distance gained from dijkstras 
	* between a source node and a target node
	*
	* @param spt to get the shortest path from
	* @param src sourecenode the start of the path
	* @param target endnode the end of the path
	*/
	void printPath(Vertices spt, Node src, Node target);

	/**
	* Resets all the vertices in a graph
	* distance is set to INF and visited gets set to false
	*
	*/
	void reset();

	Matrix &matrix;
	Vertices &vertices;
};

#endif // !GRAPH_HPP

template<class Matrix, class Vertices, class Node>
inline Graph<Matrix, Vertices, Node>::Graph(Matrix &matrix, Vertices &vertices)
	:matrix(matrix), vertices(vertices)
{
}

template<class Matrix, class Vertices, class Node>
void Graph<Matrix, Vertices, Node>::dijkstra(Node startNode, Node endNode)
{
	this->reset();

	//spt to store the shortest path
	Vertices shortestPath(vertices.size());

	//set distance to startnode to 0
	this->vertices.at(startNode.ID).distance = 0;

	for (auto &elem : vertices)
	{
		//find the node with the minimum distance
		Node minVertex = this->minDist();

		//mark the min node as visited
		this->vertices.at(minVertex.ID).visited = true;

		//if the min node is equal to the end node
		//print out the shortest path 
		//break out of the loop
		if (minVertex.ID == endNode.ID)
		{
			this->printPath(shortestPath, this->vertices.at(startNode.ID), this->vertices.at(endNode.ID));
			break;
		}

		//iterate through all the conected neighbors of the min node
		for (size_t i = 0; i < this->matrix[minVertex.ID].size(); i++)
		{

			Node node = this->vertices[i];
			double minDist = minVertex.distance + this->matrix[minVertex.ID][i].weight;
			//update the min distance of the neighbors only if
			//
			//if the node hasn't been visited
			//there is a conection between the neighbor and min node
			//the neighboring nodes distance is bigger than the min node distance plus the weight between the min node and the neighboring node
			//
			//insert the neighbor in to the spt
			if (!node.visited && this->matrix[minVertex.ID][i].weight && node.distance > minDist)
			{
				this->vertices.at(i).distance = minDist;
				shortestPath[i] = minVertex;
			}
		}
	}
}

template<class Matrix, class Vertices, class Node>
Node Graph<Matrix, Vertices, Node>::minDist()
{
	Node tempMin;
	auto min = cor::DISTANCE::infinity();

	//Loop through all the vertices that hasnt been already visited and has a min distance
	//compare the min distance of all the vertices to find minimum distance vertex
	for (auto &elem : this->vertices)
	{
		if (elem.visited == false && elem.distance <= min)
		{
			min = elem.distance;
			tempMin = elem;
		}
	}
	return tempMin;
}

template<class Matrix, class Vertices, class Node>
bool Graph<Matrix, Vertices, Node>::depthFirst(Node srcNode)
{
	this->reset();

	std::stack<Node> stack;

	//push the sourcenode in to the stack and set it as visited
	stack.push(srcNode);
	this->vertices.at(srcNode.ID).visited = true;

	//as long as the queue has nodes in it loop through them
	while (!stack.empty())
	{
		//store the top of the queue and pop the value 
		Node node = stack.top();
		stack.pop();

		//loop through all the conected neighbors of the stored node
		for (size_t i = 0; i < this->matrix[node.ID].size(); i++)
		{
			bool visited = this->vertices.at(i).visited;
			auto weight = this->matrix[node.ID][i].weight;

			//if a neighboring node hans't been marked as visited and has a weight 
			//push the node in to the stack and mark it as visited
			if (!visited && weight != cor::NOT_CONNECTED::infinity())
			{
				stack.push(this->vertices.at(i));
				this->vertices.at(i).visited = true;
			}
		}

	}

	//check if all the vertices has been marked as visited 
	//if not return false 
	for (auto &elem : this->vertices)
	{
		if (elem.visited == false)
		{
			return false;
		}
	}
	return true;
}

template<class Matrix, class Vertices, class Node>
bool Graph<Matrix, Vertices, Node>::breadthFirst(Node srcNode)
{
	this->reset();

	std::queue<Node> queue;

	// push the sourcenode in to the queue and set it as visited
	queue.push(srcNode);
	this->vertices.at(srcNode.ID).visited = true;

	//as long as the queue has nodes in it loop through them
	while (!queue.empty())
	{
		//store the front of the queue and pop the value 
		Node node = queue.front();
		queue.pop();

		//loop through all the conected neighbors of the stored node
		for (size_t i = 0; i < this->matrix[node.ID].size(); i++)
		{

			bool visited = this->vertices.at(i).visited;
			auto weight = this->matrix[node.ID][i].weight;

			//if a neighboring node hans't been marked as visited and has a weight 
			//push the node in to the queue and mark it as visited
			if (!visited && weight != cor::NOT_CONNECTED::infinity())
			{
				queue.push(this->vertices.at(i));
				this->vertices.at(i).visited = true;
			}
		}
	}

	//check if all the vertices has been marked as visited 
	//if not return false 
	for (auto &elem : this->vertices) 
	{
		if (elem.visited == false)
		{
			return false;
		}
	}
	return true;
}

template<class Matrix, class Vertices, class Node>
void Graph<Matrix, Vertices, Node>::makeSymetric()
{
	for (auto &elem : vertices)
	{
		if (elem.visited == false)
		{
			for (size_t i = 0; i < matrix[elem.ID].size(); i++)
			{
				//Get the edges opposite eatch other in the matrix
				auto edgeA = matrix[elem.ID][i];
				auto edgeB = matrix[i][elem.ID];

				//if the edges are different 
				//set the undefined edge to the real edge
				//
				//if edgeB is not defined assigns A to B
				//swap the the connection IDs
				//place edgeB at the correct spot in the matrix
				if (edgeA && !edgeB)
				{
					edgeB = edgeA;
					std::swap(edgeB.from_id, edgeB.to_id);
					matrix[i][elem.ID] = edgeB;
				}

				//if edgeA is not defined assigns B to A
				//swap the the connection IDs
				//place edgeA at the correct spot in the matrix
				if (edgeB && !edgeA)
				{
					edgeA = edgeB;
					std::swap(edgeA.from_id, edgeA.to_id);
					matrix[elem.ID][i] = edgeA;
				}
			}
		}
	}
}

template<class Matrix, class Vertices, class Node>
inline void Graph<Matrix, Vertices, Node>::printPath(Vertices spt, Node src, Node target)
{
	Node tempTarget = target;
	if (spt.at(tempTarget.ID).distance != cor::DISTANCE::infinity() || tempTarget.ID == src.ID)
	{
		std::cout << "\nEnd ";
		//while the target node has a minimum distance 
		//print out the node ID 
		//set new target to node in spt at target ID
		while (tempTarget.distance != cor::DISTANCE::infinity())
		{
			std::cout << tempTarget.ID << " <- ";
			tempTarget = spt.at(tempTarget.ID);
		}
		std::cout << "Start" << "\n";
		std::cout << "Distance from " << src.ID << " -> " << target.ID << " is: " << target.distance << "\n";
	}
}

template<class Matrix, class Vertices, class Node>
void Graph<Matrix, Vertices, Node>::reset()
{
	for (auto &elem : vertices)
	{
		elem.visited = false;
		elem.distance = cor::DISTANCE::infinity();
	}
}
