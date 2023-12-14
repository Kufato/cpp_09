/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:23:54 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/14 16:56:41 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

std::stack<int> RPN::_stack;

// Public method
static bool charIsValid(char c) {
	return (std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == ' ');
}

static bool	checkArgCharacters(std::string arg) {
	for (size_t i = 0; i < (arg.length() - 1); i++) {
		if (!charIsValid(arg[i]))
			return (false);
	}
	return (true);
}

static bool	checkArgFormat(std::string arg) {
	size_t	i;

	for (i = 0; i < (arg.length() - 1); i++) {
		if (i % 2 == 0 && arg[i] == ' ')
			return (false);
		if (i % 2 != 0 && arg[i] != ' ')
			return (false);
	}
	if (arg[i] == ' ' || isdigit(arg[i]))
		return (false);
	return (true);
}

void	RPN::reversePolishNotation(std::string arg) {
	if (!checkArgCharacters(arg))
		throw RPN::ErrorExecption();
	if (!checkArgFormat(arg))
		throw RPN::ErrorExecption();
	for (size_t i = 0; i < arg.length(); i += 2) {
		if (isdigit(arg[i])) {
			_stack.push(std::atoi(&arg[i]));
		}
		else {
			if (_stack.size() < 2)
				throw RPN::ErrorExecption();
			int value2 = _stack.top();
			_stack.pop();
			int value1 = _stack.top();
			_stack.pop();
			if (arg[i] == '/' && value2 == 0)
				throw RPN::ErrorDivideByZeroExecption();
			switch (arg[i]) {
				case '+':
					_stack.push(value1 + value2);
					break ;
				case '-':
					_stack.push(value1 - value2);
					break ;
				case '*':
					_stack.push(value1 * value2);
					break ;
				case '/':
					_stack.push(value1 / value2);
					break ;
				default:
					std::cerr << "Error" << std::endl;
					return ;
			}
		}
	}
	std::cout << _stack.top()<< std::endl;
	_stack.pop();
	return ;
}

// Exceptions
const char	*RPN::ErrorExecption::what(void) const throw() {
	return ("Error");
}

const char	*RPN::ErrorDivideByZeroExecption::what(void) const throw() {
	return ("Error: divide by zero is forbidden");
}