/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:46:43 by damendez          #+#    #+#             */
/*   Updated: 2025/01/29 18:51:46 by damendez         ###   ########.fr       */
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

void RPN::calculate(Operation oper)
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
        if (operations[i] == oper) 
        {
            if (v2 == 0 && operations[i] == '/')
                throw std::runtime_error("Error: Tried to divide by 0");
            (this->*(operation[i]))(v1, v2);
            break ;
        }
    }
}

void RPN::add(std::string stack_element)
{
    if (stack_element.size() != 1) {
        throw std::invalid_argument("Error: Invalid argument in input");
    }
    std::stringstream ss;
    ss << stack_element;
    int value;
    ss >> value;
    if (ss.fail())
        throw std::invalid_argument("Error: Invalid argument in input");
    this->push(value);
}

void  RPN::add(int v1, int v2)
{
    this->push(v1 + v2);
}

void  RPN::substract(int v1, int v2)
{
    this->push(v1 - v2);
}

void  RPN::multiply(int v1, int v2)
{
    this->push(v1 * v2);
}

void  RPN::divide(int v1, int v2)
{
    this->push(v1 / v2);
}