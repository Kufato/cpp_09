/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:41:48 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/18 17:01:55 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// Constructor
static bool	parsingDataFile(void) {
	char			*endPtr;
	double			value;
	std::string		date;
	std::string		line;
	std::ifstream	file;

	file.open("data.csv");
	if (!file.is_open()) {
		std::cerr << _RED << "Error: could not open the file" << _END << std::endl;
		return (false);
	}
	getline(file, line);
	if (line != "date,exchange_rate") {
		std::cerr << _RED << "Error: first line of data.csv must be \"date,exchange_rate\"" << _END << std::endl;
		return (false);
	}
	while (getline(file, line)) {
		if (line.empty()) {
			std::cerr << _RED << "Error: empty line are not welcom" << _END << std::endl;
			return (false);
		}
		std::size_t pos = line.find(",");
		if (pos != std::string::npos) {
			date = line.substr(0, (pos - 1));
			value = std::strtod(line.substr(pos + 1).c_str(), &endPtr);
			if (line.substr(pos + 1) == endPtr) {
				std::cerr << _RED << "Error: no values found => " << line << _END << std::endl;
				return (false);
			}
			if (!checkDate(date) || !checkValue(value))
				return (false);
			else
				this->_database[date] = value;
		}
		else {
			std::cerr << _RED << "Error: the line is in the wrong format => " << line << _END << std::endl;
			return (false);
		}
	}
	file.close();
	return (true);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &toCopy) {
	*this = toCopy;
	return ;
}

// Destructor
BitcoinExchange::~BitcoinExchange(void) {
	return ;
}

// Overload operator
BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &toCopy) {
	if (this == &toCopy)
		return (*this);
	this->_database = toCopy._database;
	return (*this);
}

// Public method
static bool checkDate(std::string date) {
	int					year, month, day;
	char				dash1, dash2, space1, space2, pipe;
	char				*dateFormat;
	double				value;
	struct tm			tm;
	std::istringstream	checkDate(date);

	if (!checkDate >> year >> dash1 >> month >> dash2 >> day >> space1 >> pipe >> space2 >> value && dash1 != '-' && dash2 != '-') {
		std::cerr << "Error: bad input => " << date << std::endl;
		return (false);
	}
	dateFormat = strptime(date, "%Y-%m-%d", &tm)
	if ((tm.tm_year == 2009 && tm.tm_mon == 1 && tm.tm_mday < 2) || tm.tm_year < 2009) {
		std::cerr << "Error: the date is too old" << std::endl;
		return false;
	}
	if (tm.tm_mon > 12 || tm.tm_mday > 31) {
		std::cerr << "Error: bad input => " << dateError << std::endl;
		return false;
	}
	if ((tm.tm_mon == 4 || tm.tm_mon == 6 || tm.tm_mon == 9 || tm.tm_mon == 11) && tm.tm_mday > 30) {
		std::cerr << "Error: bad input => " << dateError << std::endl;
		return false;
	}
	if (tm.tm_mon == 2) {
		if ((tm.tm_year % 4 == 0 && tm.tm_year % 100 != 0) || (tm.tm_year % 400 == 0)) {
			if (tm.tm_mday > 29) {
		std::cerr << "Error: bad input => " << dateError << std::endl;
				return false;
			}
		}
		else if (tm.tm_mday > 28) {
		std::cerr << "Error: bad input => " << dateError << std::endl;
			return false;
		}
	}
	return true;
}

static bool checkValue(double value) {
	if (value > 1000.0) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	if (value < 0.0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	return true;
}

void	BitcoinExchange::searchValue(char *database) {
	char			*endPtr;
	double			value;
	std::string		date;
	std::string		line;
	std::ifstream	databaseFile;

	if (!parsingDataFile())
		return ;
	databaseFile.open(database);
	if (!databaseFile.is_open()) {
		std::cerr << _RED << "Error: could not open the file" << _END << std::endl;
		return ;
	}
	getline(databaseFile, line);
	if (line.empty()) {
		std::cerr << _RED << "Error: the file is empty" << _END << std::endl;
		return ;
	}
	if (line != "date | value") {
		std::cerr << _RED << "Error: the first line must be \"date | value\"" << _END << std::endl;
		return ;
	}
	while (getline(databaseFile, line)) {
		std::size_t pos = line.find(" | ");
		date = line.substr(0, pos - 1);
		value = std::strtod(line.substr(pos + 2).c_str(), &endPtr);
		if (checkDate(line)) {
			if (checkValue(line)) {
				std::map<std::string, double>::iterator	it = this->_database.find(date); 
				if (it == this->_database.end()) {
					it = this->_database.lower_bound(date);
					if (it != this->_database.begin())
						--it;
				}
				std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
			}
		}
	}
	return ;
}