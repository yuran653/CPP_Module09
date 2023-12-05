/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:52:03 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/05 15:51:55 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <utility>

#define DATE_SIZE 10
#define BAD_INPUT -1
#define NOT_POSITIVE -2
#define TOO_LARGE -3
#define DATA_DELIM ','
#define INPUT_DELIM '|'
#define DATA_HEAD "date,exchange_rate"
#define INPUT_HEAD "date | value"

class BitcoinExchange {
	private:
		static std::multimap<int, long double>* _data;
		static std::multimap<int, long double>* _input;

		static void _initialize();
		static void _cleanup();
		static void _openReadFile
			(std::string file_name, std::multimap<int, long double>* container, char delim);
		static std::pair<int, long double> _parseBufferData(std::string buffer, char delim);

		BitcoinExchange();
		~BitcoinExchange();

	public:
		static void	printData();

	class OpenFileError : public std::runtime_error {
		public:
			OpenFileError(const std::string& message) : std::runtime_error(message) {}
	};
};

#endif
