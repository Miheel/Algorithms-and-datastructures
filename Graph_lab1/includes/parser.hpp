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

class Parser
{
public:
	Parser(const std::string& filename);
	Parser() = default;
	~Parser() = default;

	/**
	* Opens a file and parses through it 
	*
	* @param filename
	*/
	void open(const std::string& filename);
	void parse();

	cor::graph::adjMatrix getMatrix() const;
	cor::graph::vertices getVertices() const;
	cor::graph::edges getEdges() const;

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
	std::ifstream in;

	cor::TOKEN getType(std::ifstream &in) const;

	void readComment(std::ifstream &in) const;
	cor::graph::Vertex readMeta(std::ifstream &in) const;
	cor::graph::Edge readEdge(std::ifstream &in) const;
	
	cor::graph::edges edgeList;
	cor::graph::vertices vertexList;
	cor::graph::adjMatrix adjMatrix;
};

#endif // !READER_HPP
