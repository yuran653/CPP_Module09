/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:29 by jgoldste          #+#    #+#             */
/*   Updated: 2023/12/14 15:47:21 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <stack>
#include <string>

#define SPACE_SIGN ' '
#define ADD_SIGN '+'
#define SUBTRACT_SIGN '-'
#define MULTIPLY_SIGN '*'
#define DIVISION_SIGN '/'

class RPN {
	private:
		static std::deque<char>* _rpn_input;
		static std::stack<char>* _rpn_stack;

		static std::plus<int> _add;
		static std::minus<int> _subtract;
		static std::multiplies<int> _multiply;
		static std::divides<int> _divide;

		static void _initialize();
		static void _cleanup();
		static void _saveParseInput(std::string input);
		static int _calculateStack();
		template <typename Func>
		static int _calculateExpression(Func func);
		static int _calculateExpression(std::divides<int> func);
		static int _charToInt(char c);
		static char _intToChar(int i);

		RPN();
		~RPN();

	public:
		static void calculateRPN(std::string input);

		class BadInput : public std::runtime_error {
			public:
				BadInput(const std::string& message) : std::runtime_error(message) {}
	};
};
