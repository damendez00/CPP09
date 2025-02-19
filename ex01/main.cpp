/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:31:25 by damendez          #+#    #+#             */
/*   Updated: 2025/02/19 17:23:35 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void parseInput(RPN &int_storage, std::string equation)
{
    size_t oper_count = 0;
    std::stringstream ss(equation);
    std::string stack_element;
    while (ss >> stack_element)
    {
        if (stack_element == "+" || stack_element == "-"  || stack_element == "/" || stack_element == "*")
            int_storage.calculate(stack_element, oper_count);
        else
            int_storage.add(stack_element);
    }
    if (int_storage.size() != 1 || oper_count == 0)
        throw std::runtime_error("Error: Invalid format.");
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
        std::cout << int_storage.top() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}