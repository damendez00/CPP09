/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:27 by damendez          #+#    #+#             */
/*   Updated: 2025/01/27 18:55:55 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::ostream &operator<<(std::ostream &os, const std::vector<int> &container)
{
        if (container.size() > 5)
        {
                std::vector<int>::const_iterator it = container.begin();
                for (int i = 0; i < 4; i++)
                {
                        os << *it << " ";
                        it++;
                }
                os << "... ";
                os << container.back();
                return os;
        }
        for (std::vector<int>::const_iterator it = container.begin(); it != container.end(); it++)
        {
                os << *it << " ";
        }
        return os;
}

std::ostream &operator<<(std::ostream &os, const std::list<int> &container)
{
        if (container.size() > 5)
        {
                std::list<int>::const_iterator it = container.begin();
                for (int i = 0; i < 4; i++)
                {
                        os << *it << " ";
                        it++;
                }
                os << "... ";
                os << container.back();
                return os;
        }
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
        
        std::vector<int>::iterator middle = vec.begin() + vec.size() / 2;

        std::vector<int> left(vec.begin(), middle);
        std::vector<int> right(middle, vec.end());

        mergeInsertSort(left);
        mergeInsertSort(right);

        std::vector<int>::iterator leftIt = left.begin();
        std::vector<int>::iterator rightIt = right.begin();
        std::vector<int>::iterator numsIt = vec.begin();

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


void mergeInsertSort(std::list<int> &list)
{
        if (list.size() == 1)
                return ;
        
        std::list<int>::iterator middle = list.begin();
        std::advance(middle, list.size() / 2);

        std::list<int> left(list.begin(), middle);
        std::list<int> right(middle, list.end());

        mergeInsertSort(left);
        mergeInsertSort(right);

        std::list<int>::iterator leftIt = left.begin();
        std::list<int>::iterator rightIt = right.begin();
        std::list<int>::iterator numsIt = list.begin();

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
