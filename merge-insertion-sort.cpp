#include "merge-insertion-sort.hpp"

/*
	[3, 1, 11, 9, 2, 12, 0, 5, 8, 6, 4, 10, 7]	step=1
	[[3, 1], [11, 9], [12, 2], [5, 0], [8, 6], [10, 4]]	step=2
*/

void	swapVectorByStep(std::vector<int> &vec, size_t index, size_t step) {
	for (size_t i = index; i < index + step; i++)
		std::swap(vec[i], vec[i + step]);
}

void	SplitVectorIntoMainChainAndSubChain(std::vector<int> &vec, int step, std::vector<int> &main_chain, std::vector<int> &sub_chain) {

	std::vector<int>	temp_chain = sub_chain;

	sub_chain.resize(0);
	for (size_t i = 0; i < vec.size(); i++) {
		if ((i / step) % 2 == 0)
			main_chain.push_back(vec[i]);
		else
			sub_chain.push_back(vec[i]);
	}
	for (size_t i = 0; i < temp_chain.size(); i++)
		sub_chain.push_back(temp_chain[i]);
	
	// print main_chain and sub_chain
	std::cout << "--------main_chain-------" << std::endl;
	for (size_t i = 0; i < main_chain.size(); i++)
		std::cout << main_chain[i] << " ";
	std::cout << std::endl;
	std::cout << "--------sub_chain-------" << std::endl;
	for (size_t i = 0; i < sub_chain.size(); i++)
		std::cout << sub_chain[i] << " ";
	std::cout << std::endl;
}

size_t	binarySearchByStep(std::vector<int> &main_chain, int number, size_t end, size_t step) {
	size_t	left = 0;
	size_t	right = end;

	std::cout << "---BinarySearch---" << std::endl;
	std::cout << "search number: " << number << " step: "  << step << " end: "  << end << std::endl;
	if (number < main_chain[0])
		return (0);
	while (right - left > step) {
		std::cout << "left: " << left << " " << " right: " << right << std::endl;
		size_t mid = (right + left) / 2;
		if (main_chain[mid] <= number)
			left = mid;
		else
			right = mid;
		std::cout << "cmp: " << main_chain[mid] << " " << "number: " << number<< std::endl;
	}
	return (right);
}

void	InsertSubchainIntoMainchain(std::vector<int> &main_chain, std::vector<int> &sub_chain, size_t step) {
	// TODO this order must be implemented by jacovsthal number's order
	size_t	end = 0;
	for (size_t i = 0; i < sub_chain.size(); i+=step)	{
		// binary search
		size_t index = binarySearchByStep(main_chain, sub_chain[i], end, step);
		std::cout << "i: " << i << " number: " << sub_chain[i] << " index: " << index << std::endl;
		 for (size_t j = 0; j < step; j++)
		 		main_chain.insert(main_chain.begin() + index + j, sub_chain[i + j]);
		 std::cout << "---main chain after insertion---" << std::endl;
		 for (size_t j = 0; j < main_chain.size(); j++)
			 std::cout << main_chain[j] << " ";
		 std::cout << std::endl;
		 end += (step * 2);
	}
}

std::vector<int>	merge_insertion_sort(std::vector<int> &vec, size_t step) {

	std::vector<int>	main_chain, sub_chain;
	size_t				i = 0;
	size_t				pair_size = step * 2;

	if (vec.size() <= step)
		return (vec);

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
	//std::cout << "---------finish----------" << std::endl;
	//std::cout << "step: " << step << std::endl;
	//std::cout << "---------print vec----------" << std::endl;
	//for (size_t i = 0; i < vec.size(); i++) std::cout << vec[i] << " ";
	//std::cout << std::endl;
	//std::cout << "---------print sub chain----------" << std::endl;
	//for (size_t i = 0; i < sub_chain.size(); i++) std::cout << sub_chain[i] << " ";
	//std::cout << std::endl;

	// recursion 
	vec = merge_insertion_sort(vec, step * 2);

	// separate vector to main_chain, sub_chain:
	SplitVectorIntoMainChainAndSubChain(vec, step, main_chain, sub_chain);
	
	// insert sub_chain to main_chain
	InsertSubchainIntoMainchain(main_chain, sub_chain, step);

	// return main_chain
	return (main_chain);
}
