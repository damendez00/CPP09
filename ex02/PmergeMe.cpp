/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:27 by damendez          #+#    #+#             */
/*   Updated: 2025/03/04 20:46:17 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <vector>
#include <list>
#include <algorithm>

std::vector<int> generate_insertion_order(int n) {
    std::vector<int> order;
    if (n == 0) return order;

    // Generate Jacobsthal numbers until they exceed `n`
    std::vector<int> jacob = {0, 1}; // J₀=0, J₁=1
    while (jacob.back() <= n) {
        jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
    }

    // Calculate group sizes from Jacobsthal differences (J₂ onward)
    std::vector<int> groups;
    for (size_t i = 2; i < jacob.size(); ++i) {
        int diff = jacob[i] - jacob[i - 1];
        if (diff > 0) groups.push_back(diff);
    }
    std::reverse(groups.begin(), groups.end()); // Reverse for largest groups first

    // Determine actual group sizes for `n` elements
    int remaining = n;
    std::vector<int> group_sizes;
    for (int g : groups) {
        if (remaining <= 0) break;
        int take = std::min(g, remaining);
        group_sizes.push_back(take);
        remaining -= take;
    }
    if (remaining > 0) group_sizes.push_back(remaining);

    // Generate insertion order (from end of `pend` to start)
    int current = n - 1;
    for (int size : group_sizes) {
        int start = current - size + 1;
        for (int i = current; i >= start; --i) order.push_back(i);
        current = start - 1;
    }

    return order;
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &container)
{
        if (container.size() <= 10) {
                if (!container.empty()) {
                        for (std::vector<int>::const_iterator it = container.begin(); it != container.end(); it++)
                                os << *it << " ";                        
                }
        }
        else {
                std::vector<int>::const_iterator it = container.begin();
                for (size_t i = 0; i < 4; i++)
                        os << *(++it) << " ";
                os << " [...] " << *(container.end() - 1);
        }
        return os;
}

std::ostream &operator<<(std::ostream &os, const std::list<int> &container)
{
        if (container.size() <= 10) {
                if (!container.empty()) {
                        for (std::list<int>::const_iterator it = container.begin(); it != container.end(); it++)
                                os << *it << " ";
                }
        }
        else {
                std::list<int>::const_iterator it = container.begin();
                for (size_t i = 0; i < 4; i++)
                        os << *(++it) << " ";
                std::list<int>::const_iterator last = container.end();
                --last;
                os << " [...] " << *last;
        }
        return os;
}

void mergeInsertSort(std::vector<int> &vec)
{
        if (vec.size() <= 1)
                return ;
        
        // Step 1: Pair and compare elements
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

        // Step 2: Split smaller elements 'pend' and larger elements 'main_chain'
        std::vector<int> pend, main_chain;
        for (size_t i = 0; i < pairs.size(); i += 2)
        {
                pend.push_back(pairs[i]);
                if (i + 1 < pairs.size())
                        main_chain.push_back(pairs[i + 1]);
        }
        
        mergeInsertSort(main_chain);

        // Merge left and right using binary insertion
        vec = main_chain;
        std::vector<int> order = generate_insertion_order(pend.size());
        for (std::vector<int>::const_iterator val = order.begin(); val != order.end(); ++val)
        {
                int value = pend[*val];
                std::vector<int>::iterator pos = std::lower_bound(vec.begin(), vec.end(), *val);
                vec.insert(pos, value);
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
    for (std::list<int>::const_iterator val = left.begin(); val != left.end(); ++val)
    {
        std::list<int>::iterator pos = std::lower_bound(list.begin(), list.end(), *val);
        list.insert(pos, *val);
    }
    for (std::list<int>::const_iterator val = right.begin(); val != right.end(); ++val)
    {
        std::list<int>::iterator pos = std::lower_bound(list.begin(), list.end(), *val);
        list.insert(pos, *val);
    }
}
