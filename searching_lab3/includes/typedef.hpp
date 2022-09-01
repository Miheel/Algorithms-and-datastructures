/*
* Name: Mikael leuf
* Course: Datastrukturer och algoritmer, dt046g
* Date: 2021-05-06
* Lab: Grafer 1
*/

#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

#include <chrono>
#include <vector>
#include <map>
#include <String>
#include <limits>

namespace cor {

	namespace time {

		typedef std::chrono::nanoseconds nano;
		typedef std::chrono::microseconds micro;
		typedef std::chrono::milliseconds mili;
		typedef std::chrono::seconds sec;
		typedef std::chrono::steady_clock steadyClock;
		typedef std::chrono::system_clock systemClock;

		template<typename clock_t>
		using timePoint = std::chrono::time_point<clock_t>;
	}

	namespace graph {

		typedef std::numeric_limits<double> NOT_CONNECTED;
		typedef std::numeric_limits<double> DISTANCE;
		typedef double weight_t;
		typedef double distance_t;
		typedef int node_id;

		struct Edge
		{
			node_id from_id;
			node_id to_id;
			weight_t weight = NOT_CONNECTED::infinity();
			std::string description;

			operator bool()
			{
				return weight != NOT_CONNECTED::infinity();
			}
		};

		struct Vertex
		{
			int ID;
			std::string name;

			bool visited = false;

			distance_t distance = DISTANCE::infinity();

			bool operator < (const Vertex & comp) const {
				return this->ID < comp.ID;
			}
		};

		typedef std::vector<Vertex> vertices;
		typedef std::vector<Edge> edges;
		typedef std::vector<edges> adjMatrix;
		typedef std::map <Vertex, edges> adjList;
	}

	enum TOKEN {
		COMMENT,
		META,
		EDGE,
		END_OF_FILE
	};

	typedef std::numeric_limits<int> INF;
}

#endif // !TYPEDEF_HPP
