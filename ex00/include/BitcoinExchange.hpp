/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:52:03 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/04 19:28:19 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

class BitcoinExchange {
	private:
		static std::multimap<int, double> _data;
		
		static void _openReadInputFile(std::string file_name);
		static std::pair<int, double> _saveBufferData(std::string buffer);

		BitcoinExchange();
		~BitcoinExchange();

	public:
		static void	printData();

	class OpenFileError : public std::runtime_error {
		public:
			OpenFileError(const std::string& message) : std::runtime_error(message) {}
	};
	class WrongInputFormat : public std::runtime_error {
		public:
			WrongInputFormat(const std::string& message) : std::runtime_error(message) {}
	};
};

#endif
