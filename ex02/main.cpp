/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:32 by damendez          #+#    #+#             */
/*   Updated: 2025/01/27 18:56:40 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>
#include <time.h>

int main(int argc, const char *argv[])
{
        std::vector<int> vector_container;
        std::list<int> list_container;

        std::clock_t start;
        std::clock_t finish;

        if (argc < 2)
        {
                std::cout << "Need at least one argument for the program" << std::endl;
                return 1;
        }

        // vector container sort
        // try {
        //         start = std::clock();
        //         vector_container = build_container<std::vector<int> >(&argv[1]);
        //         std::cout << "Before: " << vector_container << std::endl;
        //         //mergeInsertSort(vector_container);
        //         std::cout << "After: " << vector_container << std::endl;
        //         finish = std::clock();
        //         std::cout << "Time to process a range of 5 elements with std::vector<int>: "
        //                 << (float)(finish - start)/CLOCKS_PER_SEC * 1000000 << " us" << std::endl;
        // } catch (const std::exception &e) {
        //         std::cout << "Error: " << e.what() << std::endl;
        //         return 1;
        // }

        // list contaner sort
        try {
                start = std::clock();
                list_container = build_container<std::list<int> >(&argv[1]);
                std::cout << "Before: " << list_container << std::endl;
                mergeInsertSort(list_container);
                std::cout << "After: " << list_container << std::endl;
                finish = std::clock();
                std::cout << "Time to process a range of 5 elements with std::list<int>: "
                        << (float)(finish - start)/CLOCKS_PER_SEC * 1000000 << " us" << std::endl;
        } catch (const std::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
                return 1;
        }
        return 0;
}