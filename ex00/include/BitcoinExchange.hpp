/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:52:03 by jgoldste          #+#    #+#             */
/*   Updated: 2023/11/30 19:47:00 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <fstream>
#include <map>
#include <string>

class BitcoinExchange {
	private:
		std::multimap<int, double>	_data;

		int	openReadFile(std::string file_name);

		BitcoinExchange();
		~BitcoinExchange();

	public:
		void	printData();

	class OpenFileError : public std::runtime_error {
		public:
			const char* what() const throw() {
				return "Can't open the file: ";
			}
	};
};

#endif
