/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:54:47 by damendez          #+#    #+#             */
/*   Updated: 2025/03/07 15:45:22 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <iomanip>
# include <exception>
# include <cstdlib>
# include <ctime>

typedef std::map<std::string, float> map;

class BitcoinExchange
{
        private:
                map data;
        public:
                BitcoinExchange();
                BitcoinExchange(const BitcoinExchange &src);
                BitcoinExchange &operator=(const BitcoinExchange& src);
                ~BitcoinExchange();

                map::size_type data_size() const;
                map::const_iterator operator[](map::size_type pos) const; // access by position: map[i]
                map::mapped_type operator[](const std::string key) const; // access by key value: map[key]

                void append(const std::string &key, float value);
                void append(const std::string &line);
                void check_key(const std::string &key) const;
};

std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be);