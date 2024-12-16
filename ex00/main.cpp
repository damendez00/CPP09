/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:34:53 by damendez          #+#    #+#             */
/*   Updated: 2024/12/16 17:45:58 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void    processInput(const std::string& fileName, const std::map<std::string, float>& db) {

    // open input file
    std::ifstream input(fileName);
    if (!input.is_open())
        throw std::runtime_error("Unable to open input file.");

    // parse and trim each line
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream stream(line);
        std::string date, valueStr;    
        
        // check for invalid date/value
        std::getline(line, date, '|');
        

        // find closest(greater) date

        // calculate exchange rate and give expected output
    }


}

void    loadDb(const std::string& fileName, const std::map<std::string, float>& db) {

    // open input file
    std::ifstream inputDb(fileName);
    if (!inputDb.is_open())
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
        valueStr = trim(valueStr);

        if (isValidDate(date) && isValidValue(valueStr))
            db[date] = std::stof(valueStr);
    }
}

int main(int argc, char *argv[]) {
    
    try {
        // Check if valid argc
        if (argc != 2)
            throw std::logic_error("Usage: ./btc <input file> ...");
        
        // Load the Bitcoin database
        std::map<std::string, float> db;
        loadDb("data.csv", db);
        
        // Process input file
        processInput(argv[1], db);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}