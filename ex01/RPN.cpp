/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:46:43 by damendez          #+#    #+#             */
/*   Updated: 2025/02/19 19:34:35 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(): std::stack<int>() {}

RPN::RPN(const RPN &src): std::stack<int>(src) {}

RPN &RPN::operator=(const RPN &src)
{
    if (this != &src)
        std::stack<int>::operator=(src);
    return *this;
}

RPN::~RPN() {}

void RPN::calculate(std::string oper, size_t &oper_count)
{
    if (this->size() < 2) {
        throw std::logic_error("Error: Invalid input format");
    }
    int v1;
    int v2;
    
    void (RPN::*operation[4])(int, int) = {&RPN::add, &RPN::substract, &RPN::multiply, &RPN::divide};
    char operations[5] = "+-*/";
    v2 = this->top();
    this->pop();
    v1 = this->top();
    this->pop();
    for (int i = 0; i < 5; ++i) 
    {
        if (operations[i] == oper[0])
        {
            (this->*(operation[i]))(v1, v2);
            oper_count++;
            break ;
        }
    }
}

void RPN::add(std::string stack_element)
{
    std::stringstream ss(stack_element);
    int value;
    ss >> value;
    if (ss.fail())
        throw std::invalid_argument("Error: Invalid argument in input");
    this->push(value);
}

void RPN::add(int v1, int v2)
{
    if ((v2 > 0 && v1 > std::numeric_limits<int>::max() - v2) ||
        (v2 < 0 && v1 < std::numeric_limits<int>::min() - v2)) {
        throw std::overflow_error("Error: Integer overflow in addition");
    }
    int num = v1 + v2;
    this->push(num);
}

void RPN::substract(int v1, int v2)
{
    if ((v2 < 0 && v1 > std::numeric_limits<int>::max() + v2) ||
        (v2 > 0 && v1 < std::numeric_limits<int>::min() + v2)) {
        throw std::overflow_error("Error: Integer overflow in subtraction");
    }
    int num = v1 - v2;
    this->push(num);
}

void RPN::multiply(int v1, int v2)
{
    if (v1 != 0 && (v2 > std::numeric_limits<int>::max() / v1 || v2 < std::numeric_limits<int>::min() / v1)) {
        throw std::overflow_error("Error: Integer overflow in multiplication");
    }
    int num = v1 * v2;
    this->push(num);
}

void RPN::divide(int v1, int v2)
{
    if (v2 == 0) {
        throw std::runtime_error("Error: Tried to divide by 0");
    }
    if (v1 == std::numeric_limits<int>::min() && v2 == -1) {
        throw std::overflow_error("Error: Integer overflow in division");
    }
    int num = v1 / v2;
    this->push(num);
}