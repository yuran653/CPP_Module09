/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:23 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/05 02:43:08 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<int, double>	BitcoinExchange::_data;

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

#define DATE_SIZE 10
#define NOT_DEFINED 0
#define BAD_INPUT -1
#define NOT_POSITIVE -2
#define TOO_LARGE -3
#define DATA_DIV ','
#define INPUT_DIV '|'

std::pair<int, double> BitcoinExchange::_parseBufferData(std::string buffer) {
	int key = NOT_DEFINED;
	double value = NOT_DEFINED;
	std::string key_str;
	std::string value_str;
	int i = 0;
	for (; i < DATE_SIZE; i++) {
		if (buffer.at(i) != '-')
			if (isdigit(buffer.at(i)))
				key_str.push_back(buffer.at(i));
	}
	std::istringstream(key_str) >> key;
	i++;
	int size = buffer.size();
	for (; i < size; i++)
		value_str.push_back(buffer.at(i));
	std::istringstream(value_str) >> value;
	return (std::make_pair(key, value));
}

void BitcoinExchange::_openReadInputFile(std::string file_name) {
	std::ifstream is(file_name);
	std::string buffer;
	if (is.is_open() == false)
		throw OpenFileError("Can't open file: " + file_name);
	while (is >> buffer)
		_data.insert(_parseBufferData(buffer));
	is.close();
}

void BitcoinExchange::printData() {
	_openReadInputFile("data.csv");
	for (std::multimap<int, double>::iterator it = _data.begin(); it != _data.end(); it++)
		std::cout << it->first << " | " << std::fixed << std::setprecision(2) << it->second <<std::endl;
}
