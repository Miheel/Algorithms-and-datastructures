#include <valarray>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
//#include <sstream>
//#include <numeric>


#include "timer.hpp"
#include "search.hpp"

template<class Search, class Data>
void benchSearch(std::string outFile, Search& search, size_t iterations, size_t size, Data data);

double standardDeviation(std::valarray<double> &measurements);

void sieve(size_t N);

std::vector<size_t> readPrimes(size_t N);

void log(std::string file, std::vector<double> &data, size_t sampleSize);

using namespace cor;

int main() {

	for (size_t i = 0, size_t j = 0; i < j; i++, j++)
	{
		std::cout << "huh ";
	}


	////{

	//std::cout << "Generating primes\n";
	////sieve(cor::INF::max());//10000000


	//int base = 1000000;
	//size_t iterations = 50;
	//std::vector<size_t> prime = readPrimes(base * iterations);
	////std::vector<int> prime = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	//using iter = decltype(prime.begin());
	///*
	//										41
	//						/								\
	//					  17								  67
	//				/			  \						/			 \
	//			  7				   29				 53				   79
	//		   /	\			/	   \	       /    \		    /	   \
	//		 3		 13	       23	    37	     47	     61		   73	    89
	//		/ \     /  \	  /  \	   / \		/  \     / \	  / \	   /
	//	   2   5  11    nl  19   nl  31   nl  43   nl  59   nl  71   nl  83
	//*/

	//size_t benchIterations = 0;
	//size_t sampleSize;
	////std::string series;

	//std::cout << "linear search\n";

	//for (size_t i = 1; i <= iterations; i++)
	//{
	//	sampleSize = base * i;
	//	std::cout << "		" << sampleSize << " elements\n";
	//	LinearSearch<iter> LS(prime.begin(), prime.begin() + sampleSize);
	//	benchIterations = 50;
	//	benchSearch("Lineas_search.cvs", LS, benchIterations, sampleSize, prime);

	//	std::cout << "\n\n";
	//}


	//std::cout << "Binary search\n";

	//for (size_t i = 1; i <= iterations; i++)
	//{
	//	sampleSize = base * i;
	//	std::cout << "		" << sampleSize << " elements\n";
	//	BinarySearch<iter> BS(prime.begin(), prime.begin() + sampleSize);
	//	benchIterations = 50;
	//	benchSearch("binary_search.cvs", BS, benchIterations, sampleSize, prime);

	//	std::cout << "\n\n";
	//}


	//std::cout << "Binary search tree\n";

	//for (size_t i = 1; i <= iterations; i++)
	//{
	//	sampleSize = base * i;
	//	std::cout << "		" << sampleSize << " elements\n";
	//	BTS<int> bst(prime.begin(), prime.begin() + sampleSize);
	//	benchIterations = 50;
	//	benchSearch("bst_search.cvs", bst, benchIterations, sampleSize, prime);

	//	std::cout << "\n\n";
	//}


	//std::cout << "Hashtabel\n";

	//for (size_t i = 1; i <= iterations; i++)
	//{
	//	sampleSize = base * i;
	//	std::cout << "		" << sampleSize << " elements\n";
	//	Hashtabel HashT(prime.begin(), prime.begin() + sampleSize, prime.size());
	//	benchIterations = 50;
	//	benchSearch("hashtable_search.cvs", HashT, benchIterations, sampleSize, prime);

	//	std::cout << "\n\n";
	//}

	return 0;
}

template<class Search, class Data>
void benchSearch(std::string outFile, Search& search, size_t iterations, size_t size, Data data)
{
	cor::time::Timer<cor::time::micro, cor::time::steadyClock> t, tSum;

	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<size_t> dist(0, data.at(data.size() - 1));


	std::vector<double> mearsurments;

	tSum.start();
	for (size_t i = 0; i < iterations; i++)
	{
		auto searchFor = dist(gen);

		t.start();
		auto it = search.search(searchFor);
		t.stop();
		mearsurments.push_back(t.elapsedTime());


		//std::cout << "Looking for " << data[index] << " Found ";
		//if (it)
		//{
		//std::cout << *it << "\n";
		//}
		//else
		//{
		//	std::cout << "not found\n";
		//}
	}
	tSum.stop();

	std::cout << "		" << iterations << " iterations on " << size << " elements took " << tSum.elapsedTime() << "ms each took " << tSum.elapsedTime() / iterations << "ms\n";
	//return std::to_string(size) + "," + std::to_string(tSum.elapsedTime()) + "," + std::to_string(tSum.elapsedTime() / iterations) + "," + std::to_string(iterations);

	log(outFile, mearsurments, size);
}

void log(std::string file, std::vector<double>& data, size_t sampleSize)
{
	std::valarray<double> measurements(data.data(), data.size());
	auto deviation = standardDeviation(measurements);
	auto avg = measurements.sum() / measurements.size();
	auto logStr = std::to_string(sampleSize) + "," + std::to_string(avg) + "," + std::to_string(deviation) + "," + std::to_string(measurements.size());

	std::ofstream out(file, std::ios::app);

	out << logStr << "\n";

	out.close();
}

double standardDeviation(std::valarray<double> &measurements)
{
	auto sumOfMeasurements = measurements.sum();//std::accumulate(std::begin(measurements), std::end(measurements), 0);
	auto sampleSize = measurements.size();
	auto avg = sumOfMeasurements / sampleSize;

	auto pow = std::pow(measurements - avg, double(2));
	auto sumOfSquares = pow.sum();
	return std::sqrt((1.0 / (sampleSize - 1)) * sumOfSquares);
}

void sieve(size_t N)
{
	std::vector<bool> boolvec(N, true);
	std::string primes;
	int index = 2;
	boolvec[0] = false, boolvec[1] = false;

	for (size_t i = 2; i < std::sqrt(N); i++)
	{
		if (boolvec[i] == true)
		{
			for (size_t j = i * i; j < N; j += i)
			{
				boolvec[j] = false;
			}
		}
	}

	std::cout << "Done\n";
	std::cout << "Write to file\n";
	std::ofstream out("primes");


	std::for_each(boolvec.begin() + 2, boolvec.end(), [&](const bool &b) {
		if (b)
		{
			out << std::to_string(index) + "\n";
		}
		index++;
	});
	std::cout << "Done\n";
}

std::vector<size_t> readPrimes(size_t N)
{
	std::ifstream in("primes.txt");
	std::vector<size_t> temp;
	int value;

	while (in >> value && temp.size() < N)
	{
		temp.push_back(value);
	}

	return temp;
}
