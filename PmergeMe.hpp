#ifndef	PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <list>

class	PmergeMe {
	public:
		static std::list<int>				mergeInsertionSort(std::list<int> lst, size_t step = 1);
		static std::vector<int>			mergeInsertionSort(std::vector<int> vec, size_t step = 1);
	private:
		PmergeMe();
		PmergeMe(PmergeMe const &p_merge_me);
		~PmergeMe();
		PmergeMe	&operator=(PmergeMe const &p_merge_me);
		size_t							getJacobsthalNumber(size_t n);
		// #vector
		static void						swapVectorByStep(std::vector<int> &vec, size_t index, size_t step);
		static void						splitVectorIntoMainChainAndSubChain(std::vector<int> &vec, int step, std::vector<int> &main_chain, std::vector<int> &sub_chain);
		static size_t					binarySearchByStep(std::vector<int> &main_chain, int number, size_t end, size_t step);
		static void						insertSubchainIntoMainchain(std::vector<int> &main_chain, std::vector<int> &sub_chain, size_t step);

		// #list
		static std::list<int>::iterator	getIndexListIterator(std::list<int> &lst, size_t index);
		static int						getIndexListNumber(std::list<int> lst, size_t index);
		static void						swapListByStep(std::list<int> &lst, size_t index, size_t step);
		static void						splitListIntoMainChainAndSubChain(std::list<int> &lst, int step, std::list<int> &main_chain, std::list<int> &sub_chain);
		static size_t					binarySearchByStep(std::list<int> &main_chain, int number, size_t end, size_t step);
		static void						insertSubchainIntoMainchain(std::list<int> &main_chain, std::list<int> &sub_chain, size_t step);

};

#endif
