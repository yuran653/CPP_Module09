/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:52:03 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/01 18:05:51 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
	private:
		static std::multimap<int, double>	_data;
		static std::ifstream				_is;
		static std::string					_file_data;

		static void	openReadFile(std::string file_name);

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
