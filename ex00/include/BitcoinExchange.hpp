/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:52:03 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/19 16:40:54 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <ctime>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <utility>

#define DATE_SIZE 10
#define DATA_DELIM ","
#define INPUT_DELIM " | "
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
		static void _openReadFile (const std::string& file_name, const std::string& header, T*& container);
		static void _checkLineFormat(const std::string& buffer);
		static void _checkNumberFormat(const std::string& buffer, size_t& i);
		static void _isDigitLoop(const std::string& buffer, size_t& i);
		static void _addPair(std::multimap<int, long double>*& container, const std::string& buffer);
		static void _addPair(std::queue<std::pair<int, long double> >*& container, const std::string& buffer);
		static std::pair<int, long double> _parseBufferData(const std::string& buffer, std::string delim);
		static void _findPrintRate(const std::pair<int, long double>& values);
		static void _checkDate(const std::pair<int, long double>& values);
		static void _checkOverflow(const std::pair<int, long double>& values);
		static std::string _printDate(const int& key);
		static size_t _calculatePrec(const long double& value);
		static std::pair<int, long double> _findValueByKey(const int& key);

		BitcoinExchange();
		~BitcoinExchange();

	public:
		static void	displayOutput(const char* argv);

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
