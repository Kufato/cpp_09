/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:23 by axcallet          #+#    #+#             */
/*   Updated: 2023/12/12 15:53:01 by axcallet         ###   ########.fr       */
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

#include <vector>
#include <cstdlib>
#include <utility>
#include <iostream>

class	PmergeMe {
	
	private:
		PmergeMe(void);
		PmergeMe(const PmergeMe &toCopy);
		~PmergeMe(void);
		PmergeMe &operator=(const PmergeMe &toCopy);

	public:
	// Public method
		// static void	algorithmList(int argc, char **argv);
		static std::vector<int>	algorithmVector(std::vector<int> X);

	// Execptions
		class	NegativeNumberException : public std::exception {
			public:
				virtual const char	*what(void) const throw();
		};
};