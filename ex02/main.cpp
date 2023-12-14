/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:29 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/14 13:40:20 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
static void	print(const T &container, std::string message) {
	std::cout << message << std::flush;
	for (typename T::const_iterator	it = container.begin(); it != container.end(); it++)
		std::cout << " " << *it << std::flush;
	std::cout << std::endl;
}

static bool	checkNegativeNumber(char **argv) {
	for (int i = 1; argv[i]; i++) {
		if (std::atoi(argv[i]) < 0)
			return (false);
	}
	return (true);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << _RED << "error: you must enter a series of numbers" << _END << std::endl;
		return (1);
	}
	if (argc < 3) {
		std::cerr << _RED << "error: one number is not enough" << _END << std::endl;
		return (1);
	}
	try {
		std::deque<int>		deque;
		std::vector<int>	vector;
		double				vectorTime, dequeTime;
		clock_t				mainStart, vectorEnd, dequeEnd;

		if (!checkNegativeNumber(argv))
			throw PmergeMe::NegativeNumberException();
		for (int i = 1; argv[i]; i++)
			vector.push_back(std::atoi(argv[i]));
		for (int i = 1; argv[i]; i++)
			deque.push_back(std::atoi(argv[i]));
		print(vector, "Before:\t");
		mainStart = clock();
		vector = PmergeMe::algorithmVector(vector);
		vectorEnd = clock();
		deque = PmergeMe::algorithmDeque(deque);
		dequeEnd = clock();
		print(vector, "After:\t");
		vectorTime = (vectorEnd - mainStart) / (double) CLOCKS_PER_SEC * 1000000.0;
		dequeTime = (dequeEnd - vectorEnd) / (double) CLOCKS_PER_SEC * 1000000.0;
		std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << std::flush;
		std::cout << std::fixed << std::setprecision(5) << vectorTime << " us" << std::endl;
		std::cout << "Time to process a range of " << deque.size() << " elements with std::deque : " << std::flush;
		std::cout << std::fixed << std::setprecision(5) << dequeTime << " us" << std::endl;
	}
	catch(std::exception &exep) {
		std::cerr << _RED << exep.what() << _END << std::endl;
	}
	return (0);
}