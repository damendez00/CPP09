/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:54:47 by damendez          #+#    #+#             */
/*   Updated: 2025/01/12 20:45:31 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <map>

class BitcoinExchange
{
    typedef std::map<std::string, float> map;
    private:
        map data;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& src);
        BitcoinExchange &operator=(const BitcoinExchange& src);
        ~BitcoinExchange();

        map::size_type data_size() const;
        map::const_iterator operator[](map::size_type pos) const;
        map::value_type::second_type operator[](std::string key) const;

        void append(std::string line);
        void append(std::string key, float value);
        void append(std::map<std::string, float>);
};

std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be);