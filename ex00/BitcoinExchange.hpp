/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:41:59 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/07 15:35:54 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define _END	"\033[0m"
#define _BLACK	"\033[0;30m"
#define _RED	"\033[0;31m"
#define _GREEN	"\033[0;32m"
#define _YELLOW	"\033[0;33m"
#define _BLUE	"\033[0;34m"
#define _PURPLE	"\033[0;35m"
#define _CYAN	"\033[0;36m"

#include <map>
#include <regex.h>
#include <fstream>
#include <cstdlib>
#include <iostream>

class	BitcoinExchange {
	
	private:
		std::map<std::string, double>	_database;

	public:
	// Constructors
		BitcoinExchange(void);
		BitcoinExchange(std::string database);
		BitcoinExchange(const BitcoinExchange &toCopy);

	// Destructor
		~BitcoinExchange(void);

	// Overload operator
		BitcoinExchange &operator=(const BitcoinExchange &toCopy);

	// Public method
		void	searchValue(char *database);
};
