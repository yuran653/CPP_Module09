/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:14 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/19 01:31:45 by jgoldste         ###   ########.fr       */
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
void PmergeMe::_merge(T*& leftContainer, T*& rightContainer, T*& container) {
	typename T::iterator it_left = leftContainer->begin();
	typename T::iterator it_right = rightContainer->begin();
	while (it_left != leftContainer->end() && it_right != rightContainer->end()) {
		if (*it_left < *it_right) {
			container->push_back(*it_left);
			it_left++;
		} else {
			container->push_back(*it_right);
			it_right++;
		}
	}
	while (it_left != leftContainer->end()) {
		container->push_back(*it_left);
		it_left++;
	}
	while (it_right != rightContainer->end()) {
		container->push_back(*it_right);
		it_right++;
	}
}

template <typename T>
void PmergeMe::_mergeSort(T*& container) {
	if (container->size() < 2)
		return ;
	T* leftContainer = new T;;
	T* rightContainer = new T;
	size_t i = 0;
	size_t half = container->size() / 2;
	for (typename T::iterator it = container->begin(); it != container->end(); it++) {
		if (i < half) {
			leftContainer->push_back(*it);
		} else {
			rightContainer->push_back(*it);
		}
		i++;
	}
	_mergeSort(leftContainer);
	_mergeSort(rightContainer);
	delete container;
	container = new T;
	_merge(leftContainer, rightContainer, container);
	delete leftContainer;
	delete rightContainer;
}

template <typename T>
bool PmergeMe::_isDuplicate(T*& container) {
	for (typename T::iterator it = container->begin(); it != container->end(); it++) {
		typename T::iterator it_dup = it;
		while (++it_dup != container->end())
			if (*it == *it_dup)
				return true;
	}
	return false;
}

template <typename T>
bool PmergeMe::_isSorted(T*& container) {
	typename T::iterator it = container->begin();
	typename T::iterator next = container->begin();
	next++;
	if (next == container->end())
		throw _PmergeError("The container is empty");
	while (next != container->end()) {
		if (*it > *next) {
			return false;
		} else {
			it++;
			next++;
		}
	}
	return true;
}

void PmergeMe::_parseSequence(char* sequence[]) {
	for (int i = 1; sequence[i]; i++) {
		const std::string str(sequence[i]);
		if (std::find_if(str.begin(), str.end(), _myIsDigit()) != str.end())
			throw _PmergeError("The sequence contains non-digit characters");
		long long num;
		std::istringstream(str) >> num;
		if (num < 0 || num > INT_MAX)
			throw _PmergeError("The sequence contains too large or negative number");
		_vectorSequence->push_back(num);
		_listSequence->push_back(num);
	}
	if (_vectorSequence->size() != _listSequence->size())
		throw _PmergeError("The sequence saved incorrectly");
	if (_isSorted(_vectorSequence) || _isSorted(_listSequence))
		throw _PmergeError("The sequense is sorted");
	if (_isDuplicate(_vectorSequence) || _isDuplicate(_listSequence))
		throw _PmergeError("The sequence contains duplicate numbers");
}

void PmergeMe::_printSequence() {
	std::vector<int>::iterator it_vector = _vectorSequence->begin();
	std::list<int>::iterator it_list = _listSequence->begin();
	while (it_vector != _vectorSequence->end() || it_list != _listSequence->end()) {
		if (*it_vector != *it_list)
			throw _PmergeError("The sequences not equal");
		std::cout << *it_vector;
		it_vector++;
		it_list++;
		if (it_vector != _vectorSequence->end() || it_list != _listSequence->end())
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::_cleanup() {
	delete _vectorSequence;
	delete _listSequence;
}

void PmergeMe::_initialize() {
	_vectorSequence = new std::vector<int>;
	_listSequence = new std::list<int>;
}

void PmergeMe::sortSequence (char* sequence[]) {
	_initialize();
	std::clock_t start_time;
	std::clock_t end_time;
	try {
		_parseSequence(sequence);
		std::cout << "Before: ";
		_printSequence();
		start_time = std::clock();
		_mergeSort(_vectorSequence);
		end_time = std::clock();
		double vectorSortTime = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000000.0;
		start_time = std::clock();
		_mergeSort(_listSequence);
		end_time = std::clock();
		double listSortTime = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000000.0;
		if (_isSorted(_vectorSequence) == false || _isSorted(_listSequence) == false)
			throw _PmergeError("The sequenses were sorted incorrectly");
		std::cout << "After: ";
		_printSequence();
		std::cout << "Time to process a range of " << _vectorSequence->size()
			<< " elements with std::vector : " << vectorSortTime << " us" << std::endl;
		std::cout << "Time to process a range of " << _listSequence->size()
			<< " elements with std::list   : " << listSortTime << " us" << std::endl;
	} catch (const _PmergeError& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	_cleanup();
}
