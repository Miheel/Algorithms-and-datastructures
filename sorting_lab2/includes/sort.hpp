#ifndef SORT_HPP
#define SORT_HPP

#include <iostream>
#include <vector>
#include <iterator>
#include <cstddef>

template<class T>
void swapItem(T &a, T &b)
{
	auto temp = a;
	a = b;
	b = temp;
}

template<typename ForwIt>
ForwIt minElement(ForwIt first, ForwIt last)
{
	if (first == last)
		return last;

	auto minElem = first;
	for (auto j = first + 1; j != last; j++)
	{
		if (*j < *minElem)
		{
			minElem = j;
		}
	}
	return minElem;
}

template<typename ForwIt>
void insertionSort(ForwIt first, ForwIt last)
{
	//for (auto next = first + 1; next != last; next++)
	//{
	//	for (auto curr = next; curr != first; curr--)
	//	{
	//		if (*(curr-1) > *curr) {
	//			std::iter_swap(curr, (curr - 1));
	//		}
	//	}
	//	for (auto IT = first; IT != last; IT++)
	//	{
	//		std::cout << *IT << ", ";
	//	}
	//	std::cout << "\n";
	//}

	for (auto it = first; it != last; it++) {
		auto insertion = std::upper_bound(first, it, *it);
		std::rotate(insertion, it, std::next(it));
	}


}

template<typename RandomIt>
void selectionSort(RandomIt first, RandomIt last)
{
	for (auto current = first; current != last; current++)
	{
		//find the smallest value in the arr
		auto const min = std::min_element(current, last);
		//auto const min = minElement(current, last);

		//swap the found min value with the current IT pos
		std::iter_swap(current, min);
		//swapItem(*current, *min);
	}
}

template<typename RandomIt>
RandomIt medianOfThree(RandomIt first, RandomIt last)
{
	auto mid = first + (std::distance(first, last) / 2);

	if (*first > *last) std::iter_swap(first, last);

	if (*first > *mid) std::iter_swap(first, mid);

	if (*mid > *last) std::iter_swap(mid, last);

	std::iter_swap(mid, last);
	return last;
}

template<typename ForwIt, typename Comp>
ForwIt lomutoPartition(ForwIt first, ForwIt last, Comp comp)
{
	if (first == last) return first;

	auto pivot = std::prev(last);
	auto low = first;
	for (auto next = first; next <= pivot; next++)
	{
		if (comp(*next))
		{
			std::iter_swap(low, next);
			++low;
		}
	}
	std::iter_swap(low, pivot);
	return low;
}

template<typename RandIt>
void quickSortLeft(RandIt first, RandIt last)
{
	auto low = first;
	auto high = last;
	while (low < high)
	{
		auto pivot = *std::prev(high);
		auto middle = lomutoPartition(low, high, [pivot](const auto& it) { return it < pivot; });

		//sort only the smaller of the partiotions first
		//tail recurtion auxillary space gose from O(n) to O(logn) in worst case

		if (std::distance(low, middle) < std::distance(middle, high))
		{
			quickSortLeft(low, middle);
			low = middle + 1;
		}
		else {
			quickSortLeft(std::next(middle), high);
			high = middle;
		}
	}
}

template<typename RandIt>
void quickSortMedian(RandIt first, RandIt last)
{
	//if (first == last) { return; }

	auto low = first;
	auto high = last;
	while (low < high)
	{
		auto pivot = *medianOfThree(low, std::prev(high));
		auto middle = lomutoPartition(low, high, [pivot](const auto& it) { return it < pivot; });

		//quickSortMedian(first, middle);
		//quickSortMedian(std::next(middle), last);

		if (std::distance(low, middle) < std::distance(middle, high))
		{
			quickSortMedian(low, middle);
			low = middle + 1;
		}
		else {
			quickSortMedian(std::next(middle), high);
			high = middle;
		}
	}
}

template<class iter>
void Selection_sort(iter first, iter last)
{
	iter min = first;
	for (auto i = first; i != last; i++)
	{
		min = i;
		for (auto j = i + 1; j != last; j++)
		{
			if (*j < *min)
			{
				std::iter_swap(j, min);
			}
		}
	}
}

template<class pointer>
void mswap(pointer * a, pointer * b)
{
	auto temp = *a;
	*a = *b;
	*b = temp;
}

template<class List>
void Bubble_sort(List & list, int size)
{
	for (auto i = 0; i < size - 1; i++)
	{
		for (auto j = 0; j < size - i - 1; j++)
		{
			if (list[j] > list[j + 1])
			{
				mswap(&list[j], &list[j + 1]);
			}
		}
	}
	list.size();
}

#endif // !SORT_HPP
