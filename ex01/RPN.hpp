/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:23:59 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/12 15:53:23 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define _END		"\033[0m"
#define _BLACK		"\033[0;30m"
#define _RED		"\033[0;31m"
#define _GREEN		"\033[0;32m"
#define _YELLOW		"\033[0;33m"
#define _BLUE		"\033[0;34m"
#define _PURPLE		"\033[0;35m"
#define _CYAN		"\033[0;36m"

#include <stack>
#include <cctype>
#include <regex.h>
#include <cstdlib>
#include <iostream>

class	RPN {
	
	private:
		static std::stack<int>	_stack;
		RPN(void);
		RPN(const RPN &toCopy);
		~RPN(void);
		RPN &operator=(const RPN &toCopy);

	public:
	// Public method
		static void	reversePolishNotation(std::string arg);

	// Execptions
		class	ErrorExecption : public std::exception {
			public:
				virtual const char	*what(void) const throw();
		};
		class	ErrorDivideByZeroExecption : public std::exception {
			public:
				virtual const char	*what(void) const throw();
		};
};
