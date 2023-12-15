/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:11 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/15 15:56:48 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

 int main (int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Wrong number of arguments" << std::endl;
		return 0;
	}
	PmergeMe::sortSequence(argv[1]);
	return 0;
 }