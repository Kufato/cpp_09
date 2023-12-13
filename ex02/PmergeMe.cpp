/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:19 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/13 11:47:59 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Public method
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
	for (std::vector<std::pair<int, int> >::iterator it = Vpair.begin(); it != Vpair.end(); it++) {
		std::cout << it->first << " and " << it->second <<std::endl;
	}
	if (X.size() % 2)
		S.push_back(X.back());
	S = algorithmVector(S);
	return (S);
}

// Exceptions
const char	*PmergeMe::NegativeNumberException::what(void) const throw() {
	return ("error: negative numbers are not welcome");
}