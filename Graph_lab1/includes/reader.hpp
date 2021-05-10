/*
* Name: Mikael leuf
* Course: Datastrukturer och algoritmer, dt046g
* Date: 2021-05-06
* Lab: Grafer 1
*/

#ifndef READER_HPP
#define READER_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include "typedef.hpp"

class Reader
{
public:
	Reader() = default;
	~Reader() = default;

	/**
	* Opens a file and parses through it 
	*
	* @param filename
	*/
	void open(const std::string filename);

	cor::adjMatrix getMatrix() const;
	cor::vertices getVertices() const;
	cor::edges getEdges() const;

	/**
	* Creates a 2d vector
	* iterates through a edge list and places all edges in the 2dvector
	*
	*/
	void makeAdjMatrix();

	/**
	* iterates though matrix and prints out all the data 
	*/
	void printGraph() const;

	/**
	* opens a file and outputs the matrix to the file
	*
	* @param filename the outputfile to open
	* @param delim the delimiter to be between the cells of the matrix
	*/
	void exportGraph(const std::string filename, const std::string delim) const;

private:
	cor::TOKEN getType(std::ifstream &in) const;

	void readComment(std::ifstream &in) const;
	cor::Vertex readMeta(std::ifstream &in) const;
	cor::Edge readEdge(std::ifstream &in) const;

	cor::edges edgeList;
	cor::vertices vertexList;
	cor::adjMatrix adjMatrix;
	cor::adjList adjList;
};
#endif // !READER_HPP
