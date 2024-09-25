/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:55:39 by ychng             #+#    #+#             */
/*   Updated: 2024/09/25 13:25:16 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>
#include <stack>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <limits>

bool isNumber(const std::string num)
{
	return num.length() == 1 && std::isdigit(num[0]);
}

bool isOperator(const std::string& op)
{
	return op == "+" || op == "-" || op == "*" || op == "/";
}

int precedence(const std::string& op)
{
	if (op == "+" || op == "-")
		return 1;
	if (op == "*" || op == "/")
		return 2;
	return 0;
}

void processToken(const std::string& token, std::stack<std::string>& postFix, std::stack<std::string>& opStack)
{
	if (isNumber(token))
		postFix.push(token);
	if (isOperator(token))
	{
		while (!opStack.empty() && precedence(opStack.top()) >= precedence(token))
		{
			postFix.push(opStack.top());
			opStack.pop();
		}
		opStack.push(token);
	}
}

std::stack<std::string> reverseStack(std::stack<std::string> stack)
{
	std::stack<std::string> reverse;
	while (!stack.empty())
	{
		reverse.push(stack.top());
		stack.pop();
	}
	// while (!reverse.empty())
	// {
	// 	std::cout << reverse.top() << " ";
	// 	reverse.pop();
	// }
	// std::cout << "\n";
	return reverse;
}

std::stack<std::string> toPostFix(const std::string& infix)
{
	std::stack<std::string> postFix;
	std::stack<std::string> opStack;
	std::stringstream stream(infix);
	std::string token;
	while (stream >> token)
		processToken(token, postFix, opStack);
	while (!opStack.empty())
	{
		postFix.push(opStack.top());
		opStack.pop();
	}
	return reverseStack(postFix);
}



std::stack<std::string> parseRPN(const std::string& input)
{
	std::stack<std::string> postFix;
	std::stringstream stream(input);
	std::string token;
	while (stream >> token)
		postFix.push(token);
	return reverseStack(postFix);
}

long evaluatePostfix(std::stack<std::string>& postFix)
{
	std::stack<int> evalStack;
	
	while (!postFix.empty())
	{
		std::string token = postFix.top();
		postFix.pop();
		if (isNumber(token))
		{
			evalStack.push(atoi(token.c_str()));
		}
		else if (isOperator(token))
		{
			if (evalStack.size() < 2)
			{
				std::cout << "error: not enough operands for " << token << "\n";
				return std::numeric_limits<long>::max();
			}
			int rightOperand = evalStack.top();
			evalStack.pop();
			int leftOperand = evalStack.top();
			evalStack.pop();

			if (token == "+")
				evalStack.push(leftOperand + rightOperand);
			else if (token == "-")
				evalStack.push(leftOperand - rightOperand);
			else if (token == "*")
				evalStack.push(leftOperand * rightOperand);
			else if (token == "/")
			{
				if (rightOperand == 0)
				{
					std::cout << "error: division by zero\n";
					return std::numeric_limits<long>::max();
				}
				evalStack.push(leftOperand / rightOperand);
			}
		}
		else
		{
			std::cout << "error: bad input => " << token << "\n";
			return std::numeric_limits<long>::max();
		}
	}
	return evalStack.top();
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "error: only ./RPN <input> is allowed.\n";
		return -1;
	}
	std::stack<std::string> postFix = parseRPN(argv[1]);
	long result = evaluatePostfix(postFix);
	if (result != std::numeric_limits<long>::max())
		std::cout << result << "\n";
}
