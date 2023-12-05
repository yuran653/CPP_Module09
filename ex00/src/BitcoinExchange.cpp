/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:23 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/05 15:53:46 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<int, long double>*	BitcoinExchange::_data;
std::multimap<int, long double>*	BitcoinExchange::_input;

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::_initialize() {
	_data = new std::multimap<int, long double>;
	_input = new std::multimap<int, long double>;
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

void BitcoinExchange::_openReadFile
	(std::string file_name, std::multimap<int, long double>* container, char delim) {
	std::ifstream is(file_name);
	std::string buffer;
	if (is.is_open() == false)
		throw OpenFileError("Can't open file: " + file_name);
	while (std::getline(is, buffer)) {
		container->insert(_parseBufferData(buffer, delim));
	}
	is.close();
}

void BitcoinExchange::printData() {
	_initialize();
	_openReadFile("data.csv", _data, DATA_DELIM);
	for (std::multimap<int, long double>::iterator it = _data->begin(); it != _data->end(); it++)
		std::cout << it->first << " | " << std::fixed << std::setprecision(2) << it->second <<std::endl;
	_openReadFile("input.txt", _input, INPUT_DELIM);
	for (std::multimap<int, long double>::iterator it = _input->begin(); it != _input->end(); it++)
		std::cout << it->first << " | " << std::fixed << std::setprecision(2) << it->second <<std::endl;
	_cleanup();
}
