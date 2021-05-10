/*
* Name: Mikael leuf
* Course: Datastrukturer och algoritmer, dt046g
* Date: 2021-05-06
* Lab: Grafer 1
*/

#include <iostream>
#include <sstream>
#include <fstream>

#include "parser.hpp"
#include "u_graph.hpp"

using namespace cor;

int main() {
	Parser parser("export.txt");

	parser.parse();
	parser.makeAdjMatrix();

	auto matrix = parser.getMatrix();
	auto Vertices = parser.getVertices();

	graph::U_Graph<graph::adjMatrix, graph::vertices, graph::Vertex> graph(matrix, Vertices);

	if ((graph.breadthFirst(Vertices[0]) && graph.depthFirst(Vertices[0])) == false)
	{
		graph.makeSymetric();
	}

	std::cout << std::boolalpha << graph.breadthFirst(Vertices[0]) << graph.depthFirst(Vertices[0]);


	graph::Vertex *src = &Vertices[24], *target = &Vertices[37];
	graph.dijkstra(*src, *target);

	src = &Vertices[46], target = &Vertices[47];
	graph.dijkstra(*src, *target);

	src = &Vertices[20], target = &Vertices[19];
	graph.dijkstra(*src, *target);


	parser.exportGraph("export.cvs", ",");

	return 0;
}