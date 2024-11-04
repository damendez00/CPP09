/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:35:58 by damendez          #+#    #+#             */
/*   Updated: 2024/11/04 17:44:40 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BtcExchange::BtcExchange()
{
}

BtcExchange::BtcExchange(const BtcExchange& rhs)
{
    (void)rhs;
}

BtcExchange& BtcExchange::operator=(const BtcExchange& rhs)
{
    (void)rhs;
    return (*this);
}

BtcExchange::~BtcExchange()
{
}

bool    BtcExchange::getCSV(std::map<std::string, float> &data)
{
    std::ifstream file("data.csv");
    if (!file.is_open())
        throw std::runtime_error("Couldn't open CSV db.");
    int linecount = 0;
    std::string line;
    while (std::getline(file, line))
    {
        // extract parts of line separately with a delimeter
        std::istringstream linestream(line);
        std::string date;
        std::string value;
        
        if (std::getline(linestream, date, ',') && std::getline(linestream, value))
        {
            try
            {
                float fvalue = std::stof(value);
                parseDate(date); // TO-DO
                data[date] = fvalue;
            }
            catch(const std::exception& e)
            {
                if (linecount > 0)
                    return true;
            }
            linecount++;
        }
    }
    return false;
}

void    BtcExchange::btc(std::string argv)
{
    (void)argv;
    std::map<std::string, float> data;

    if (!getCSV(data))
        throw std::runtime_error("There's an error in a date in the CSV db.");
    getBTC(data, argv);
}