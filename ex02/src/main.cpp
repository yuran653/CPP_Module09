/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:11 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/19 16:58:29 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

 int main (int argc, char* argv[]) {
	if (argc < 3) {
		std::cerr << "Error: Wrong number of arguments" << std::endl;
		return 0;
	}
	PmergeMe::sortSequence((const char**)argv);
	return 0;
 }

 // ./PmergeMe `shuf -i 1-3000 -n 30000 | tr '\n' ' '`
 // ./PmergeMe `jot -r 3000 1 30000 | tr '\n' ' '`
