/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:54:47 by damendez          #+#    #+#             */
/*   Updated: 2025/02/06 19:53:00 by damendez         ###   ########.fr       */
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

class BitcoinExchange
{
        typedef std::map<std::string, float> map;
        private:
                map data;
        public:
                BitcoinExchange();
                BitcoinExchange(const BitcoinExchange &src);
                BitcoinExchange &operator=(const BitcoinExchange& src);
                ~BitcoinExchange();

                map::size_type data_size() const;
                map::const_iterator operator[](map::size_type pos) const;
                map::value_type::second_type operator[](std::string key) const;

                void append(std::string key, float value);
                void append(std::string line);
                void check_key(std::string key);
};

std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be);