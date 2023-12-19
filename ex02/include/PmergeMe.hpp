/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:09 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/19 16:56:17 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <ctime>
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
		static void _parseSequence(const char* sequence[]);
		static void _printSequence();
		template <typename T>
		static bool _isSorted(T*& container);
		template <typename T>
		static bool _isDuplicate(T*& container);
		template <typename T>
		static void _mergeSort(T*& container);
		template <typename T>
		static void _merge(T*& leftContainer, T*& rightContainer, T*& container);

		struct _myIsDigit {
			bool operator()(char c) const {
				return (std::isdigit(static_cast<unsigned char>(c)) == 0);
			}
		};

		struct _PmergeError : public std::runtime_error {
			_PmergeError(const std::string& message) : std::runtime_error(message) {}
		};

	public:
		static void sortSequence (const char* sequence[]);
};
