/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:11 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/17 17:47:31 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

 int main (int argc, char* argv[]) {
	if (argc < 3) {
		std::cerr << "Error: Wrong number of arguments" << std::endl;
		return 0;
	}
	PmergeMe::sortSequence(argv);
	return 0;
 }