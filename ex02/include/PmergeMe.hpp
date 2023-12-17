/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:09 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/18 00:08:55 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <exception>
#include <iostream>
#include <list>
#include <limits>
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
		static void _parseSequence(char* sequence[]);
		template <typename T>
		static bool _isSorted(T& container);
		template <typename T>
		static bool _isDuplicate(T& container);
		template <typename T>
		static void _mergeSort(T& container);
		template <typename T>
		static void _merge(T& leftContainer, T& rightContainer, T& container);

	public:

		static void sortSequence (char* sequence[]);

		class myIsDigit {
			public:
				bool operator()(char c) const {
					return (std::isdigit(static_cast<unsigned char>(c)) == 0);
				}
		};

		class PmergeError : public std::runtime_error {
			public:
				PmergeError(const std::string& message) : std::runtime_error(message) {}
		};
};
