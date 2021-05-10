/*
* Name: Mikael leuf
* Course: Datastrukturer och algoritmer, dt046g
* Date: 2021-05-06
* Lab: Grafer 1
*/

#include <iostream>
#include <sstream>
#include <fstream>

#include "reader.hpp"
#include "graph.hpp"

int main() {
	Reader reader;

	reader.open("export.txt");
	reader.makeAdjMatrix();

	auto matrix = reader.getMatrix();
	auto Vertices = reader.getVertices();

	Graph<cor::adjMatrix, cor::vertices, cor::Vertex> graph(matrix, Vertices);

	if ((graph.breadthFirst(Vertices[0]) && graph.depthFirst(Vertices[0])) == false)
	{
		graph.makeSymetric();
	}

	std::cout << std::boolalpha << graph.breadthFirst(Vertices[0]) << graph.depthFirst(Vertices[0]);


	cor::Vertex *src = &Vertices[24], *target = &Vertices[37];
	graph.dijkstra(*src, *target);

	src = &Vertices[46], target = &Vertices[47];
	graph.dijkstra(*src, *target);

	src = &Vertices[20], target = &Vertices[19];
	graph.dijkstra(*src, *target);


	reader.exportGraph("export.cvs", ",");

	return 0;
}