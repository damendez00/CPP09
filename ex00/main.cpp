/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:34:53 by damendez          #+#    #+#             */
/*   Updated: 2025/02/03 17:25:09 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <exception>
#include <cstdlib>
#include <ctime>

#ifndef DB_FILE
# define DB_FILE "./data.csv"
#endif

void parseInput(BitcoinExchange &data, const char* inputFile)
{
        std::fstream    fs;
        std::string     line;

        fs.open(inputFile, std::fstream::in);
        if (!fs.is_open())
                throw std::logic_error("Error: could not open input file");
        while (std::getline(fs, line))
        {
                std::stringstream       ss(line);
                std::string             key;
                float                   value;

                if (line.find('|') == line.npos)
                {
                        std::cerr << "Error: Bad input on line " << line << std::endl;
                        continue;
                }
                std::getline(ss, key, '|');
		if (key.empty()) {
                        std::cerr << "Error: Bad input on line " << line << std::endl;
                        continue;
                }
                if (key == "date ")
                        continue;
                key.erase(key.end() - 1);
                try {
                    ss >> value;
                    data.check_key(key);
                } catch (std::exception &e) {
                        std::cerr << "Error: Bad input on line " << line << std::endl;
                        continue;
                }
                if (ss.fail()) {
                        std::cerr << "Error: Bad input on line " << line << std::endl;
                        continue;
                }
                if (value > 1000)
                {
                        std::cerr << "Error: Too large a number => " << value << std::endl;
                        continue;
                }
                if (value < 0)
                {
                        std::cerr << "Error: Not a positive number => " << value << std::endl;
                        continue;
                }
                std::cout << key << " => " << value <<  " = " << value * data[key] << std::endl;
        }
}

void parseDb(BitcoinExchange &data) 
{
        std::fstream    fs;
        std::string     line;

        fs.open(DB_FILE, std::fstream::in);
        if (!fs.is_open())
                throw std::logic_error("could not open database");
        while (std::getline(fs, line)) {
                data.append(line);
        }
        fs.close();        
}

int main(int argc, char *argv[])
{
        if (argc != 2)
        {
                std::cerr << "Error: not enough arguments, proper usage: ./btc <inputfile>.";
                return 1;
        }
        try {
                BitcoinExchange data;
                parseDb(data);
                parseInput(data, argv[1]);
        } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return 1;
        }
        return 0;
}
