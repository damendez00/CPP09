/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:34:53 by damendez          #+#    #+#             */
/*   Updated: 2024/12/22 20:13:55 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

float   myStof(const std::string& str) {
    std::istringstream string(str);
    float value;
    string >> value;
    return value;
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos ? "" : str.substr(start, end - start + 1));
}

bool    isValidValue(const std::string& valueStr) {
        float num = myStof(valueStr);
        if (num >= 0.0f && num <= 1000.0f)
            return true;
        else
            return false;
}

bool    isValidDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    return true;
}

void    processInput(const std::string& fileName, const std::map<std::string, float>& db) {

    // open input file
    std::ifstream input(fileName.c_str());
    if (!input.is_open())
        throw std::runtime_error("Unable to open input file.");

    // parse and trim each line
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream stream(line);
        std::string date, valueStr;    
        
        // check for invalid date/value
        std::getline(stream, date, '|');
        std::getline(stream, valueStr);
        date = trim(date);
        valueStr = trim(valueStr);

        if (!isValidDate(date) || !isValidValue(valueStr)) {
            std::cerr << "Error: bad input in input file => " << date << " | " << valueStr << std::endl;
            continue;
        }

        std::istringstream valueStream(valueStr);
        float value;
        valueStream >> value;
        
        // find closest(greater) date
        std::map<std::string, float>::const_iterator it = db.lower_bound(date);
        if (it == db.begin())
            it++;
        else if (it == db.end()) {
            std::cerr << "Error: no valid date found for input date " << date << std::endl;
            continue;
        }
        
        // calculate exchange rate and give expected output
        float exchangeRate = it->second;
        std::cout << date << " => " << value << " = " << value * exchangeRate << std::endl;
    }
}

void    loadDb(const std::string& fileName, std::map<std::string, float>& db) {

    // open input file
    std::ifstream inputDb(fileName.c_str());
    if (!inputDb.is_open() || fileName != "data.csv")
        throw std::runtime_error("Unable to open database.");

    // parse and trim each line
    std::string line;
    while (std::getline(inputDb, line)) {
        std::istringstream stream(line);
        std::string date, valueStr;

        std::getline(stream, date, ',');
        std::getline(stream, valueStr);

        // if date and value are valid add to db map
        date = trim(date);
        std::cout << "data.csv date = " << date;
        valueStr = trim(valueStr);
        std::cout << " | value = " << valueStr << std::endl;

        if (isValidDate(date) && isValidValue(valueStr)) {
            float value = myStof(valueStr);
            db[date] = value;
        }   
    }
}

int main(int argc, char *argv[]) {
    
    try {
        if (argc != 2)
            throw std::logic_error("Usage: ./btc <input file> ...");
        std::map<std::string, float> db;
        loadDb("data.csv", db);
        processInput(argv[1], db);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}