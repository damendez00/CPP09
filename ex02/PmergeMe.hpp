/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:24 by damendez          #+#    #+#             */
/*   Updated: 2025/01/22 14:55:42 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <list>
# include <iostream>
# include <sstream>
# include <ostream>

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
void mergeInsertSort(Container &nums)
{
        if (nums.size() <= 1)
                return ;

        Container left(nums.begin(), nums.begin() + nums.size() / 2);
        Container right(nums.begin() + nums.size() / 2, nums.end());

        mergeInsertSort(left);
        mergeInsertSort(right);

        typename Container::iterator leftIt = left.begin();
        typename Container::iterator rightIt = right.begin();
        typename Container::iterator numsIt = nums.begin();

        while (leftIt != left.end() && rightIt != right.end())
        {
                if (*leftIt < *rightIt)
                        *numsIt++ = *leftIt++;
                else
                        *numsIt++ = *rightIt++;
        }

        while (leftIt != left.end())
        {
                *numsIt++ = *leftIt++;
        }
        while (rightIt != right.end())
        {
                *numsIt++ = *rightIt++;
        }
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
                if (ss.fail())
                        throw std::invalid_argument("Invalid argument");
                if (find_duplicate(container, entry) || entry < 0)
                        throw std::invalid_argument("Duplicate or negative value");
                container.push_back(entry);
        }
        return container;
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &container);
std::ostream &operator<<(std::ostream &os, const std::list<int> &container);