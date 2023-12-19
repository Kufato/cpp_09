/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:41:59 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/19 16:02:01 by axcallet         ###   ########.fr       */
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
#include <time.h>
#include <regex.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iostream>

class	BitcoinExchange {

	private:
		static std::map<std::string, double>	_database;
		static bool	parsingDataFile(void);
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &toCopy);

	public:
	// Constructors

	// Destructor
		~BitcoinExchange(void);

	// Overload operator
		BitcoinExchange &operator=(const BitcoinExchange &toCopy);

	// Public method
		static void	searchValue(char *input);
};
