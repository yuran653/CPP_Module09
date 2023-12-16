/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:14 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/16 15:52:56 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::vector<int>* PmergeMe::_vectorSequence;
std::list<int>* PmergeMe::_listSequence;

PmergeMe::PmergeMe() {
}

PmergeMe::~PmergeMe() {
}

void PmergeMe::_parseSequence(char* sequence[]) {
	for (int i = 1; sequence[i]; i++) {
		std::string str(sequence[i]);
		if (std::find_if(str.begin(), str.end(), myIsDigit()) != str.end())
			throw PmergeError("The sequence contains non-digit characters");
		long long num;
		std::istringstream(str) >> num;
		if (num < 0 || num > INT_MAX)
			throw PmergeError("The sequence contains too large or negative number");
		_vectorSequence->push_back(num);
		_listSequence->push_back(num);
	}
}

void PmergeMe::_initialize() {
	_vectorSequence = new std::vector<int>;
	_listSequence = new std::list<int>;
}

void PmergeMe::_cleanup() {
	delete _vectorSequence;
	delete _listSequence;
}

void PmergeMe::sortSequence (char* sequence[]) {
	_initialize();
	try {
		_parseSequence(sequence);
		for (std::vector<int>::iterator it = _vectorSequence->begin(); it != _vectorSequence->end(); it++)
			std::cout << "Vector -> " << *it << std::endl;
		for (std::list<int>::iterator it = _listSequence->begin(); it != _listSequence->end(); it++)
			std::cout << "LIst -> " << *it << std::endl;
	} catch (const PmergeError& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	_cleanup();
}
