/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:23 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/04 13:21:09 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<int, double>	BitcoinExchange::_data;

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::openReadFile(std::string file_name) {
	std::ifstream is(file_name);
	std::string buffer;
	if (is.is_open() == false)
		throw OpenFileError("Can't open file: " + file_name);
	while (is >> buffer)
		std::cout << buffer << std::endl;
	is.close();
}

void BitcoinExchange::printData() {
	openReadFile("data.csv");
}