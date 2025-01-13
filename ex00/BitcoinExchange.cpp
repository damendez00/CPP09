/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:35:58 by damendez          #+#    #+#             */
/*   Updated: 2025/01/13 10:11:27 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src) {
    if (this != &src)
        data = src.data;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be) {
    typedef std::map<std::string, float> map;

    for (map::size_type i = 0; i < be.data_size(); i++)
    {
        os << "Key: " << be[i]->first << " ";
        os << "Value: " << be[i]->second;
        os << std::endl;
    }
    return os;
}