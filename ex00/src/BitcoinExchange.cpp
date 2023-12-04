/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:23 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/04 19:43:35 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<int, double>	BitcoinExchange::_data;

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

std::pair<int, double> BitcoinExchange::_saveBufferData(std::string buffer) {
	int key = -1;
	double value = -1;
	for (std::string::iterator it; *it == ','; it++)
		if (*it == '-')
			buffer.erase(it);
	scanf("%d,%lf",)
	return (std::make_pair(key, value));
}

void BitcoinExchange::_openReadInputFile(std::string file_name) {
	std::ifstream is(file_name);
	std::string buffer;
	if (is.is_open() == false)
		throw OpenFileError("Can't open file: " + file_name);
	while (is >> buffer)
		_data.insert(_saveBufferData(buffer));
	is.close();
}

void BitcoinExchange::printData() {
	_openReadInputFile("data.csv");
}

	// 	for (std::string::iterator it = buffer.begin(); it != buffer.end(); it++) {
	// 		if (isdigit(*it) == 0)
	// 			std::cout << *it;
	// 	}
			
	// 	std::cout << std::endl;
	// }