/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:52:03 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/07 22:44:48 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <ctime>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <cmath>
#include <queue>
#include <sstream>
#include <string>
#include <utility>

#define DATE_SIZE 10
#define DATA_DELIM ','
#define INPUT_DELIM '|'
#define BTC_EXIST_DATE 20090102
#define DATA_HEAD "date,exchange_rate"
#define INPUT_HEAD "date | value"
#define DATA_FILE "data.csv"

class BitcoinExchange {
	private:
		static std::multimap<int, long double>* _data;
		static std::queue<std::pair<int, long double> >* _input;

		static void _initialize();
		static void _cleanup();
		template <typename T>
		static void _openReadFile (std::string file_name, T* container, char delim);
		static void _addPair(std::multimap<int, long double>* container, std::string buffer, char delim);
		static void _addPair(std::queue<std::pair<int, long double> >* container, std::string buffer, char delim);
		static std::pair<int, long double> _parseBufferData(std::string buffer, char delim);
		static void _deleteHead(std::multimap<int, long double>* container);
		static void _deleteHead(std::queue<std::pair<int, long double> >* container);
		static void _findPrintRate(std::pair<int, long double> values);
		static void _checkDate(int date);
		static void _checkOverflow(long double value);
		static std::string _printDate(int key);
		static size_t _calculatePrec(long double value);

		BitcoinExchange();
		~BitcoinExchange();

	public:
		static void	displayOutput(std::string input_file_name);

	class OpenFileError : public std::runtime_error {
		public:
			OpenFileError(const std::string& message) : std::runtime_error(message) {}
	};

	class BadInput : public std::runtime_error {
		public:
			BadInput(const std::string& message) : std::runtime_error(message) {}
	};
};

#endif
