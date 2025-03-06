/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:24 by damendez          #+#    #+#             */
/*   Updated: 2025/03/06 17:47:23 by damendez         ###   ########.fr       */
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
                if (ss.fail())
                        throw std::invalid_argument("Invalid argument");
                if (find_duplicate(container, entry) || entry < 0)
                        throw std::invalid_argument("Duplicate or negative value");
                container.push_back(entry);
        }
        if (container.size() <= 1)
                throw std::invalid_argument("Only 1 positive integer detected, already sorted!");
        return container;
}

template <typename Container>
Container generate_insertion_order(int n) {
        Container order;
        if (n == 0) return order;

        Container jacob;
        jacob.push_back(0); // J₀=0
        jacob.push_back(1); // J₁=1
        while (jacob.back() <= n) {
            jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
        }
    
        // Calculate group sizes from Jacobsthal differences (J₂ onward)
        Container groups;
        for (size_t i = 2; i < jacob.size(); ++i) {
            int diff = jacob[i] - jacob[i - 1];
            if (diff > 0) groups.push_back(diff);
        }
        std::reverse(groups.begin(), groups.end()); // Reverse for largest groups first
    
        // Determine actual group sizes for `n` elements
        int remaining = n;
        Container group_sizes;
        for (size_t i = 0; i < groups.size(); ++i) {
            if (remaining <= 0) break;
            int take = std::min(groups[i], remaining);
            group_sizes.push_back(take);
            remaining -= take;
        }
        if (remaining > 0) group_sizes.push_back(remaining);
    
        // Generate insertion order (from end of `pend` to start)
        int current = n - 1;
        for (size_t i = 0; i < group_sizes.size(); ++i) {
            int start = current - group_sizes[i] + 1;
            for (int j = current; j >= start; --j) order.push_back(j);
            current = start - 1;
        }
        return order;
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &container);
std::ostream &operator<<(std::ostream &os, const std::list<int> &container);

void mergeInsertSort(std::vector<int> &vec);
void mergeInsertSort(std::list<int> &list);
