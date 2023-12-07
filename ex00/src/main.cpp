/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:51:33 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/07 21:31:29 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main (int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Error: Wrong number of arguments" << std::endl;
		return 0;
	}
	BitcoinExchange::displayOutput(argv[1]);
	return 0;
}
