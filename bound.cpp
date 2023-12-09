/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bound.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/09 17:24:22 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <string>

int main() {
	std::multimap<int, std::string> m;

	m.insert(std::make_pair(10, "ten")); 
	m.insert(std::make_pair(20, "twenty"));
	m.insert(std::make_pair(30, "thirty")); 
	m.insert(std::make_pair(30, "thirty again"));
	m.insert(std::make_pair(40, "forty"));
	m.insert(std::make_pair(50, "fifty")); 
	m.insert(std::make_pair(60, "sixty"));
	m.insert(std::make_pair(70, "seventy"));

	int search_key = 5; 

	std::multimap<int, std::string>::iterator lower, upper;

	lower = m.lower_bound(search_key);
	// upper = m.upper_bound(search_key);

	if (lower == m.begin() && lower->first == search_key) {
		std::cout << "Lower: " << lower->first << " -> " << lower->second << std::endl;
		return 0;
	} else {
		std::cout << "No matching value" << std::endl;
		return 0;
	}

	lower--;

	std::cout << "Lower: " << lower->first << " -> " << lower->second << std::endl;
	// std::cout << "Upper: " << upper->first << " -> " << upper->second << std::endl;

	return 0;
}