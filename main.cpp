#include "PmergeMe.hpp"
#include <iostream>
#include <random>
#include <algorithm>


int main(int argc, char *argv[]) {

	if (argc != 2)
		return (1);

	// get size fromt argv
	int	size = std::atoi(argv[1]);

	// generate vector
	{
		std::vector<int>	unsorted(size);
		for (size_t i = 0; i < unsorted.size(); i++)
			unsorted[i] = i;

		// shuffle vector values
		std::random_device	seed_gen;
		std::mt19937		engine(seed_gen());
		std::shuffle(unsorted.begin(), unsorted.end(), engine);

		// print shuffled vector values
		std::cout << "------original vector number------" << std::endl;
		for (size_t i = 0; i < unsorted.size(); i++) std::cout << unsorted[i] << " ";
		std::cout << std::endl;

		// merge-insertion sort	
		std::vector<int>	sorted = PmergeMe::mergeInsertionSort(unsorted);

		// print sorted vector values
		std::cout << "------sorted vector number------" << std::endl;
		for (size_t i = 0; i < sorted.size(); i++) std::cout << sorted[i] << " ";
		std::cout << std::endl;
	}

	{
		std::list<int>	unsorted;
		for (size_t i = 0; i < static_cast<size_t>(size); i++)
			unsorted.push_back(size - i);


		// print shuffled vector values
		std::cout << "------original list number------" << std::endl;
		for (std::list<int>::iterator iter = unsorted.begin(); iter != unsorted.end(); iter++) std::cout << *iter << " ";
		std::cout << std::endl;

		// merge-insertion sort	
		std::list<int>	sorted = PmergeMe::mergeInsertionSort(unsorted);

		// print sorted vector values
		std::cout << "------sorted list number------" << std::endl;
		for (std::list<int>::iterator iter = sorted.begin(); iter != sorted.end(); iter++) std::cout << *iter << " ";
		std::cout << std::endl;
	}


}

