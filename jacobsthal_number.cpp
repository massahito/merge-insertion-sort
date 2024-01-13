#include <iostream>

size_t	getJacobsthalNumber(size_t n) {
	if (n <= 1)
		return (n);
	return (getJacobsthalNumber(n - 1) + 2 * getJacobsthalNumber(n - 2));
}

