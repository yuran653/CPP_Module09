/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:09 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/15 19:36:51 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#define SPACE_SIGN ' '

class PmergeMe {
	private:
		static std::vector<int>* _vectorSequence;
		static std::list<int>* _listSequence;

		PmergeMe();
		~PmergeMe();

		static void _initialize();
		static void _cleanup();
		static void _parseSequence(std::string sequence);

	public:

		static void sortSequence (std::string sequence);

		class PmergeError : public std::runtime_error {
			public:
				PmergeError(const std::string& message) : std::runtime_error(message) {}
		};
};
