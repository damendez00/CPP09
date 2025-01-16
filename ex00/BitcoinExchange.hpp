/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:54:47 by damendez          #+#    #+#             */
/*   Updated: 2025/01/16 16:23:47 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <iomanip>

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
};

std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be);