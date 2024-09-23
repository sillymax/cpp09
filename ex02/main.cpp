/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:30:35 by ychng             #+#    #+#             */
/*   Updated: 2024/09/23 22:08:38by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cstdlib>

using std::cout;
using std::endl;
using std::vector;
using std::list;

void insertSort(std::vector<int>& vec, int target)
{
	int left = 0;
	int right = vec.size() - 1;

	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (target < vec[middle])
			right = middle - 1;
		else
			left = middle + 1;
	}
	vec.insert(vec.begin() + left, target);
}

void insertSort(std::list<int>& lst, int target)
{
	int left = 0;
	int right = lst.size() - 1;
	std::list<int>::iterator it = lst.begin();

	while (left <= right)
	{
		int middle = (left + right) / 2;
		std::advance(it, middle);

		if (target < *it)
			right = middle - 1;
		else
			left = middle + 1;
		it = lst.begin();
	}

	it = lst.begin();
    std::advance(it, left);
    lst.insert(it, target);
}

void mergeSort(std::vector<int>& vec)
{
	if (vec.size() < 2)
		return ;

	int middle = vec.size() / 2;
	std::vector<int> left(vec.begin(), vec.begin() + middle);
	std::vector<int> right(vec.begin() + middle, vec.end());

	mergeSort(left);
	mergeSort(right);

	size_t i = 0, j = 0, k = 0;
	while (i < left.size() && j < right.size())
	{
		if (left[i] <= right[j])
			vec[k++] = left[i++];
		else
			vec[k++] = right[j++];
	}
	while (i < left.size())
		vec[k++] = left[i++];
	while (j < right.size())
		vec[k++] = right[j++];
}

void mergeSort(std::list<int>& lst)
{
	if (lst.size() < 2)
		return ;
	
	// Find the middle iterator
	std::list<int>::iterator middle = lst.begin();
	std::advance(middle, lst.size() / 2);

	std::list<int> left(lst.begin(), middle);
	std::list<int> right(middle, lst.end());

	mergeSort(left);
	mergeSort(right);

	lst.clear();
	std::list<int>::iterator it1 = left.begin();
	std::list<int>::iterator it2 = right.begin();
	while (it1 != left.end() && it2 != right.end())
	{
		if (*it1 <= *it2)
		{
			lst.push_back(*it1);
			it1++;
		}
		else
		{
			lst.push_back(*it2);
			it2++;
		}
	}
	while (it1 != left.end())
	{
		lst.push_back(*it1);
		it1++;
	}
	while (it2 != right.end())
	{
		lst.push_back(*it2);
		it2++;
	}
}

void fordJohnsonSortVector(std::vector<int>& vec)
{
	int n = vec.size();

	// Stage 1: Pair and sort elements
	for (size_t i = 0; i + 1 < vec.size(); i += 2)
	{
		if (vec[i] > vec[i + 1])
			std::swap(vec[i], vec[i + 1]);
	}

	// Create a vector for the larger elements
	std::vector<int> sortedElements;
	for (int i = 1; i < n; i += 2)
		sortedElements.push_back(vec[i]);
	mergeSort(sortedElements);

	//
	for (int i = 0; i < n; i += 2)
		insertSort(sortedElements, vec[i]);
	vec = sortedElements;
}

void fordJohnsonSortList(std::list<int>& lst)
{
	int n = lst.size();

	// Stage 1: pair and sort elements
	std::list<int>::iterator it = lst.begin();
	for (int i = 0; i + 1 < n; i += 2)
	{
		std::list<int>::iterator nextIt = it;
		nextIt++;
		if (nextIt != lst.end() && *it > *nextIt)
			std::swap(*it, *nextIt);
		std::advance(it, 2);
	}

	// Create a list for the larger elements
    std::list<int> sortedElements;
    it = lst.begin();
    std::advance(it, 1); // Move to the first larger element
    for (int i = 1; i < n; i += 2)
    {
        sortedElements.push_back(*it);
        std::advance(it, 2); // Move to the next larger element
    }
	mergeSort(sortedElements);

	it = lst.begin();
	for (int i = 0; i < n; i += 2)
	{
		insertSort(sortedElements, *it);
		std::advance(it, 2);
	}
	lst = sortedElements;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "error: only ./PmergeMe <input> is allowed.\n";
		return -1;
	}

	std::vector<int> numbersVector;
	std::list<int> numbersList;
	for (int i = 1; i < argc; i++)
	{
		int num = atoi(argv[i]);
		if (num < 0)
		{
			std::cout << "error: only positive numbers are allowed.\n";
			return -1;
		}

		numbersVector.push_back(num);
		numbersList.push_back(num);
	}

	std::cout << "Before: ";
	for (size_t i = 0; i < numbersVector.size(); i++)
		std::cout << numbersVector[i] << " ";
	std::cout << "\n";

	struct timeval startVector, endVector;
	gettimeofday(&startVector, NULL);
	fordJohnsonSortVector(numbersVector);
	gettimeofday(&endVector, NULL);

	struct timeval startList, endList;
	gettimeofday(&startList, NULL);
	fordJohnsonSortList(numbersList);
	gettimeofday(&endList, NULL);

	std::cout << "After: ";
	for (size_t i = 0; i < numbersVector.size(); i++)
		std::cout << numbersVector[i] << " ";
	std::cout << "\n";

    // std::cout << "After: ";
    // for (std::list<int>::iterator it = numbersList.begin(); it != numbersList.end(); it++)
    //     std::cout << *it << " ";
    // std::cout << "\n";

	long seconds = endVector.tv_sec - startVector.tv_sec;
	long microseconds = endVector.tv_usec - startVector.tv_usec;
	long elapsed = seconds * 1e6 + microseconds;
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : "
			  <<  static_cast<double>(elapsed) / 1e6 << " us\n";

	seconds = endList.tv_sec - startList.tv_sec;
	microseconds = endList.tv_usec - startList.tv_usec;
	elapsed = seconds * 1e6 + microseconds;
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::list : "
			  <<  static_cast<double>(elapsed) / 1e6 << " us\n";
}
