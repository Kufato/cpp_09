/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:19 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/14 13:49:04 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Vector
static std::vector<int>::iterator binarySearchVector(std::vector<int> &A, int target) {
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

std::vector<int>	PmergeMe::algorithmVector(std::vector<int> X) {
	std::vector<int>					S;
	std::vector<std::pair<int, int> >	Vpair;

	if (X.size() == 1)
		return (X);
	// Create pairs of numbers and add the largest of each pair to S
	for (std::vector<int>::iterator it = X.begin(); it != X.end(); it += 2) {
		if (it + 1 == X.end())
			break ;
		std::pair<int, int>	pair;
		pair.first = (*it > *(it + 1)) ? *it : *(it + 1);
		pair.second = (*it < *(it + 1)) ? *it : *(it + 1);
		Vpair.push_back(pair);
		S.push_back(pair.first);
	}
	// recursive call
	S = algorithmVector(S);
	// insert element paired with smallest element in S
	for (std::vector<std::pair<int, int> >::iterator it = Vpair.begin(); it != Vpair.end(); ) {
		if (it->first == S.front()) {
			S.insert(S.begin(), it->second);
			it = Vpair.erase(it); // Update the iterator after erasing
		}
		else
			++it;
	}
	// insert the elements remaining in S
	for (std::vector<std::pair<int, int> >::iterator it = Vpair.begin(); it != Vpair.end(); it++)
		S.insert(binarySearchVector(S, it->second), it->second);
	// insert the last element of X if X has an odd number of elements
	if (X.size() % 2)
		S.insert(S.begin(), X.back());
	return (S);
}

// Deque
static std::deque<int>::iterator binarySearchVector(std::deque<int> &A, int target) {
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

std::deque<int>	PmergeMe::algorithmDeque(std::deque<int> X) {
	std::deque<int>						S;
	std::deque<std::pair<int, int> >	Vpair;

	if (X.size() == 1)
		return (X);
	// Create pairs of numbers and add the largest of each pair to S
	for (std::deque<int>::iterator it = X.begin(); it != X.end(); it += 2) {
		if (it + 1 == X.end())
			break ;
		std::pair<int, int>	pair;
		pair.first = (*it > *(it + 1)) ? *it : *(it + 1);
		pair.second = (*it < *(it + 1)) ? *it : *(it + 1);
		Vpair.push_back(pair);
		S.push_back(pair.first);
	}
	// recursive call
	S = algorithmDeque(S);
	// insert element paired with smallest element in S
	for (std::deque<std::pair<int, int> >::iterator it = Vpair.begin(); it != Vpair.end(); ) {
		if (it->first == S.front()) {
			S.insert(S.begin(), it->second);
			it = Vpair.erase(it); // Update the iterator after erasing
		}
		else
			++it;
	}
	// insert the elements remaining in S
	for (std::deque<std::pair<int, int> >::iterator it = Vpair.begin(); it != Vpair.end(); it++)
		S.insert(binarySearchVector(S, it->second), it->second);
	// insert the last element of X if X has an odd number of elements
	if (X.size() % 2)
		S.insert(S.begin(), X.back());
	return (S);
}

// Exceptions
const char	*PmergeMe::NegativeNumberException::what(void) const throw() {
	return ("error: negative numbers are not welcome");
}