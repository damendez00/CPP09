/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:35:58 by damendez          #+#    #+#             */
/*   Updated: 2025/01/16 16:27:47 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src): data(src.data)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src)
{
        if (this != &src)
                data = src.data;
        return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

std::map<std::string, float>::size_type BitcoinExchange::data_size() const
{
        return data.size();
}

std::map<std::string, float>::const_iterator BitcoinExchange::operator[](map::size_type pos) const
{
        map::const_iterator iterl = this->data.begin();
        std::advance(iterl, pos);
        return iterl;
}

std::map<std::string, float>::value_type::second_type BitcoinExchange::operator[](std::string key) const
{
        map::const_iterator it;

        it = data.lower_bound(key);
        if (it == data.begin() || (it != data.end() && it->first != key) || it == data.end())
                --it;
        return it->second;
}

void BitcoinExchange::append(std::string key, float value)
{
        std::pair<map::iterator, bool> ret;
        ret = data.insert(std::make_pair(key, value));
        if (ret.second == false)
        {
                std::cout << "Changing rate for " << ret.first->first << std::endl;
                data[key] = value;
        }
}

void BitcoinExchange::append(std::string line)
{
        std::stringstream       ss(line);
        std::string                     key;
        float                           value;

        if (!(line.find(',') == line.npos))
        {
                std::getline(ss, key, ',');
                if (key == "date")
                        return ;
                ss >> value;
                if (ss.fail())
                        std::cerr << "Error: Bad input in db => " << line << std::endl;
        }
        else
        {
                std::cerr << "Error: Bad input in db => " << std::endl;
                return ;
        }
        append(key, value);
}

std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be)
{
        typedef std::map<std::string, float> map;


        for (map::size_type i = 0; i < be.data_size(); i++)
        {
                os << "Key: " << be[i]->first << " ";
                os << "Value: " << be[i]->second;
                os << std::endl;
        }
        return os;
}