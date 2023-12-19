/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:23 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/19 19:35:40 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<int, long double>* BitcoinExchange::_data;
std::queue<std::pair<int, long double> >* BitcoinExchange::_input;

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

std::pair<int, long double> BitcoinExchange::_findValueByKey(const int& key) {
	std::multimap<int, long double>::iterator values_found = _data->lower_bound(key);
	if (values_found == _data->begin()) {
		if (values_found->first == key)
			return *values_found;
		else
			throw BadInput("No matching date");
	}
	if (values_found->first != key)
		values_found--;
	return *values_found;	
}

size_t BitcoinExchange::_calculatePrec(const long double& value) {
	std::ostringstream oss;
	oss << value;
	std::string str = oss.str();
	size_t pos = str.find(".");
	return (pos == std::string::npos ? 0 : str.size() - pos - 1);
}

std::string BitcoinExchange::_printDate(const int& key) {
	std::ostringstream oss;
	oss << key;
	std::string date = oss.str();
	date.insert(4, "-").insert(7, "-");
	return date;
}

void BitcoinExchange::_checkOverflow(const std::pair<int, long double>& values) {
	if (values.second < 0)
		throw BadInput("Not a positive number");
	else if (values.second > std::numeric_limits<int>::max())
		throw BadInput("Too large a number");
}

void BitcoinExchange::_checkDate(const std::pair<int, long double>& values) {
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

void BitcoinExchange::_findPrintRate(const std::pair<int, long double>& values) {
	try {
		_checkDate(values);
		_checkOverflow(values);
		std::pair<int, long double> values_found = _findValueByKey(values.first);
		std::cout << _printDate(values_found.first) << " => " << std::fixed
		<< std::setprecision(_calculatePrec(values.second)) << values.second
		<< " = ";
		long double result = values_found.second * values.second;
		std::cout << std::fixed << std::setprecision(_calculatePrec(result)) << result << std::endl;
	} catch (const BadInput& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

std::pair<int, long double> BitcoinExchange::_parseBufferData(const std::string& buffer, std::string delim) {
	int key = -1;
	long double value = -1;
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

void BitcoinExchange::_addPair(std::multimap<int, long double>*& container, const std::string& buffer) {
	container->insert(_parseBufferData(buffer, DATA_DELIM));
}

void BitcoinExchange::_addPair(std::queue<std::pair<int, long double> >*& container, const std::string& buffer) {
	container->push(_parseBufferData(buffer, INPUT_DELIM));
}

void BitcoinExchange::_isDigitLoop(const std::string& buffer, size_t& i) {
	while (buffer[i] && isdigit(buffer[i]))
		i++;
}

void BitcoinExchange::_checkNumberFormat(const std::string& buffer, size_t& i) {
	if (buffer[i] == '-')
		i++;
	_isDigitLoop(buffer, i);
	if (buffer[i] == '.')
		i++;
	_isDigitLoop(buffer, i);
	if (buffer[i])
		throw OpenFileError("Bad input => " + buffer);
}

void BitcoinExchange::_checkLineFormat(const std::string& buffer) {
	size_t size = buffer.size();
	if (size < DATE_SIZE)
		throw OpenFileError("Bad input => " + buffer);
	for (size_t i = 0; i < size; i++) {
		if (i == 4 || i == 7) {
			if (buffer[i] != '-')
				throw OpenFileError("Bad input => " + buffer);
		} else if (i < DATE_SIZE) {
			if (isdigit(buffer[i]) == 0)
				throw OpenFileError("Bad input => " + buffer);
		} else {
			if (buffer[i] == ',') {
				i++;
				_checkNumberFormat(buffer, i);
			} else {
				if (size < DATE_SIZE + 3)
					throw OpenFileError("Bad input => " + buffer);
				if (buffer[i] != ' ' && buffer[i + 1] != '|' && buffer[i + 2] != ' ')
					throw OpenFileError("Bad input => " + buffer);
				i += 3;
				_checkNumberFormat(buffer, i);
			}
		}
	}
}

template <typename T>
void BitcoinExchange::_openReadFile(const std::string& file_name, const std::string& header, T*& container) {
	std::ifstream is(file_name);
	std::string buffer;
	if (is.is_open() == false)
		throw OpenFileError("Can not open file: " + file_name);
	std::getline(is, buffer);
	if (buffer.compare(header))
		throw OpenFileError("Wrong header: " + file_name + ": [" + buffer + "]");
	while (std::getline(is, buffer)) {
		_checkLineFormat(buffer);
		_addPair(container, buffer);
	}
	is.close();
	if (container->empty())
		throw OpenFileError("The file is empty: " + file_name);
}

void BitcoinExchange::_initialize() {
	_data = new std::multimap<int, long double>;
	_input = new std::queue<std::pair<int, long double> >;
}
void BitcoinExchange::_cleanup() {
	delete _data;
	delete _input;
}

	void BitcoinExchange::displayOutput(const char* argv) {
	const std::string input_file_name(argv);
	_initialize();
	try {
		_openReadFile(input_file_name, INPUT_HEAD, _input);
		_openReadFile(DATA_FILE, DATA_HEAD, _data);
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
