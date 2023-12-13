/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:19 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/13 18:11:33 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Public method
template <typename T>
static typename T::iterator binarySearchVector(T& A, int target) {
	int	mid;
	int	left = 0;
	int	right = (A.size() - 1);

	while (left <= right) {
		mid = (left + right) / 2;
		if (A[mid] < target)
			left = mid + 1;
		else if (A[mid] > target)
			right = mid - 1;
		else
			return A.begin() + mid;
	}
	return A.begin() + left;
}
template <typename T>
T	PmergeMe::algorithm(T X) {
	T					S;
	T/*<std::pair<int, int> >*/	Vpair;

	if (X.size() == 1)
		return (X);
	for (typename T::iterator it = X.begin(); it != X.end(); it += 2) {
		if (it + 1 == X.end())
			break ;
		std::pair<int, int>	pair;
		pair.first = (*it > *(it + 1)) ? *it : *(it + 1);
		pair.second = (*it < *(it + 1)) ? *it : *(it + 1);
		Vpair.push_back(pair);
		S.push_back(pair.first);
	}
	S = algorithmVector(S);
	for (typename T/*<std::pair<int, int> >*/::iterator it = Vpair.begin(); it != Vpair.end(); ) {
		if (it->first == S.front()) {
			S.insert(S.begin(), it->second);
			it = Vpair.erase(it);  // Update the iterator after erasing
		}
		else
			++it;
	}
	for (typename T/*<std::pair<int, int> >*/::iterator it = Vpair.begin(); it != Vpair.end(); it++)
		S.insert(binarySearchVector(S, it->second), it->second);
	if (X.size() % 2)
		S.insert(S.begin(), X.back());
	return (S);
}
// Exceptions
const char	*PmergeMe::NegativeNumberException::what(void) const throw() {
	return ("error: negative numbers are not welcome");
}