/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:27 by damendez          #+#    #+#             */
/*   Updated: 2025/02/04 18:58:51 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

std::ostream &operator<<(std::ostream &os, const std::vector<int> &container)
{
        // if (container.size() > 5)
        // {
        //         std::vector<int>::const_iterator it = container.begin();
        //         for (int i = 0; i < 4; i++)
        //         {
        //                 os << *it << " ";
        //                 it++;
        //         }
        //         os << "... ";
        //         os << container.back();
        //         return os;
        // }
        for (std::vector<int>::const_iterator it = container.begin(); it != container.end(); it++)
        {
                os << *it << " ";
        }
        return os;
}

std::ostream &operator<<(std::ostream &os, const std::list<int> &container)
{
        // if (container.size() > 5)
        // {
        //         std::list<int>::const_iterator it = container.begin();
        //         for (int i = 0; i < 4; i++)
        //         {
        //                 os << *it << " ";
        //                 it++;
        //         }
        //         os << "... ";
        //         os << container.back();
        //         return os;
        // }
        for (std::list<int>::const_iterator it = container.begin(); it != container.end(); it++)
        {
                os << *it << " ";
        }
        return os;
}

void mergeInsertSort(std::vector<int> &vec)
{
        if (vec.size() <= 1)
                return ;
        
        // Pair up and compare elements
        std::vector<int> pairs;
        for (size_t i = 0; i < vec.size(); i += 2)
        {
                if (i + 1 < vec.size())
                {
                        if (vec[i] < vec[i + 1])
                        {
                                pairs.push_back(vec[i]);
                                pairs.push_back(vec[i + 1]);
                        }
                        else
                        {
                                pairs.push_back(vec[i + 1]);
                                pairs.push_back(vec[i]);    
                        }
                }
                else
                        pairs.push_back(vec[i]);
        }

        // Sort pairs
        std::vector<int> left, right;
        for (size_t i = 0; i < pairs.size(); i += 2)
        {
                left.push_back(pairs[i]);
                if (i + 1 < pairs.size())
                        right.push_back(pairs[i + 1]);
        }
        
        //std::cout << "Pairs: ";
        // for (const auto &p : pairs) // TO-CHANGE
        //         std::cout << p << " ";
        // std::cout << std::endl;
        // std::cout << "Left before sorting left: " << left << std::endl;
        // std::cout << "Right before sorting left: " << right << std::endl;
        mergeInsertSort(left);
        // std::cout << "Left before sorting right: " << left << std::endl;
        // std::cout << "Right before sorting right: " << right << std::endl;
        mergeInsertSort(right);

        // Merge left and right using binary insertion
        vec.clear();
        for (const auto &val : left)
        {
                auto pos = std::lower_bound(vec.begin(), vec.end(), val);
                vec.insert(pos, val);
        }
        for (const auto &val : right)
        {
                auto pos = std::lower_bound(vec.begin(), vec.end(), val);
                vec.insert(pos, val);
        }
}

void mergeInsertSort(std::list<int> &list)
{
    if (list.size() <= 1)
        return;

    // Pair up and compare elements
    std::list<int> pairs;
    std::list<int>::const_iterator it = list.begin();
    while (it != list.end())
    {
        int first = *it;
        ++it;
        if (it == list.end()) {
            pairs.push_back(first);
            break;
        }
        int second = *it;
        ++it;
        if (first < second)
        {
            pairs.push_back(first);
            pairs.push_back(second);
        }
        else
        {
            pairs.push_back(second);
            pairs.push_back(first);
        }
    }

    // Split into left and right
    std::list<int> left, right;
    bool addToLeft = true;
    for (std::list<int>::const_iterator val = pairs.begin(); val != pairs.end(); val++)
    {
        int num = *val;
        if (addToLeft)
            left.push_back(num);
        else
            right.push_back(num);
        addToLeft = !addToLeft;
    }

    // Recursively sort left and right
    mergeInsertSort(left);
    mergeInsertSort(right);

    // Merge left and right using binary insertion
    list.clear();
    for (const auto &val : left)
    {
        auto pos = std::lower_bound(list.begin(), list.end(), val);
        list.insert(pos, val);
    }
    for (const auto &val : right)
    {
        auto pos = std::lower_bound(list.begin(), list.end(), val);
        list.insert(pos, val);
    }
}
