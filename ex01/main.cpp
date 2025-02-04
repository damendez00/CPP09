/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:31:25 by damendez          #+#    #+#             */
/*   Updated: 2025/01/29 18:40:55 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void parseInput(RPN &int_storage, std::string equation)
{
    size_t oper_count = 0;
    for (size_t i = 0; i < equation.size(); ++i)
    {
        if (equation[i] == ADD || equation[i] == SUB || equation[i] == DIV || equation[i] == MUL) {
            int_storage.calculate((Operation)equation[i], oper_count);
        } else if (equation[i] != ' ' ) {
            std::string stack_element;
            int         j = i; 
            while (equation[i] != ' ' && equation[i])
                i++;
            stack_element.append(equation.begin() + j, equation.begin() + i);
            int_storage.add(stack_element);
            stack_element.clear();
        }
    }
    if (int_storage.size() != 1 || oper_count == 0)
        throw std::runtime_error("Error: Invalid input format.");
    std::cout << int_storage.top() << std::endl;
}

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: not enough arguments, proper usage: ./RPN <input>." << std::endl;
        return 1;
    }
    try {
        RPN int_storage;
        parseInput(int_storage, argv[1]);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}