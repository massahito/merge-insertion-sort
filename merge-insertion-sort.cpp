#include "merge-insertion-sort.hpp"

/*
	[3, 1, 11, 9, 2, 12, 0, 5, 8, 6, 4, 10, 7]	step=1
	[[3, 1], [11, 9], [12, 2], [5, 0], [8, 6], [10, 4]]	step=2
*/

void	swapVectorByStep(std::vector<int> &vec, size_t index, size_t step) {
	for (size_t i = index; i < index + step; i++)
		std::swap(vec[i], vec[i + step]);
}

void	merge_insertion_sort(std::vector<int> &vec, size_t step) {

	std::vector<int>	main_chain, sub_chain;
	size_t				i = 0;
	size_t				pair_size = step * 2;

	if (vec.size() <= step)
		return ;

	// sort By step
	while (i + pair_size <= vec.size()) {
			if (vec[i] < vec[i + step])
				swapVectorByStep(vec, i, step);
		i += pair_size;
	}
	if (vec.size() % pair_size) {
		sub_chain = std::vector<int>(vec.begin() + i, vec.end());
		vec.resize((vec.size() / pair_size) * pair_size);
	}

	// print
	std::cout << "---------finish----------" << std::endl;
	std::cout << "step: " << step << std::endl;
	std::cout << "---------print vec----------" << std::endl;
	for (size_t i = 0; i < vec.size(); i++) std::cout << vec[i] << " ";
	std::cout << std::endl;
	std::cout << "---------print sub chain----------" << std::endl;
	for (size_t i = 0; i < sub_chain.size(); i++) std::cout << sub_chain[i] << " ";
	std::cout << std::endl;

	merge_insertion_sort(vec, step * 2);


	// separate vector to main_chain, sub_chain:
	
	// insert sub_chain to main_chain
	
	// return main_chain
}
