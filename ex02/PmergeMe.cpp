/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:27 by damendez          #+#    #+#             */
/*   Updated: 2025/01/07 17:48:50 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <iterator>

PmergeMe::PmergeMe(const std::vector<int>& input) : originalSequence(input) {}

void insertionSortVector(std::vector<int>& vec, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = vec[i];
        int j = i - 1;
        while (j >= left && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

void mergeVector(std::vector<int>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = vec[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = vec[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            ++i;
        } else {
            vec[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        vec[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        vec[k] = R[j];
        ++j;
        ++k;
    }
}

void PmergeMe::mergeInsertSortVector(std::vector<int>& vec, int left, int right) {
    if (left < right) {
        if (right - left <= 10) {
            insertionSortVector(vec, left, right);
        } else {
            int mid = left + (right - left) / 2;
            mergeInsertSortVector(vec, left, mid);
            mergeInsertSortVector(vec, mid + 1, right);
            mergeVector(vec, left, mid, right);
        }
    }
}

void insertionSortList(std::list<int>& lst) {
    if (lst.size() < 2) return;

    std::list<int>::iterator it = lst.begin();
    ++it;
    for (; it != lst.end(); ++it) {
        int key = *it;
        std::list<int>::iterator j = it;
        --j;
        while (j != lst.begin() && *j > key) {
            std::list<int>::iterator next = j;
            ++next;
            *next = *j;
            --j;
        }
        if (*j > key) {
            std::list<int>::iterator next = j;
            ++next;
            *next = *j;
            *j = key;
        } else {
            std::list<int>::iterator next = j;
            ++next;
            *next = key;
        }
    }
}

std::list<int> mergeList(std::list<int>& left, std::list<int>& right) {
    std::list<int> result;
    std::list<int>::iterator it1 = left.begin();
    std::list<int>::iterator it2 = right.begin();

    while (it1 != left.end() && it2 != right.end()) {
        if (*it1 <= *it2) {
            result.push_back(*it1);
            ++it1;
        } else {
            result.push_back(*it2);
            ++it2;
        }
    }

    while (it1 != left.end()) {
        result.push_back(*it1);
        ++it1;
    }

    while (it2 != right.end()) {
        result.push_back(*it2);
        ++it2;
    }

    return result;
}

void PmergeMe::mergeInsertSortList(std::list<int>& lst) {
    if (lst.size() <= 10) {
        insertionSortList(lst);
    } else {
        std::list<int>::iterator middle = lst.begin();
        std::advance(middle, lst.size() / 2);
        std::list<int> left(lst.begin(), middle);
        std::list<int> right(middle, lst.end());

        mergeInsertSortList(left);
        mergeInsertSortList(right);

        lst = mergeList(left, right);
    }
}

void PmergeMe::displaySequence(const std::string& message, const std::vector<int>& sequence) const {
    std::cout << message;
    for (std::vector<int>::const_iterator it = sequence.begin(); it != sequence.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::displaySequence(const std::string& message, const std::list<int>& sequence) const {
    std::cout << message;
    for (std::list<int>::const_iterator it = sequence.begin(); it != sequence.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::sortAndMeasure() {
    displaySequence("Before: ", originalSequence);

    std::vector<int> vectorCopy = originalSequence;
    std::clock_t start = std::clock();
    mergeInsertSortVector(vectorCopy, 0, vectorCopy.size() - 1);
    std::clock_t end = std::clock();
    double vectorDuration = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    sortedWithVector = vectorCopy;

    std::list<int> listCopy(originalSequence.begin(), originalSequence.end());
    start = std::clock();
    mergeInsertSortList(listCopy);
    end = std::clock();
    double listDuration = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    sortedWithList = listCopy;

    displaySequence("After (vector): ", sortedWithVector);
    displaySequence("After (list): ", sortedWithList);

    std::cout << "Time to process a range of " << originalSequence.size() << " elements with std::vector: " << vectorDuration << " ms" << std::endl;
    std::cout << "Time to process a range of " << originalSequence.size() << " elements with std::list: " << listDuration << " ms" << std::endl;
}