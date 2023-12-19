/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:43:12 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/19 11:35:52 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << _RED << "Wrong number of arguments !" << _END << std::endl;
		return (1);
	}
	BitcoinExchange::searchValue(argv[1]);
	return (0);
}