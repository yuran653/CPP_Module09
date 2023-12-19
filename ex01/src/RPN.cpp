/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:35 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/19 16:51:13 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

std::deque<char>* RPN::_rpn_input;
std::stack<int>* RPN::_rpn_stack;

RPN::RPN() {
}

RPN::~RPN() {
}

char RPN::_intToChar(const int& i) {
	return (i + '0');
}

int RPN::_charToInt(const char& c) {
	return (c - '0');
}

int RPN::_calculateExpression(std::divides<int> func) {
	_rpn_input->pop_front();
	if (_rpn_stack->size() < 2)
		throw BadInput("Not enough operands before operator");
	int b = _rpn_stack->top();
	if (b == 0)
		throw BadInput("Division by zero");
	_rpn_stack->pop();
	int a = _rpn_stack->top();
	_rpn_stack->pop();
	return func(a, b);
}

int RPN::_calculateExpression(std::minus<int> func) {
	_rpn_input->pop_front();
	if (_rpn_stack->size() == 0) {
		_rpn_stack->push(_charToInt(_rpn_input->front()));
		_rpn_input->pop_front();
	}
	int b = _rpn_stack->top();
	_rpn_stack->pop();
	int a = 0;
	if (_rpn_stack->size() > 0) {
		a = _rpn_stack->top();
		_rpn_stack->pop();
	}
	return func(a, b);
}

template <typename Func>
int RPN::_calculateExpression(Func func) {
	_rpn_input->pop_front();
	if (_rpn_stack->size() < 2)
		throw BadInput("Not enough operands before operator");
	int b = _rpn_stack->top();
	_rpn_stack->pop();
	int a = _rpn_stack->top();
	_rpn_stack->pop();
	return func(a, b);
}

int RPN::_calculateStack() {
	while (_rpn_input->size()) {

		switch (_rpn_input->front()) {
			case ADD_SIGN:
				_rpn_stack->push(_calculateExpression(_add));
				break;
			case SUBTRACT_SIGN:
				_rpn_stack->push(_calculateExpression(_subtract));
				break;
			case MULTIPLY_SIGN:
				_rpn_stack->push(_calculateExpression(_multiply));
				break;
			case DIVISION_SIGN:
				_rpn_stack->push(_calculateExpression(_divide));
				break;
			default:
				_rpn_stack->push(_charToInt(_rpn_input->front()));
				_rpn_input->pop_front();
		}
	}
	if (_rpn_stack->size() != 1)
		throw BadInput("More operands than operators");
	return _rpn_stack->top();
}

void RPN::_saveParseInput(std::string& input) {
	std::string::iterator it = input.begin();
	while (it != input.end() && std::isspace(*it))
		it++;
	input.erase(input.begin(), it);
	std::string::reverse_iterator r_it = input.rbegin();
	while (r_it != input.rend() && std::isspace(*r_it))
		r_it++;
	input.erase(r_it.base(), input.end());
	if (input.size() == 0)
		throw BadInput("The input is empty");
	for (r_it = input.rbegin(); r_it != input.rend(); r_it++) {
		while (isspace(*r_it))
			r_it++;
		if (isdigit(*r_it) == 0 && (*r_it != ADD_SIGN && *r_it != SUBTRACT_SIGN
			&& *r_it != MULTIPLY_SIGN && *r_it != DIVISION_SIGN))
			throw BadInput(std::string("Unacceptable character in input: ") + *r_it);
		if (r_it + 1 != input.rend() && *(r_it + 1) != SPACE_SIGN)
			throw BadInput(std::string("Two characters in a row: ") + *(r_it + 1) + *r_it);
		_rpn_input->push_front(*r_it);
	}
	if (_rpn_input->size() == 1 && isdigit(_rpn_input->front()) == 0)
		throw BadInput("Operator can't be the single character of expression");
	if (isdigit(_rpn_input->back()) != 0 && (_rpn_input->size() > 2
		|| (_rpn_input->size() == 2 && _rpn_input->front() != SUBTRACT_SIGN)))
		throw BadInput("Operand can't be the last character");
}

void RPN::_initialize() {
	_rpn_input = new std::deque<char>;
	_rpn_stack = new std::stack<int>;
}

void RPN::_cleanup() {
	delete _rpn_input;
	delete _rpn_stack;
}

void RPN::calculateRPN(const char* argv) {
	std::string input(argv);
	_initialize();
	try {
		if (input.size() == 0)
			throw BadInput("The input is empty");
		_saveParseInput(input);
		std::cout << _calculateStack() << std::endl;
	} catch (const BadInput& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	_cleanup();
}
