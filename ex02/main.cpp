/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:32 by damendez          #+#    #+#             */
/*   Updated: 2025/01/07 15:28:44 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <positive integers>" << std::endl;
        return 1;
    }

    std::vector<int> inputSequence;
    for (int i = 1; i < argc; ++i) {
        try {
            int value = std::atoi(argv[i]);
            if (value <= 0) {
                throw std::invalid_argument("Negative or zero value");
            }
            inputSequence.push_back(value);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    PmergeMe sorter(inputSequence);
    sorter.sortAndMeasure();

    return 0;
}