/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:59:07 by damendez          #+#    #+#             */
/*   Updated: 2024/12/28 16:26:16 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <stdexcept>

class RPN 
{
    private:        
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        
        std::string     _expression;
        std::stack<int> _stack;

        void    _processToken(const std::string &token);
        bool    _isOperator(const std::string &token) const;
        int     _applyOperator(const std::string &token, int a, int b) const;
        int     _stoi(const std::string &str) const;
        
    public:
        RPN(const std::string &expression);
        ~RPN();
        int evaluate();
};