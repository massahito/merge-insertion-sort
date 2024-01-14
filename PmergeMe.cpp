#include "PmergeMe.hpp"

size_t	PmergeMe::getJacobsthalNumber(size_t n) {
	return ((n < 2) ? n : getJacobsthalNumber(n - 1) + 2 * getJacobsthalNumber(n - 2));
}

// # vector
void	PmergeMe::swapVectorByStep(std::vector<int> &vec, size_t index, size_t step) {
	for (size_t i = index; i < index + step; i++)
		std::swap(vec[i], vec[i + step]);
}

void	PmergeMe::splitVectorIntoMainChainAndSubChain(std::vector<int> &vec, int step, std::vector<int> &main_chain, std::vector<int> &sub_chain) {

	std::vector<int>	temp_chain = sub_chain;

	sub_chain.clear();
	for (size_t i = 0; i < vec.size(); i++) {
		if ((i / step) % 2 == 0)
			main_chain.push_back(vec[i]);
		else
			sub_chain.push_back(vec[i]);
	}
	for (size_t i = 0; i < temp_chain.size(); i++)
		sub_chain.push_back(temp_chain[i]);
}

size_t	PmergeMe::binarySearchByStep(std::vector<int> &main_chain, int number, size_t end, size_t step) {
	size_t	left = 0;
	size_t	right = end;

	if (number < main_chain[0])
		return (0);
	while (right - left > 1) {
		size_t mid = (right + left) / 2;
		if (main_chain[mid * step] < number)
			left = mid;
		else
			right = mid;
	}
	return (right * step);
}


void	PmergeMe::insertSubchainIntoMainchain(std::vector<int> &main_chain, std::vector<int> &sub_chain, size_t step) {
	// TODO this order must be implemented by jacovsthal number's order
	size_t	count = 0;

	for (size_t i = 0; i < sub_chain.size(); i+=step)	{
		// binary search
		size_t index = binarySearchByStep(main_chain, sub_chain[i], count, step);
		 for (size_t j = 0; j < step; j++)
		 		main_chain.insert(main_chain.begin() + index + j, sub_chain[i + j]);
		 count += 2;
	}
}

std::vector<int>	PmergeMe::mergeInsertionSort(std::vector<int> vec, size_t step) {

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

	// recursion 
	vec = mergeInsertionSort(vec, step * 2);

	// separate vector to main_chain, sub_chain:
	splitVectorIntoMainChainAndSubChain(vec, step, main_chain, sub_chain);
	
	// insert sub_chain to main_chain
	insertSubchainIntoMainchain(main_chain, sub_chain, step);

	// return main_chain
	return (main_chain);
}


// # List

// get iterator
std::list<int>::iterator	PmergeMe::getIndexListIterator(std::list<int> &lst, size_t index) {
	std::list<int>::iterator	iter = lst.begin();
	for (size_t i = 0; i < index; i++)
		iter++;
	return (iter);
}

int		PmergeMe::getIndexListNumber(std::list<int> lst, size_t index) {
	return (*getIndexListIterator(lst, index));
}

// swap function
void	PmergeMe::swapListByStep(std::list<int> &lst, size_t index, size_t step) {
	std::list<int>::iterator	first_iter = getIndexListIterator(lst, index);
	std::list<int>::iterator	second_iter= getIndexListIterator(lst, index + step);
	for (size_t i = 0; i < step; i++) {
		std::swap(*first_iter, *second_iter);
		first_iter++;
		second_iter++;
	}
}

void	PmergeMe::splitListIntoMainChainAndSubChain(std::list<int> &lst, int step, std::list<int> &main_chain, std::list<int> &sub_chain) {

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
}

size_t	PmergeMe::binarySearchByStep(std::list<int> &main_chain, int number, size_t end, size_t step) {
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

void	PmergeMe::insertSubchainIntoMainchain(std::list<int> &main_chain, std::list<int> &sub_chain, size_t step) {
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

std::list<int>	PmergeMe::mergeInsertionSort(std::list<int> lst, size_t step) {

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

