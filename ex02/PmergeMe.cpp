/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:27 by damendez          #+#    #+#             */
/*   Updated: 2025/01/22 15:06:07 by damendez         ###   ########.fr       */
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