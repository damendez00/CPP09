/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:59:07 by damendez          #+#    #+#             */
/*   Updated: 2025/01/17 20:01:39 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <stack>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

enum Operation
{
    ADD = '+',
    SUB = '-',
    DIV = '/',
    MUL = '*'
};

class RPN: public std::stack<int>
{
    public:
        RPN();
        RPN(const RPN &src);
        RPN &operator=(const RPN &src);
        ~RPN();
        void calculate(Operation operation);
        void add(std::string stack_element);
        int add(int v1, int v2);
        int substract(int v1, int v2);
        int multiply(int v1, int v2);
        int divide(int v1, int v2);
};