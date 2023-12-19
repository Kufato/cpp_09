/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:41:48 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/19 16:07:02 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::map<std::string, double>	BitcoinExchange::_database;

// Constructor
BitcoinExchange::BitcoinExchange(void) {
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
// -------------------- Utils --------------------
static bool checkPattern(const char *pattern, std::string line) {
	regex_t		preg;
	regmatch_t	pmatch;

	if (regcomp(&preg, pattern, REG_NOSUB | REG_EXTENDED))
		return false;
	if (!regexec(&preg, line.c_str(), 1, &pmatch, 0)) {
		regfree(&preg);
		return true;
	}
	regfree(&preg);
	return false;
}

static bool	checkDate(std::string date) {
	int			year, month, day;
	std::size_t	pos1, pos2;

	pos1 = date.find("-");
	pos2 = date.find("-", (pos1 + 1));
	year = atoi(date.substr(0, pos1).c_str());
	month = atoi(date.substr((pos1 + 1), (pos2 - 1)).c_str());
	day = atoi(date.substr(pos2 + 1).c_str());

	if ((year == 2009 && month == 1 && day < 2) || year < 2009) {
		std::cerr << "Error: the date is too old" << std::endl;
		return false;
	}
	if (month > 12 || day > 31) {
		std::cerr << "Error: bad date => " << date << std::endl;
		return false;
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
		std::cerr << "Error: bad date => " << date << std::endl;
		return false;
	}
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			if (day > 29) {
		std::cerr << "Error: bad date => " << date << std::endl;
				return false;
			}
		}
		else if (day > 28) {
		std::cerr << "Error: bad date => " << date << std::endl;
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

// -------------------- Data File --------------------
static bool checkFormatData(std::string line) {
	const char	*pattern = "^[0-9]{1,}-[0-9]{2}-[0-9]{2},[0-9]{1,}(\\.[0-9]{1,}){0,}$";

	if (!checkPattern(pattern, line)) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}
	return (true);
}

bool	BitcoinExchange::parsingDataFile(void) {
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
		if (checkFormatData(line)) {
			std::size_t pos = line.find(",");
			date = line.substr(0, pos);
			value = std::strtod(line.substr(pos + 1).c_str(), &endPtr);
			if (!checkDate(date))
				return (false);
			else
				_database[date] = value;
		}
		else {
			std::cerr << _RED << "Error: the line is in the wrong format => " << line << _END << std::endl;
			return (false);
		}
	}
	file.close();
	return (true);
}

// -------------------- Input File --------------------
static bool checkFormatInput(std::string line) {
	const char	*pattern = "^[0-9]{1,}-[0-9]{2}-[0-9]{2} \\| -?[0-9]{1,}(\\.[0-9]{1,}){0,}$";

	if (!checkPattern(pattern, line)) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}
	return (true);
}

void	BitcoinExchange::searchValue(char *input) {
	char			*endPtr;
	double			value;
	std::string		date;
	std::string		line;
	std::ifstream	inputFile;

	if (!parsingDataFile())
		return ;
	inputFile.open(input);
	if (!inputFile.is_open()) {
		std::cerr << _RED << "Error: could not open the file" << _END << std::endl;
		return ;
	}
	getline(inputFile, line);
	if (line != "date | value") {
		std::cerr << _RED << "Error: first line of data.csv must be \"date | value\"" << _END << std::endl;
		return ;
	}
	while (getline(inputFile, line)) {
		if (line.empty()) {
			std::cerr << _RED << "Error: empty line are not welcom" << _END << std::endl;
			return ;
		}
		if (checkFormatInput(line)) {
			std::size_t pos = line.find("|");
			date = line.substr(0, pos - 1);
			value = std::strtod(line.substr(pos + 2).c_str(), &endPtr);
			if (checkDate(date) && checkValue(value)) {
				std::map<std::string, double>::iterator	it = _database.find(date); 
				if (it == _database.end()) {
					it = _database.lower_bound(date);
					if (it != _database.begin())
						--it;
				}
				std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
			}
		}
	}
	return ;
}