/*
* Name: Mikael leuf
* Course: Datastrukturer och algoritmer, dt046g
* Date: 2021-05-06
* Lab: Grafer 1
*/

#include "reader.hpp"

void Reader::open(std::string filename)
{
	std::string line;
	std::ifstream in(filename);
	cor::TOKEN token;

	if (!in.is_open())
	{
		std::cout << "file not found";
	}
	else
	{
		while ((token = getType(in)) != cor::TOKEN::END_OF_FILE)
		{
			switch (token)
			{
			case cor::TOKEN::COMMENT:
				this->readComment(in);
				break;
			case cor::TOKEN::META:
				this->vertexList.push_back(this->readMeta(in));
				break;
			case cor::TOKEN::EDGE:
				this->edgeList.push_back(this->readEdge(in));
				break;
			case cor::TOKEN::END_OF_FILE:
				break;
			}
		}
	}
}

cor::adjMatrix Reader::getMatrix() const
{
	return this->adjMatrix;
}

cor::vertices Reader::getVertices() const
{
	return this->vertexList;
}

cor::edges Reader::getEdges() const
{
	return this->edgeList;
}

void Reader::makeAdjMatrix()
{
	this->adjMatrix.resize(this->vertexList.size(), cor::edges(this->vertexList.size()));
	for (auto &edge : this->edgeList)
	{
		this->adjMatrix[edge.from_id][edge.to_id] = edge;
	}
}

void Reader::printGraph() const
{
	for (size_t i = 0; i < this->adjMatrix.size(); i++)
	{
		for (size_t j = 0; j < this->adjMatrix.size(); j++)
		{
			std::cout << std::setw(5) << this->adjMatrix[i][j].weight << "\t";
		}
		std::cout << "\n";
	}
}

void Reader::exportGraph(const std::string filename, const std::string delim = " ") const
{
	std::ofstream out(filename, std::ios::out);

	for (size_t i = 0; i < this->adjMatrix.size(); i++)
	{
		for (size_t j = 0; j < this->adjMatrix.size(); j++)
		{
			out << this->adjMatrix[i][j].weight << delim;
		}
		out << "\n";
	}
}

cor::TOKEN Reader::getType(std::ifstream & in) const
{
	switch (in.peek())
	{
	case '#':
		return cor::TOKEN::COMMENT;
		break;
	case 'M':
		return cor::TOKEN::META;
		break;
	case std::istream::traits_type::eof():
		return cor::TOKEN::END_OF_FILE;
		break;
	default:
		return cor::TOKEN::EDGE;
		break;
	}
}

void Reader::readComment(std::ifstream & in) const
{
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

cor::Vertex Reader::readMeta(std::ifstream & in) const
{
	cor::Vertex tempVertex;
	char temp;
	in >> temp >> tempVertex.ID;
	std::getline(in, tempVertex.name);
	return tempVertex;
}

cor::Edge Reader::readEdge(std::ifstream & in) const
{
	cor::Edge tempedge;
	in >> tempedge.from_id >> tempedge.to_id >> tempedge.weight;
	std::getline(in, tempedge.description);
	return tempedge;
}
