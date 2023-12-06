/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:23 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/06 19:39:26 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<int, long double>* BitcoinExchange::_data;
std::queue<std::pair<int, long double> >* BitcoinExchange::_input;

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::_initialize() {
	_data = new std::multimap<int, long double>;
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

int BitcoinExchange::_calculatePrec(long double value) {
	long double decimal_part = fabs(value - static_cast<int>(value));
	int precision = 0;
	for (; decimal_part && precision < std::numeric_limits<long double>::digits10; precision++) {
		decimal_part *= 10;
		decimal_part = decimal_part - static_cast<int>(decimal_part);
	}
	return precision;
}

std::string BitcoinExchange::_printDate(int key) {
	std::ostringstream oss;
	oss << key;
	std::string date = oss.str();
	date.insert(4, "-");
	date.insert(7, "-");
	return date;
}

void BitcoinExchange::_findPrintRate(std::pair<int, long double> values) {
	if (values.first > 0) {
		std::cout << _printDate(values.first) << " => " << std::fixed
			<< std::setprecision(_calculatePrec(values.second)) << values.second << " = "
			<< std::setprecision(_calculatePrec(values.second)) << values.second << std::endl;
	}
}

void BitcoinExchange::displayOutput(std::string input_file_name) {
	_initialize();
	try {
		_openReadFile(input_file_name, _input, INPUT_DELIM);
		_openReadFile(DATA_FILE, _data, DATA_DELIM);
		std::cout << INPUT_HEAD << std::endl;
		for (int size = _input->size(); size; size--) {
			_findPrintRate(_input->front());
			_input->pop();
		}
	} catch (const OpenFileError& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	_cleanup();
}
