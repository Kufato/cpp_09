/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:41:48 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/19 11:44:41 by axcallet         ###   ########.fr       */
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
// -------------------- Check Date/Value --------------------
static bool	checkDate(std::string date) {
	struct tm	tm;

	strptime(date.c_str(), "%Y-%m-%d", &tm);
	if ((tm.tm_year == 2009 && tm.tm_mon == 1 && tm.tm_mday < 2) || tm.tm_year < 2009) {
		std::cerr << "Error: the date is too old" << std::endl;
		return false;
	}
	if (tm.tm_mon > 12 || tm.tm_mday > 31) {
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}
	if ((tm.tm_mon == 4 || tm.tm_mon == 6 || tm.tm_mon == 9 || tm.tm_mon == 11) && tm.tm_mday > 30) {
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}
	if (tm.tm_mon == 2) {
		if ((tm.tm_year % 4 == 0 && tm.tm_year % 100 != 0) || (tm.tm_year % 400 == 0)) {
			if (tm.tm_mday > 29) {
		std::cerr << "Error: bad input => " << date << std::endl;
				return false;
			}
		}
		else if (tm.tm_mday > 28) {
		std::cerr << "Error: bad input => " << date << std::endl;
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
	int					year, month, day;
	char				dash1, dash2, comma;
	double				value;
	std::istringstream	checkLine(line);

	if (!(checkLine >> year >> dash1 >> month >> dash2 >> day >> comma >> value)) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}
	if (dash1 != '-' || dash2 != '-' || comma != ',') {
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
			date = line.substr(0, (pos - 1));
			value = std::strtod(line.substr(pos + 1).c_str(), &endPtr);
			std::cout << _GREEN << "data: date = " << date << " and value = " << value << _END << std::endl;
			if (!checkDate(date) || !checkValue(value))
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
	int					year, month, day;
	char				dash1, dash2, space1, space2, pipe;
	double				value;
	std::istringstream	checkLine(line);

	if (!(checkLine >> year >> dash1 >> month >> dash2 >> day >> space1 >> pipe >> space2 >> value)) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}
	if (dash1 != '-' || dash2 != '-' || space1 != ' ' || space2 != ' ' || pipe != ' ') {
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
			date = line.substr(0, pos - 2);
			value = std::strtod(line.substr(pos + 2).c_str(), &endPtr);
			std::cout << _GREEN << "input: date = " << date << " and value = " << value << _END << std::endl;
			if (!checkDate(date) || !checkValue(value))
				return ;
			else {
				std::map<std::string, double>::iterator	it = _database.find(date); 
				if (it == _database.end()) {
					it = _database.lower_bound(date);
					if (it != _database.begin())
						--it;
					std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
				}
			}
		}
	}
	return ;
}