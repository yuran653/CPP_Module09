/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:29 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/12 20:29:13 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque>
#include <iostream>
// #include <queue>
// #include <stack>
#include <string>

#define SPACE_SIGN ' '
#define ADD_SIGN '+'
#define SUBTRACT_SIGN '-'
#define MULTIPLY_SIGN '*'
#define DIVISION_SIGN '/'

class RPN {
	private:
		// static std::queue<char>* _rpn_queue;
		// static std::stack<char>* _rpn_input;
		// static std::stack<char>* _rpn_stack;
		static std::deque<char>* _rpn_input;
		static std::deque<char>* _rpn_stack;

		static void _initialize();
		static void _cleanup();
		static void _saveParseInput(std::string input);

		RPN();
		~RPN();

	public:
		static int calculateRPN(std::string input);

		class BadInput : public std::runtime_error {
			public:
				BadInput(const std::string& message) : std::runtime_error(message) {}
	};
};