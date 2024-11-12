/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:35:58 by damendez          #+#    #+#             */
/*   Updated: 2024/11/12 19:35:37 by damendez         ###   ########.fr       */
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

float	BtcExchange::stringToFloat(const std::string &str)
{
    std::stringstream ss(str);
    float result;
    ss >> result;
    if (ss.fail())
        throw std::invalid_argument("Error: invalid number.");   
    return result;
}

int	BtcExchange::stringToInt(const std::string &str)
{
    std::stringstream ss(str);
    int result;
    ss >> result;
    if (ss.fail())
        throw std::invalid_argument("Error: invalid number.");
    return result;
}

void	BtcExchange::parseFileLine(std::string date, float value)
{
    bool error = false;
    
    if (value < 0)
        throw std::out_of_range("Error: not a positive number.");
    if (value > 1000)
        throw std::out_of_range("Error: number too large.");
    if (date.length() >= 10)
    {
        std::string year = date.substr(0, 4);
        for (int i = 0; i < (int)year.length(); i++)
            if (!std::isdigit(year[i]))
                error = true;
        if (error == false && (stringToInt(year) > 2023 || stringToInt(year) < 2009))
            error = true;

        std::string	month = date.substr(5, 2);
		for (int i = 0; i < (int)month.length(); i++)
			if (error == false && !std::isdigit(month[i]))
				error = true;
		if (error == false && stringToInt(month) > 12)
			error = true;
			
		std::string	day = date.substr(8, 2);
		for (int i = 0; i < (int)day.length(); i++)
			if (error == false && !std::isdigit(day[i]))
				error = true;
		if (error == false && stringToInt(day) > 31)
			error = true;
		if (error == false && stringToInt(day) < 2 && stringToInt(year) == 2009)
			error = true;
    }
    else
        error = true;
    if (error)
    {
        std::string error = "Error: date ";
        error.append(date);
        error.append(" is invalid. ");
        throw std::invalid_argument(error);
    }
}

bool	BtcExchange::getBTC(const std::map<std::string, float> &data, std::string infile)
{
    std::ifstream file(infile.c_str());
    if (!file.is_open())
    {
        std::string error;
        error = "Couldn't open input file: ";
        error.append(infile);
        error.append(".");
        throw std::runtime_error(error);
    }
    std::string line;
    int linecount = 0;
    while (std::getline(file, line))
    {
        std::istringstream linestream(line);
        std::string date;
        std::string value;
        if (std::getline(linestream, date, '|') && std::getline(linestream, value))
        {
            try
            {
                date = date.substr(0,10);
                float fvalue = 0;
                try
                {
                    value = value.substr(1, value.length());
                    for (int i = 0; i < (int)value.length(); i++)
                        if (!std::isdigit(value[i]) && value[i] != '.')
                            throw std::invalid_argument("Error: invalid number.");
                    fvalue = stringToFloat(value);
                }
                catch(const std::exception& e)
                {
                    throw std::invalid_argument("Error: invalid number.");
                }
                parseFileLine(date, fvalue);
                std::map<std::string, float>::const_iterator it = data.lower_bound(date); // position of map that has string not less than date
		        // if (it == data.begin() || (it != data.end() && it->first != date))
			    //     --it;
                //std::cout << "Date from data: " << it->first << " Value from data: " << it->second << std::endl;
                if (it == data.end())
                    --it;
                std::cout << date << " => " << fvalue << " = " << it->second * fvalue << std::endl;
            }
            catch(const std::exception& e)
            {
                if (linecount > 0)
                    std::cerr << e.what() << '\n';
            }
            linecount++;
        }
        else
            std::cout << "Error: date " << line << " is invalid." << std::endl;
    }
    return false; // ?
}

void	BtcExchange::parseDate(std::string date)
{
    for (int i = 0; i < (int)date.length(); i++)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] == '-')
                continue;
            else
            {
                std::cout << date << "" << date[i] << std::endl;
                throw std::runtime_error("There's an error in a date in the CSV db.");
            }
        }
        else
        {
            if (date[i] >= '0' && date[i] <= '9')
                continue ;
            else
                throw std::runtime_error("There's an error in a date in the CSV db.");
        }
    }
}

bool	BtcExchange::BtcExchange::getCSV(std::map<std::string, float> &data)
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
                float fvalue = stringToFloat(value);
                parseDate(date);
                data[date] = fvalue;
            }
            catch(const std::exception& e)
            {
                if (linecount > 0)
                    return false; // ?
            }
            linecount++;
        }
    }
    return true;
}

void    BtcExchange::btc(std::string argv)
{
    std::map<std::string, float> data;

    if (!getCSV(data))
        throw std::runtime_error("There's an error in a date in the CSV db.");
    getBTC(data, argv);
}
