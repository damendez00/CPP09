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
    for (size_t i = 0; i < equation.size(); ++i)
    {
        if (equation[i] == ADD || equation[i] == SUB || equation[i] == DIV || equation[i] == MUL) {
            int_storage.calculate((Operation)equation[i]);
        } else if (equation[i] != ' ' ) {
            std::string stack_element;
            int         j = i; 
            while (equation[i] != ' ')
                i++;
            stack_element.append(equation.begin() + j, equation.begin() + i);
            int_storage.add(stack_element);
            stack_element.clear();
        }
    }
    std::cout << int_storage.top() << std::endl;
}

int main (int argc, char *argv[])
{
    RPN int_storage;

    if (argc != 2)
    {
        std::cerr << "Error: not enough arguments, proper usage: ./RPN <input>." << std::endl;
        return 1;
    }
    try {
        parseInput(int_storage, argv[1]);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}