/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:24 by damendez          #+#    #+#             */
/*   Updated: 2025/01/07 17:46:20 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <list>
#include <string>

class PmergeMe {
public:
    PmergeMe(const std::vector<int>& input);
    void sortAndMeasure();

private:
    std::vector<int> originalSequence;
    std::vector<int> sortedWithVector;
    std::list<int> sortedWithList;

    void mergeInsertSortVector(std::vector<int>& vec, int left, int right);
    void mergeInsertSortList(std::list<int>& lst);

    void displaySequence(const std::string& message, const std::vector<int>& sequence) const;
    void displaySequence(const std::string& message, const std::list<int>& sequence) const;
};