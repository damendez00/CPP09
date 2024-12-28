/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:35:58 by damendez          #+#    #+#             */
/*   Updated: 2024/12/28 17:48:36 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

BitcoinExchange::BitcoinExchange(const std::string& dbFile) {
    loadDatabase(dbFile);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& dbFile) {
    std::ifstream file(dbFile.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open database file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        double rate;
        if (std::getline(iss, date, ',') && iss >> rate) {
            exchangeRates[date] = rate;
        }
    }
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it = exchangeRates.lower_bound(date);
    if (it == exchangeRates.end() || it->first != date) {
        if (it == exchangeRates.begin()) {
            throw std::runtime_error("Error: no available exchange rate.");
        }
        --it;
    }
    return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    std::istringstream ss(date);
    int year, month, day;
    char delim1, delim2;
    if (ss >> year >> delim1 >> month >> delim2 >> day && delim1 == '-' && delim2 == '-') {
        if (year == 2 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
            return true;
        }
    }
    return false;
}

bool BitcoinExchange::isValidValue(const std::string& value) const {
    try {
        double val = stod(value);
        return val >= 0.0 && val <= 1000.0;
    } catch (...) {
        return false;
    }
}

void BitcoinExchange::processInputFile(const std::string& inputFile) {
    std::ifstream file(inputFile.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date, value;
        if (std::getline(iss, date, '|') && std::getline(iss, value)) {
            date.erase(date.find_last_not_of(" \n\r\t") + 1);
            value.erase(0, value.find_first_not_of(" \n\r\t"));
            if (!isValidDate(date)) {
                std::cerr << "Error: bad input => " << date << std::endl;
            } else if (!isValidValue(value)) {
                std::cerr << "Error: not a positive number." << std::endl;
            } else {
                try {
                    double rate = getExchangeRate(date);
                    double val = stod(value);
                    double result = rate * val;
                    std::cout << date << " => " << val << " = " << result << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        } else {
            std::cerr << "Error: bad input format." << std::endl;
        }
    }
}

double BitcoinExchange::stod(const std::string& str) const {
    std::istringstream string(str);
    double value;
    string >> value;
    return value;
}
