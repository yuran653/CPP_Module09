/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:23 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/01 18:06:52 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<int, double>	BitcoinExchange::_data;
std::ifstream				BitcoinExchange::_is;
std::string					BitcoinExchange::_file_data;

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::openReadFile(std::string file_name) {
	_is.open("data.csv");
	if (_is.is_open() == false)
		throw OpenFileError("Can't open file: " + file_name);
	_is >> _file_data;
}

void BitcoinExchange::printData() {
	std::cout << _file_data << std::endl;
}