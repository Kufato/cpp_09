/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:41:48 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/11 14:39:16 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// Constructor
BitcoinExchange::BitcoinExchange(void) {
	return ;
}
BitcoinExchange::BitcoinExchange(std::string database) {
	double			value;
	std::string		date;
	std::string		line;
	std::ifstream	file;

	file.open(database.c_str());
	if (!file.is_open()) {
		std::cerr << _RED << "error: could not open the file" << _END << std::endl;
		return ;
	}
	getline(file, line);
	while (getline(file, line)) {
		date = line.substr(0, 10);
		std::size_t pos = line.find(",");
		char *endPtr;
		value = std::strtod(line.substr(pos + 1).c_str(), &endPtr);
		this->_database[date] = value;
	}
	file.close();
	return ;
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
static bool checkPatternDate(const char *pattern, std::string date) {
	regex_t		preg;
	regmatch_t	pmatch;

	if (regcomp(&preg, pattern, REG_NOSUB | REG_EXTENDED))
		return false;
	if (!regexec(&preg, date.c_str(), 1, &pmatch, 0)) {
		regfree(&preg);
		return true;
	}
	regfree(&preg);
	return false;
}

static bool checkDate(std::string line) {
	const char	*patternDate = "^[0-9]{4,}-[0-9]{2}-[0-9]{2} \\| $";
	std::size_t pos = line.find("| ");
	std::string	dateTmp = line.substr(0, pos + 2);
	std::string dateError = line.substr(0, pos - 1);

	if (!checkPatternDate(patternDate, dateTmp)) {
		std::cerr << "Error: bad input => " << dateError << std::endl;
		return false;
	}
	int	year = std::atoi(line.substr(0, 4).c_str());
	int	month = std::atoi(line.substr(5, 2).c_str());
	int	day = std::atoi(line.substr(8, 2).c_str());
	if ((year == 2009 && month == 1 && day < 2) || year < 2009) {
		std::cerr << "Error: the date is too old" << std::endl;
		return false;
	}
	if (month > 12 || day > 31) {
		std::cerr << "Error: bad input => " << dateError << std::endl;
		return false;
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
		std::cerr << "Error: bad input => " << dateError << std::endl;
		return false;
	}
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			if (day > 29) {
		std::cerr << "Error: bad input => " << dateError << std::endl;
				return false;
			}
		}
		else if (day > 28) {
		std::cerr << "Error: bad input => " << dateError << std::endl;
			return false;
		}
	}
	return true;
}

static bool checkValue(std::string line) {
	char 		*endPtr;
	std::string	valueTmp = line.substr(13);
	double		value = std::strtod(valueTmp.c_str(), &endPtr);
	
	if (valueTmp.size() == 0) {
		std::cerr << "Error: no value found" << std::endl;
		return false;
	}
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

	databaseFile.open(database);
	if (!databaseFile.is_open()) {
		std::cerr << _RED << "error: could not open the file" << _END << std::endl;
		return ;
	}
	getline(databaseFile, line);
	if (line != "date | value") {
		std::cerr << _RED << "The first line must be \"date | value\"" << _END << std::endl;
		return ;
	}
	while (getline(databaseFile, line)) {
		if (checkDate(line)) {
			if (checkValue(line)) {
				std::size_t pos = line.find("| ");
				date = line.substr(0, pos - 1);
				value = std::strtod(line.substr(pos + 2).c_str(), &endPtr);
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