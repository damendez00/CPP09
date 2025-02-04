/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:35:58 by damendez          #+#    #+#             */
/*   Updated: 2025/01/29 18:09:12 by damendez         ###   ########.fr       */
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

        it = data.upper_bound(key);
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
        std::string             key;
        float                   value;

        if (!(line.find(',') == line.npos))
        {
                std::getline(ss, key, ',');
                if (key == "date")
                        return ;
                try {
                        ss >> value;
                        check_key(key);
                } catch (std::exception &e) {
                        throw std::runtime_error("Bad input in db.");
                }        
                if (ss.fail())
                        throw std::runtime_error("Bad input in db.");
        }
        else
        {
                throw std::runtime_error("Bad input in db.");
        }
        append(key, value);
}

void BitcoinExchange::check_key(std::string key) 
{
        std::stringstream ss(key);
        std::string token;
        int year;
        int month;
        int day;

        int pos = 0;
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);

        static const int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        while (std::getline(ss, token, '-')) {
                std::stringstream key(token);
                switch (pos)
                { 
                        case 0:
                                key >> year;
                                if (key.fail() || !key.eof())
                                        throw std::logic_error("check date");
                                if (token.length() != 4 || year > now->tm_year + 1900 || year < 2009)
                                        throw std::logic_error("check date");
                                pos++;
                                continue;
                        case 1:
                                key >> month;
                                //std::cout << "token: " << token << std::endl;
                                //std::cout << month << " now month " << now->tm_mon + 1 << std::endl;
                                //std::cout << year << " now year " << now->tm_year + 1900 << std::endl;
                                if (key.fail() || !key.eof())
                                        throw std::logic_error("check date");
                                if (token.length() != 2 || (year == now->tm_year + 1900 && month > now->tm_mon + 1))
                                        throw std::logic_error("check date");
                                if (month > 12 || month < 1)
                                        throw std::logic_error("check date");
                                pos++;
                                continue;
                        case 2:
                                key >> day;
                                if (key.fail() || !key.eof())
                                        throw std::logic_error("check date");
                                if (token.length() != 2 || (year == now->tm_year + 1900 && month == now->tm_mon + 1 && day > now->tm_mday))
                                        throw std::logic_error("check date");
                                if (year == 2009 && (month < 1 || (month == 1 && day < 02)))
                                        throw std::logic_error("check date");
                                if (day < 1 || day > daysInMonths[month - 1])
                                        throw std::logic_error("check date");
                                pos++;
                                continue;
                        default:
                                throw std::logic_error("check date");
                                continue;
                        pos++;
                }
        }
        if (pos != 3)
                throw std::logic_error("check date");
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