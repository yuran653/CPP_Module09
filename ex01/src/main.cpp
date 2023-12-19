/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:32 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/19 16:53:53 by jgoldste         ###   ########.fr       */
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

// ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
// ./RPN "7 7 * 7 -"
// ./RPN "1 2 * 2 / 2 * 2 4 - +"
// ./RPN "(1 + 1)"
