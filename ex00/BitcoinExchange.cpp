/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:35:58 by damendez          #+#    #+#             */
/*   Updated: 2025/03/07 15:45:10 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src): data(src.data) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src)
{
        if (this != &src)
                data = src.data;
        return *this;
}

BitcoinExchange::~BitcoinExchange() {}

map::size_type BitcoinExchange::data_size() const
{
        return data.size();
}

// access by position
map::const_iterator BitcoinExchange::operator[](map::size_type pos) const
{
        map::const_iterator iterl = this->data.begin();
        std::advance(iterl, pos);
        return iterl;
}

// access by key value
map::mapped_type BitcoinExchange::operator[](std::string key) const
{
        map::const_iterator it = data.upper_bound(key);
        if (it == data.begin())
                throw std::out_of_range("Error: No data available for the given date.");
        --it;
        return it->second;
}

void BitcoinExchange::append(const std::string &key, float value)
{
        std::pair<map::iterator, bool> ret = data.insert(std::make_pair(key, value));
        if (!ret.second) {
                std::cout << "Updating rate for " << ret.first->first << std::endl;
                data[key] = value;
        }
}

void BitcoinExchange::append(const std::string &line)
{
        std::stringstream       ss(line);
        std::string             key;
        float                   value;

        if (!(line.find(',') == line.npos)) 
        {
                std::getline(ss, key, ',');
                if (key == "date")
                        return ;
                ss >> value;                
                if (ss.fail())
                        throw std::runtime_error("Bad input in db.");
                check_key(key);
                append(key, value);
        } else {
                throw std::runtime_error("Bad input in db.");   
        }
}

void BitcoinExchange::check_key(const std::string &key) const 
{
        std::stringstream ss(key);
        std::string token;
        int year, month, day;
        int pos = 0;
        
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        static const int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        while (std::getline(ss, token, '-'))
        {
            std::stringstream key(token);
            switch (pos)
            {
                case 0:
                    key >> year;
                    if (key.fail() || !key.eof() || token.length() != 4 || year > now->tm_year + 1900 || year < 2009)
                        throw std::logic_error("Error: Invalid year in date.");
                    break;
                case 1:
                    key >> month;
                    if (key.fail() || !key.eof() || token.length() != 2 || month < 1 || month > 12 || (year == now->tm_year + 1900 && month > now->tm_mon + 1))
                        throw std::logic_error("Error: Invalid month in date.");
                    break;
                case 2:
                    key >> day;
                    if (key.fail() || !key.eof() || token.length() != 2 || day < 1 || day > daysInMonths[month - 1] || (year == now->tm_year + 1900 && month == now->tm_mon + 1 && day > now->tm_mday))
                        throw std::logic_error("Error: Invalid day in date.");
                    break;
                default:
                    throw std::logic_error("Error: Invalid date format.");
            }
            pos++;
        }
        if (pos != 3)
            throw std::logic_error("Error: Incomplete date.");
}

std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be)
{
        for (map::size_type i = 0; i < be.data_size(); i++)
        {
                os << "Key: " << be[i]->first << " ";
                os << "Value: " << be[i]->second;
                os << std::endl;
        }
        return os;
}