/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:35 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/12 21:49:27 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// std::queue<char>* _rpn_queue;
// std::stack<char>* _rpn_input;
// std::stack<char>* _rpn_stack;
std::deque<char>* RPN::_rpn_input;
std::deque<char>* RPN::_rpn_stack;

RPN::RPN() {
}

RPN::~RPN() {
}

void RPN::_saveParseInput(std::string input) {
	for (int i = input.size() - 1; input.at(i) == SPACE_SIGN && i >= 0; i--)
		input.erase(i);
	while (input.size() && input.at(0) == SPACE_SIGN)
		input.erase(0);
	if (input.size() == 0)
		throw BadInput("The input is empty");
	for (std::string::reverse_iterator it = input.rbegin(); it != input.rend(); it++) {
		while (*it == SPACE_SIGN)
			it++;
		if (isdigit(*it) == 0 && (*it != ADD_SIGN && *it != SUBTRACT_SIGN
			&& *it != MULTIPLY_SIGN && *it != DIVISION_SIGN))
			throw BadInput(std::string("Unacceptable character in input: ") + *it);
		if (it + 1 != input.rend() && *(it + 1) != SPACE_SIGN)
			throw BadInput(std::string("Two characters in a row: ") + *(it + 1) + *it);
		_rpn_stack->push_front(*it);
	}
	if (isdigit(_rpn_stack->back()) == 0 && _rpn_stack->size() > 2
		&& (_rpn_stack->size() != 1 && _rpn_input->front() != SUBTRACT_SIGN))
			throw BadInput("")
	// if (_rpn_stack->size() == 2
	// 	&& _rpn_stack->at(0) != SUBTRACT_SIGN && _rpn_stack->at(1) != )
	// 		throw BadInput("")
	for (std::deque<char>::iterator it = _rpn_stack->begin(); it != _rpn_stack->end(); it ++)
		std::cout << *it << std::endl;
}

void RPN::_initialize() {
	// _rpn_queue = new std::queue<char>;
	// _rpn_input = new std::stack<char>;
	// _rpn_stack = new std::stack<char>;
	_rpn_input = new std::deque<char>;
	_rpn_stack = new std::deque<char>;
}

void RPN::_cleanup() {
	// delete _rpn_queue;
	delete _rpn_input;
	delete _rpn_stack;
}

int RPN::calculateRPN(std::string input) {
	int result = 0;
	_initialize();
	try {
		_saveParseInput(input);
	} catch (const BadInput& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	_cleanup();
	return result;
}
