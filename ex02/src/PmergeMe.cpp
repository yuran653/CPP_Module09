/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:14 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/15 19:36:26 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
}

PmergeMe::~PmergeMe() {
}

void PmergeMe::_parseSequence(std::string sequence) {
	std::stringstram ss;

}

void PmergeMe::_initialize() {
	_vectorSequence = new std::vector<int>;
	_listSequence = new std::list<int>;
}

void PmergeMe::_cleanup() {
	delete _vectorSequence;
	delete _listSequence;
}

void PmergeMe::sortSequence (std::string sequence) {
	_initialize();
	try {
		_parseSequence(sequence);
		std::cout << sequence << std::endl;
	} catch (const PmergeError& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	_cleanup();
}
