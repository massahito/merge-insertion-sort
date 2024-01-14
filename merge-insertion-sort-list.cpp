#include "merge-insertion-sort-list.hpp"

// get iterator
std::list<int>::iterator	getIndexListIterator(std::list<int> &lst, size_t index) {
	std::list<int>::iterator	iter = lst.begin();
	for (size_t i = 0; i < index; i++)
		iter++;
	return (iter);
}

int		getIndexListNumber(std::list<int> lst, size_t index) {
	return (*getIndexListIterator(lst, index));
}

// swap function
void	swapListByStep(std::list<int> &lst, size_t index, size_t step) {
	std::list<int>::iterator	first_iter = getIndexListIterator(lst, index);
	std::list<int>::iterator	second_iter= getIndexListIterator(lst, index + step);
	for (size_t i = 0; i < step; i++) {
		std::swap(*first_iter, *second_iter);
		first_iter++;
		second_iter++;
	}
}

void	splitListIntoMainChainAndSubChain(std::list<int> &lst, int step, std::list<int> &main_chain, std::list<int> &sub_chain) {

	std::list<int>	temp_chain = sub_chain;

	sub_chain.clear();
	for (size_t i = 0; i < lst.size(); i++) {
		if ((i / step) % 2 == 0)
			main_chain.push_back(getIndexListNumber(lst, i));
		else
			sub_chain.push_back(getIndexListNumber(lst, i));
	}
	for (size_t i = 0; i < temp_chain.size(); i++)
		sub_chain.push_back(getIndexListNumber(temp_chain, i));
	
	// print main_chain and sub_chain
	std::cout << "--------main_chain-------" << std::endl;
	for (size_t i = 0; i < main_chain.size(); i++)
		std::cout << getIndexListNumber(main_chain, i) << " ";
	std::cout << std::endl;
	std::cout << "--------sub_chain-------" << std::endl;
	for (size_t i = 0; i < sub_chain.size(); i++)
		std::cout << getIndexListNumber(sub_chain, i) << " ";
	std::cout << std::endl;
}

size_t	binarySearchByStep(std::list<int> &main_chain, int number, size_t end, size_t step) {
	size_t	left = 0;
	size_t	right = end;

	if (number < getIndexListNumber(main_chain, 0))
		return (0);
	while (right - left > 1) {
		size_t mid = (right + left) / 2;
		if (getIndexListNumber(main_chain, mid * step) < number)
			left = mid;
		else
			right = mid;
	}
	return (right * step);
}

void	insertSubchainIntoMainchain(std::list<int> &main_chain, std::list<int> &sub_chain, size_t step) {
	// TODO this order must be implemented by jacovsthal number's order
	size_t	count = 0;
	for (size_t i = 0; i < sub_chain.size(); i+=step)	{
		// binary search
		size_t index = binarySearchByStep(main_chain, getIndexListNumber(sub_chain, i), count, step);
		 for (size_t j = 0; j < step; j++)
		 		main_chain.insert(getIndexListIterator(main_chain, index + j), getIndexListNumber(sub_chain, i + j));
		 count += 2;
	}
}

std::list<int>	mergeInsertionSort(std::list<int> lst, size_t step) {

	std::list<int>	main_chain, sub_chain;
	size_t				i = 0;
	size_t				pair_size = step * 2;

	if (lst.size() <= step)
		return (lst);

	// sort By step
	while (i + pair_size <= lst.size()) {
			if (getIndexListNumber(lst, i) < getIndexListNumber(lst, i + step))
				swapListByStep(lst, i, step);
		i += pair_size;
	}
	if (lst.size() % pair_size) {
		sub_chain = std::list<int>(getIndexListIterator(lst, i), lst.end());
		lst.resize((lst.size() / pair_size) * pair_size);
	}

	// recursion 
	lst = mergeInsertionSort(lst, step * 2);

	// separate vector to main_chain, sub_chain:
	splitListIntoMainChainAndSubChain(lst, step, main_chain, sub_chain);
	
	// insert sub_chain to main_chain
	insertSubchainIntoMainchain(main_chain, sub_chain, step);

	// return main_chain
	return (main_chain);
}
