/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:23:09 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/11 14:34:47 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << _RED << "Wrong number of arguments !" << _END << std::endl;
		return (1);
	}
	try {
		RPN::reversePolishNotation(argv[1]);
	}
	catch (std::exception &exep) {
		std::cerr << exep.what() << std::endl;
	}
	return (0);
}