/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:46:43 by damendez          #+#    #+#             */
/*   Updated: 2024/12/28 16:38:18 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(const std::string& expression) : _expression(expression) {}

RPN::~RPN() {}

int     RPN::evaluate() {
    std::istringstream iss(_expression);
    std::string token;
    while (iss >> token)
        _processToken(token);
    if (_stack.size() != 1)
        throw std::runtime_error("Error: Invalid expression");
    return _stack.top();
}

void    RPN::_processToken(const std::string& token) {
    if (_isOperator(token)) {
        if (_stack.size() < 2)
            throw std::runtime_error("Error: Invalid expression");
        int b = _stack.top(); _stack.pop();
        int a = _stack.top(); _stack.pop();
        int result = _applyOperator(token, a, b);
        _stack.push(result);
    } else {
        int value = _stoi(token);
        _stack.push(value);
    }
}

bool    RPN::_isOperator(const std::string& token) const {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int     RPN::_applyOperator(const std::string& token, int a, int b) const {
    if (token == "+") return a + b;
    else if (token == "-") return a - b;
    else if (token == "*") return a * b;
    else if (token == "/") return a / b;
    throw std::runtime_error("Error: Unknown operator");
}

int     RPN::_stoi(const std::string& str) const {
    std::istringstream string(str);
    int value;
    string >> value;
    return value;
}