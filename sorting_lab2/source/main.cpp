#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <valarray>
#include <numeric>
#include <random>

#include "timer.hpp"
#include "sort.hpp"
#include "generator.hpp"
#include "typedef.hpp"

double standardDeviation(std::valarray<double> &measurements);

template <class Sort, class Data>
void bench(Sort sort, std::string funkName, size_t size, size_t iterations, Data data);

void logMeasurements(std::string file, std::vector<double> &data, size_t sampleSize);

using namespace cor;

int main()
{

	auto seed = std::random_device{}();
	size_t iterations = 10;
	size_t size = 20000;
	auto insertion = [](auto first, auto last)
	{ insertionSort(first, last); };
	auto selection = [](auto first, auto last)
	{ selectionSort(first, last); };
	auto quicksortl = [](auto first, auto last)
	{ quickSortLeft(first, last); };
	auto quicksortm = [](auto first, auto last)
	{ quickSortMedian(first, last); };
	auto sort = [](auto first, auto last)
	{ std::sort(first, last); };

	std::cout << "\nrandom" << std::endl;
	std::cout << "	insertion" << std::endl;
	bench(insertion, "insertion_random.cvs", size, iterations, Random(seed));
	std::cout << "\n	selection" << std::endl;
	bench(selection, "selection_random.cvs", size, iterations, Random(seed));
	std::cout << "\n	quicksortl" << std::endl;
	bench(quicksortl, "quicksortl_random.cvs", size, iterations, Random(seed));
	std::cout << "\n	quicksortm" << std::endl;
	bench(quicksortm, "quicksortm_random.cvs", size, iterations, Random(seed));
	std::cout << "\n	std::sort" << std::endl;
	bench(sort, "stdsort_random.cvs", size, iterations, Random(seed));

	std::cout << "\ngrowing" << std::endl;
	std::cout << "	insertion" << std::endl;
	bench(insertion, "insertion_growing.cvs", size, iterations, Growing(seed));
	std::cout << "\n	selection" << std::endl;
	bench(selection, "selection_growing.cvs", size, iterations, Growing(seed));
	std::cout << "\n	quicksortl" << std::endl;
	bench(quicksortl, "quicksortl_growing.cvs", size, iterations, Growing(seed));
	std::cout << "\n	quicksortm" << std::endl;
	bench(quicksortm, "quicksortm_growing.cvs", size, iterations, Growing(seed));
	std::cout << "\n	std::sort" << std::endl;
	bench(sort, "stdsort_growing.cvs", size, iterations, Growing(seed));

	std::cout << "\nfalling" << std::endl;
	std::cout << "	insertion" << std::endl;
	bench(insertion, "insertion_falling.cvs", size, iterations, Falling(seed));
	std::cout << "\n	selection" << std::endl;
	bench(selection, "selection_falling.cvs", size, iterations, Falling(seed));
	std::cout << "\n	quicksortl\n" << std::endl;
	bench(quicksortl, "quicksortl_falling.cvs", size, iterations, Falling(seed));
	std::cout << "\n	quicksortm" << std::endl;
	bench(quicksortm, "quicksortm_falling.cvs",  size, iterations, Falling(seed));
	std::cout << "\n	std::sort" << std::endl;
	bench(sort, "stdsort_falling.cvs", size, iterations, Falling(seed));

	std::cout << "\nconstant" << std::endl;
	std::cout << "	insertion" << std::endl;
	bench(insertion, "insertion_constant.cvs", size, iterations, Constant(seed));
	std::cout << "\n	selection" << std::endl;
	bench(selection, "selection_constant.cvs", size, iterations, Constant(seed));
	std::cout << "\n	quicksortl" << std::endl;
	bench(quicksortl, "quicksortl_constant.cvs", size, iterations, Constant(seed));
	std::cout << "\n	quicksortm" << std::endl;
	bench(quicksortm, "quicksortm_constant.cvs", size, iterations, Constant(seed));
	std::cout << "\n	std::sort" << std::endl;
	bench(sort, "stdsort_constant.cvs", size, iterations, Constant(seed));

	return 0;
}

template <class Sort, class Data>
void bench(Sort sort, std::string funkName, size_t size, size_t iterations, Data data)
{
	cor::time::Timer<cor::time::mili, cor::time::steadyClock> t;

	std::vector<double> measurements;

	for (size_t i = 1; i <= iterations; i++)
	{
		auto dataSize = size * i;
		std::vector<int> randvec(dataSize);
		std::generate(randvec.begin(), randvec.end(), data);
		
		size_t count = 10;
		std::vector<int> tempVec;

		for (size_t j = 0; j < count; j++)
		{
			tempVec = randvec;
			t.start();
			sort(tempVec.begin(), tempVec.end());
			t.stop();
			measurements.push_back(t.elapsedSec());
		}

		std::cout << "		elements: " << size * i << " " << count << " times. Time: " << t.elapsedSec() << "s\n";
		std::cout << "		Is sorted: " << std::boolalpha << std::is_sorted(tempVec.begin(), tempVec.end()) << std::endl;
		logMeasurements(funkName, measurements, dataSize);
		measurements.clear();
	}

}

void logMeasurements(std::string file, std::vector<double> &data, size_t sampleSize)
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
	auto sumOfMeasurements = measurements.sum(); // std::accumulate(std::begin(measurements), std::end(measurements), 0);
	auto sampleSize = measurements.size();
	auto avg = sumOfMeasurements / sampleSize;

	auto pow = std::pow(measurements - avg, double(2));
	auto sumOfSquares = pow.sum();
	return std::sqrt((1.0 / (sampleSize - 1)) * sumOfSquares);
}
