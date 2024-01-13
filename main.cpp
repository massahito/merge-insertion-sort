#include "merge-insertion-sort.hpp"

#include <iostream>
#include <vector>
#include <random>


int main(int argc, char *argv[]) {

	if (argc != 2)
		return (1);

	// get size fromt argv
	int	size = std::atoi(argv[1]);

	// generate vector
	std::vector<int>	vct(size);
	for (size_t i = 0; i < vct.size(); i++)
		vct[i] = i;

	// shuffle vector values
	std::random_device	seed_gen;
	std::mt19937		engine(seed_gen());
	std::shuffle(vct.begin(), vct.end(), engine);

	// print shuffled vector values
	std::cout << "------original vector number------" << std::endl;
	for (size_t i = 0; i < vct.size(); i++) std::cout << vct[i] << " ";
	std::cout << std::endl;
	
	merge_insertion_sort(vct, 1);


}

