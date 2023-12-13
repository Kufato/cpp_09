/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:19 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/13 16:51:39 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Public method
static std::vector<int>::iterator binarySearchVector(std::vector<int>& A, int T) {
	int	mid;
	int	left = 0;
	int	right = (A.size() - 1);

	while (left <= right) {
		mid = (left + right) / 2;
		if (A[mid] < T)
			left = mid + 1;
		else if (A[mid] > T)
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
	for (std::vector<int>::iterator it = X.begin(); it != X.end(); it += 2) {
		if (it + 1 == X.end())
			break ;
		std::pair<int, int>	pair;
		pair.first = (*it > *(it + 1)) ? *it : *(it + 1);
		pair.second = (*it < *(it + 1)) ? *it : *(it + 1);
		Vpair.push_back(pair);
		S.push_back(pair.first);
	}
	// std::cout << "Vpair" << std::endl; 
	// for (std::vector<std::pair<int, int> >::iterator it = Vpair.begin(); it != Vpair.end(); it++) {
	// 	std::cout << it->first << " and " << it->second << std::endl;
	// }
	// std::cout << std::endl;
	S = algorithmVector(S);
	// std::cout << "S = "; 
	// for (std::vector<int>::iterator it = S.begin(); it != S.end(); it++) {
	// 	std::cout << *it << " "; 
	// }
	// std::cout << std::endl;
	for (std::vector<std::pair<int, int> >::iterator it = Vpair.begin(); it != Vpair.end(); ) {
		if (it->first == S.front()) {
			S.insert(S.begin(), it->second);
			it = Vpair.erase(it);  // Update the iterator after erasing
		}
		else
			++it;
	}
	// std::cout << "S = "; 
	// for (std::vector<int>::iterator it = S.begin(); it != S.end(); it++) {
	// 	std::cout << *it << " "; 
	// }
	// std::cout << std::endl;
	for (std::vector<std::pair<int, int> >::iterator it = Vpair.begin(); it != Vpair.end(); it++)
		S.insert(binarySearchVector(S, it->second), it->second);
	// std::cout << "S = "; 
	// for (std::vector<int>::iterator it = S.begin(); it != S.end(); it++) {
	// 	std::cout << *it << " "; 
	// }
	// std::cout << std::endl;
	if (X.size() % 2)
		S.insert(S.begin(), X.back());
	return (S);
}
// Exceptions
const char	*PmergeMe::NegativeNumberException::what(void) const throw() {
	return ("error: negative numbers are not welcome");
}