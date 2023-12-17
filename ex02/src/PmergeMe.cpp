/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:14 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/18 00:18:37 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::vector<int>* PmergeMe::_vectorSequence;
std::list<int>* PmergeMe::_listSequence;

PmergeMe::PmergeMe() {
}

PmergeMe::~PmergeMe() {
}

template <typename T>
void PmergeMe::_merge(T& leftContainer, T& rightContainer, T& container) {
	delete container;
	container = new T;
	typename T::iterator it_left = leftContainer.begin();
	typename T::iterator it_right = rightContainer.begin();
	while (it_left != leftContainer.end() && it_right != rightContainer.end()) {
		if (*it_left < *it_right) {
			container.push_back(*it_left);
			it_left++;
		} else {
			container.push_back(*it_right);
			it_right++;
		}
	}
	while (it_left != leftContainer.end()) {
		container.push_back(*it_left);
		it_left++;
	}
	while (it_right != rightContainer.end()) {
		container.push_back(*it_right);
		it_right++;
	}
}

template <typename T>
void PmergeMe::_mergeSort(T& container) {
	if (container.size() <= 1)
		return ;
	T* leftContainer = new T;
	T* rightContainer = new T;
	size_t i = 0;
	size_t half = container.size() / 2;

	for (typename T::iterator it = container.begin(); it != container.end(); it++) {
		if (i < half)
			leftContainer->push_back(*it);
		else
			rightContainer->push_back(*it);
	}
	_mergeSort(leftContainer);
	_mergeSort(rightContainer);
	_merge(leftContainer, rightContainer, container);
	delete leftContainer;
	delete rightContainer;
}

template <typename T>
bool PmergeMe::_isSorted(T& container) {
	typename T::iterator it = container.begin();
	typename T::iterator next = container.begin();
	next++;
	if (next == container.end())
		throw PmergeError("The container is empty");
	while (next != container.end()) {
		if (*it > *next) {
			return false;
		} else {
			it++;
			next++;
		}
	}
	return true;
}

template <typename T>
bool PmergeMe::_isDuplicate(T& container) {
	for (typename T::iterator it = container.begin(); it != container.end(); it++) {
		typename T::iterator it_dup = it;
		while (++it_dup != container.end())
			if (*it == *it_dup)
				return true;
	}
	return false;
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
	if (_vectorSequence->size() != _listSequence->size())
		throw PmergeError("The sequence saved incorrectly");
	if (_isDuplicate(_vectorSequence) || _isDuplicate(_listSequence))
		throw PmergeError("The sequence contains duplicate numbers");
	if (_isSorted(_vectorSequence) || _isSorted(_listSequence))
		throw PmergeError("The sequense is sorted");
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
		_mergeSort(*_vectorSequence);
		for (std::vector<int>::iterator it = _vectorSequence->begin(); it != _vectorSequence->end(); it++)
			std::cout << "Vector -> " << *it << std::endl;
		for (std::list<int>::iterator it = _listSequence->begin(); it != _listSequence->end(); it++)
			std::cout << "List -> " << *it << std::endl;
	} catch (const PmergeError& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	_cleanup();
}
