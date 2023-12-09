/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:23 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/09 11:32:58 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<int, long double>* BitcoinExchange::_data;
std::queue<std::pair<int, long double> >* BitcoinExchange::_input;

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

size_t BitcoinExchange::_calculatePrec(long double value) {
	std::ostringstream oss;
	oss << value;
	std::string str = oss.str();
	size_t pos = str.find(".");
	return (pos == std::string::npos ? 0 : str.size() - pos - 1);
}

std::string BitcoinExchange::_printDate(int key) {
	std::ostringstream oss;
	oss << key;
	std::string date = oss.str();
	date.insert(4, "-").insert(7, "-");
	return date;
}

void BitcoinExchange::_checkOverflow(std::pair<int, long double> values) {
	if (values.second < 0)
		throw BadInput("Not a positive number");
	else if (values.second > std::numeric_limits<int>::digits10)
		throw BadInput("Too large a number");
}

// void BitcoinExchange::_checkDate(std::pair<int, long double> values) {
// 	std::time_t current_time = std::time(NULL);
// 	std::tm* current_tm = std::localtime(&current_time);
// 	int current_date = (current_tm->tm_year + 1900) * 10000
// 		+ (current_tm->tm_mon + 1) * 100 + current_tm->tm_mday;
// 	int year = values.first / 10000;
// 	int month = (values.first - year * 10000) / 100;
// 	if (values.first < BTC_EXIST_DATE || values.first > current_date || month > 12)
// 		throw BadInput("Bad input => " + _printDate(values.first));
// 	int day = (values.first - year * 10000) % 100;
// 	if ((month == 1 || month == 3 || month == 5 || month == 7
// 		|| month == 8 || month == 10 || month == 12) && day > 31)
// 		throw BadInput("Bad input => " + _printDate(values.first));
// 	else if ((month == 2 || month == 4 || month == 6 || month == 9 || month == 11)
// 		&& day > 30)
// 		throw BadInput("Bad input => " + _printDate(values.first));
// 	else if (year % 4 != 0 && month == 2 && day > 28)
// 		throw BadInput("Bad input => " + _printDate(values.first));
// 	else if ((year % 4 == 0 && month == 2 && day > 29))
// 		throw BadInput("Bad input => " + _printDate(values.first));
// }

void BitcoinExchange::_checkDate(std::pair<int, long double> values) {
	std::time_t current_time = std::time(NULL);
	std::tm* current_tm = std::localtime(&current_time);
	int current_date = (current_tm->tm_year + 1900) * 10000
		+ (current_tm->tm_mon + 1) * 100 + current_tm->tm_mday;
	int year = values.first / 10000;
	int month = (values.first - year * 10000) / 100;
	int day = (values.first - year * 10000) % 100;
	if (values.first < BTC_EXIST_DATE || values.first > current_date
		|| month < 1 || month > 12 || day < 1)
		throw BadInput("Bad input => " + _printDate(values.first));
	bool leap_year = (year % 4 == 0);
	switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: {
			if (day > 31)
				throw BadInput("Bad input => " + _printDate(values.first));
				break;
		} case 4: case 6: case 9: case 11: {
			if (day > 30)
				throw BadInput("Bad input => " + _printDate(values.first));
				break;
		} case 2: {
			if (leap_year == true && day > 29) {
				throw BadInput("Bad input => " + _printDate(values.first));
				break;
			} else if (leap_year == false && day > 28) {
				throw BadInput("Bad input => " + _printDate(values.first));
				break;
			}
		}
	}
}

void BitcoinExchange::_findPrintRate(std::pair<int, long double> values) {
	try {
		_checkDate(values);
		_checkOverflow(values);
		std::cout << _printDate(values.first) << " => " << std::fixed
		<< std::setprecision(_calculatePrec(values.second)) << values.second
		<< " = "
		<< std::setprecision(_calculatePrec(values.second)) << values.second
		<< std::endl;
	} catch (const BadInput& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

std::pair<int, long double> BitcoinExchange::_parseBufferData(std::string buffer, std::string delim) {
	int key = BAD_INPUT;
	long double value = BAD_INPUT;
	std::string key_str;
	std::string value_str;
	int i = 0;
	for (; i < DATE_SIZE; i++) {
		if (buffer.at(i) != '-')
			if (isdigit(buffer.at(i)))
				key_str.push_back(buffer.at(i));
	}
	std::istringstream(key_str) >> key;
	if (delim.compare(DATA_DELIM) == 0)
		i++;
	else if (delim.compare(INPUT_DELIM) == 0)
		i += 3;
	int size = buffer.size();
	for (; i < size; i++)
		value_str.push_back(buffer.at(i));
	std::istringstream(value_str) >> value;
	return (std::make_pair(key, value));
}

void BitcoinExchange::_addPair(std::multimap<int, long double>* container, std::string buffer) {
	container->insert(_parseBufferData(buffer, DATA_DELIM));
}

void BitcoinExchange::_addPair(std::queue<std::pair<int, long double> >* container, std::string buffer) {
	container->push(_parseBufferData(buffer, INPUT_DELIM));
}

template <typename T>
void BitcoinExchange::_openReadFile (std::string file_name, std::string header, T* container) {
	std::ifstream is(file_name);
	std::string buffer;
	if (is.is_open() == false)
		throw OpenFileError("Can not open file: " + file_name);
	std::getline(is, buffer);
	if (buffer.compare(header))
		throw OpenFileError("Wrong header: " + file_name + ": [" + buffer + "]");
	while (std::getline(is, buffer))
		_addPair(container, buffer);
	is.close();
}

void BitcoinExchange::_initialize() {
	_data = new std::multimap<int, long double>;
	_input = new std::queue<std::pair<int, long double> >;
}
void BitcoinExchange::_cleanup() {
	delete _data;
	delete _input;
}

void BitcoinExchange::displayOutput(std::string input_file_name) {
	_initialize();
	try {
		_openReadFile(input_file_name, INPUT_HEAD,_input);
		_openReadFile(DATA_FILE, DATA_HEAD,_data);
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
