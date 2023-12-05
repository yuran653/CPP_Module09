/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:23 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/05 22:15:11 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<int, long double>*	BitcoinExchange::_data;
// std::multimap<int, long double>*	BitcoinExchange::_input;
std::queue<std::pair<int, long double> >* BitcoinExchange::_input;

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::_initialize() {
	_data = new std::multimap<int, long double>;
	// _input = new std::multimap<int, long double>;
	_input = new std::queue<std::pair<int, long double> >;
}
void BitcoinExchange::_cleanup() {
	delete _data;
	delete _input;
}

std::pair<int, long double> BitcoinExchange::_parseBufferData(std::string buffer, char delim) {
	int key = BAD_INPUT;
	long double value = BAD_INPUT;
	if (buffer.compare(DATA_HEAD) || buffer.compare(INPUT_HEAD)) {
		std::string key_str;
		std::string value_str;
		int i = 0;
		for (; i < DATE_SIZE; i++) {
			if (buffer.at(i) != '-')
				if (isdigit(buffer.at(i)))
					key_str.push_back(buffer.at(i));
		}
		std::istringstream(key_str) >> key;
		if (delim == DATA_DELIM)
			i++;
		else if (delim == INPUT_DELIM)
			i += 3;
		int size = buffer.size();
		for (; i < size; i++)
			value_str.push_back(buffer.at(i));
		std::istringstream(value_str) >> value;
	}
	return (std::make_pair(key, value));
}

// void BitcoinExchange::_openReadFile
// 	(std::string file_name, std::multimap<int, long double>* container, char delim) {
// 	std::ifstream is(file_name);
// 	std::string buffer;
// 	if (is.is_open() == false)
// 		throw OpenFileError("Can't open file: " + file_name);
// 	while (std::getline(is, buffer)) {
// 		container->insert(_parseBufferData(buffer, delim));
// 	}
// 	is.close();
// 	container->erase(container->begin());
// }

void BitcoinExchange::_addPair(std::multimap<int, long double>* container, std::string buffer, char delim) {
	container->insert(_parseBufferData(buffer, delim));
}

void BitcoinExchange::_addPair(std::queue<std::pair<int, long double> >* container, std::string buffer, char delim) {
	container->push(_parseBufferData(buffer, delim));
}

void BitcoinExchange::_deleteHead(std::multimap<int, long double>* container) {
	container->erase(container->begin());
}

void BitcoinExchange::_deleteHead(std::queue<std::pair<int, long double> >* container) {
	container->pop();
}

template <typename T>
void BitcoinExchange::_openReadFile (std::string file_name, T* container, char delim) {
	std::ifstream is(file_name);
	std::string buffer;
	if (is.is_open() == false)
		throw OpenFileError("Can't open file: " + file_name);
	while (std::getline(is, buffer)) {
		_addPair(container, buffer, delim);
	}
	is.close();
	_deleteHead(container);
}

// std::pair<int, long double> BitcoinExchange::_findRate(int key) {
// 	for (std::multimap<int, long double>::iterator it = _data->begin(); it != _data->end(); it++) {

// 	}
// }

#include <cmath>
std::string BitcoinExchange::_printDate(int key) {
	std::ostringstream oss;
	oss << key;
	std::string date = oss.str();
	date.insert(4, "-");
	date.insert(7, "-");
	return date;
}

void BitcoinExchange::printData() {
	_initialize();
	try {
		_openReadFile(INPUT_FILE, _input, INPUT_DELIM);
		_openReadFile(DATA_FILE, _data, DATA_DELIM);
	} catch (const OpenFileError& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	while (_input->size()) {
		std::cout << _printDate(_input->front().first) << std::endl;
		_input->pop();
	}
	// while (_input->size()) {
	// 	std::cout << _input->front().first << " | " << _input->front().second << std::endl;
	// 	_input->pop();
	// }
	// for (std::multimap<int, long double>::iterator it = _input->begin(); it != _input->end(); it++) {
	// 	std::cout << _printDate(it->first) << std::endl;
	// }
	_cleanup();
}
