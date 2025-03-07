/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:59:07 by damendez          #+#    #+#             */
/*   Updated: 2025/03/07 15:51:51 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <stack>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <limits>

class RPN: public std::stack<int>
{
    public:
        RPN();
        RPN(const RPN &src);
        RPN &operator=(const RPN &src);
        ~RPN();
        
        void calculate(std::string oper, size_t &oper_count);
        void add(std::string stack_element);
        void add(int v1, int v2);
        void substract(int v1, int v2);
        void multiply(int v1, int v2);
        void divide(int v1, int v2);
};

