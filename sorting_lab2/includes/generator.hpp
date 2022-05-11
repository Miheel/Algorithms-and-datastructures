#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <random>
#include <limits>
#include "typedef.hpp"
class Random
{
public:
	Random(unsigned seed) 
		:gen(seed), dist(0, cor::INF::max())
	{}
	int operator()() {
		return dist(gen);
	}

private:
	std::mt19937 gen;
	std::uniform_int_distribution<int> dist;
};



class Growing
{
public:
	Growing(unsigned seed)
		:gen(seed), dist(0, 10), value(dist(gen))
	{}
	int operator()() {
		value = value + dist(gen);
		return value;
	}

private:
	std::mt19937 gen;
	std::uniform_int_distribution<int> dist;
	unsigned value;
};



class Falling
{
public:
	Falling(unsigned seed)
		:gen(seed), dist(0, 10), value(dist(gen))
	{}
	int operator()() {
		value = value - dist(gen);
		return value;
	}

private:
	std::mt19937 gen;
	std::uniform_int_distribution<int> dist;
	unsigned value;
};



class Constant
{
public:
	Constant(unsigned seed)
		:val(seed)
	{}
	int operator()() {
		return val;
	}

private:
	unsigned val;
};

#endif // !GENERATOR_HPP
