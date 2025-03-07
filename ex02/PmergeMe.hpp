/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:24 by damendez          #+#    #+#             */
/*   Updated: 2025/03/07 17:06:28 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <list>
# include <iostream>
# include <sstream>
# include <ostream>
# include <algorithm>

template <typename Container>
bool find_duplicate(const Container &nums, int new_value)
{
        for (typename Container::const_iterator it = nums.begin(); it != nums.end(); ++it)
        {
                if (*it == new_value)
                        return true;
        }
        return false;
}

template <typename Container>
Container build_container(const char **args)
{
        Container container;
        for (int i = 0; args[i]; ++i)
        {
                int entry;
                std::stringstream ss(args[i]);
                ss >> entry;
                if (ss.fail() || !ss.eof())
                        throw std::invalid_argument("Invalid argument: " + std::string(args[i]));
                if (find_duplicate(container, entry) || entry < 0)
                        throw std::invalid_argument("Duplicate or negative value: " + std::string(args[i]));
                container.push_back(entry);
        }
        if (container.size() <= 1)
                throw std::invalid_argument("Only 1 positive integer detected, already sorted!");
        return container;
}

template <typename Container>
typename Container::iterator binarySearch(typename Container::iterator begin, typename Container::iterator end, int value) {
        while (begin != end) {
                typename Container::iterator mid = begin;
                std::advance(mid, std::distance(begin, end) / 2);
                if (*mid < value) {
                        begin = ++mid;
                } else {
                        end = mid;
                }
        }
        return begin;
}

void mergeInsertSort(std::vector<int> &vec);

void mergeInsertSort(std::list<int> &list);

std::ostream &operator<<(std::ostream &os, const std::vector<int> &container);

std::ostream &operator<<(std::ostream &os, const std::list<int> &container);


