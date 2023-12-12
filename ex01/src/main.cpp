/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:32 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/12 15:55:17 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Error: Wrong number of arguments" << std::endl;
		return 0;
	}
	RPN::calculateRPN(argv[1]);
	return 0;
}
