/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:29 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/12 15:47:02 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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
		// std::deque<int>		XDeque;
		std::vector<int>	XVector;

		for (int i = 1; argv[i]; i++) {
			if (std::atoi(argv[i]) < 0)
				throw PmergeMe::NegativeNumberException();
		}
		for (int i = 1; argv[i]; i++)
			XVector.push_back(std::atoi(argv[i]));
		 XVector = PmergeMe::algorithmVector(XVector);
		// PmergeMe::algorithmList(argc, argv);
	}
	catch(std::exception &exep) {
		std::cerr << exep.what() << std::endl;
	}
	return (0);
}