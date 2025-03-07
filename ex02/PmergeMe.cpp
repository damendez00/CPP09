/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:27 by damendez          #+#    #+#             */
/*   Updated: 2025/03/07 17:21:58 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::vector<int> generate_insertion_order(int n) {
    std::vector<int> order;
    if (n == 0) return order;

    std::vector<int> jacob;
    jacob.push_back(0); // J₀=0
    jacob.push_back(1); // J₁=1
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
                std::vector<int>::iterator pos = binarySearch<std::vector<int> >(vec.begin(), vec.end(), value);
                vec.insert(pos, value);
        }
}

void mergeInsertSort(std::list<int> &list)
{
        if (list.size() <= 1)
                return;
                
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

    std::list<int> pend, main_chain;
    bool addToLeft = true;
    for (std::list<int>::const_iterator val = pairs.begin(); val != pairs.end(); val++)
    {
        int num = *val;
        if (addToLeft)
            pend.push_back(num);
        else
            main_chain.push_back(num);
        addToLeft = !addToLeft;
    }

    mergeInsertSort(main_chain);
        
    list = main_chain;
    std::vector<int> order = generate_insertion_order(pend.size());
    for (std::vector<int>::const_iterator val = order.begin(); val != order.end(); ++val)
    {
        std::list<int>::iterator pend_it = pend.begin();
        std::advance(pend_it, *val);
        int value = *pend_it;
        std::list<int>::iterator pos = binarySearch<std::list<int> >(list.begin(), list.end(), value);
        list.insert(pos, value);
    }
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &container)
{
        if (container.size() <= 10) {
                if (!container.empty()) {
                        for (std::vector<int>::const_iterator it = container.begin(); it != container.end(); it++)
                                os << *it << " ";                        
                }
        } else {
                std::vector<int>::const_iterator it = container.begin();
                for (size_t i = 0; i < 4; i++) {
                        os << *(it++);
                        if (i < 3)
                                os << " ";
                }
                os << " [...] " << *(--container.end());
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
        } else {
                std::list<int>::const_iterator it = container.begin();
                for (size_t i = 0; i < 4; i++) {
                        os << *(it++);
                        if (i < 3)
                                os << " ";
                }
                os << " [...] " << *(--container.end());
        }
        return os;
}