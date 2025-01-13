/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:34:53 by damendez          #+#    #+#             */
/*   Updated: 2025/01/13 10:47:13 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#ifndef DB_FILE
# define DB_FILE "./data.csv"
#endif

int main(int argc, char *argv[]) {
    std::fstream    fs;
    std::string     line;
    BitcoinExchange data;

    fs.open(DB_FILE, std::fstream::in);
    if (!fs.is_open()) {
		std::cerr << "Error: could not open database" << std::endl;
		return 1;
    }
    while (std::getline(fs, line)) {
        data.append(line); // TO-DO
    }
    fs.close();
    
    fs.open(argv[1], std::fstream::in);
        if (!fs.is_open()) {
		std::cerr << "Error: could not open database" << std::endl;
		return 1;
    }
    while (std::getline(fs, line)) {
        std::stringstream   ss(line);
        std::string         key;
        float               value;

        if (line.find('|') == line.npos) {
			std::cerr << "Error: Bad input => " << line << std::endl;
			continue;
        }
    }
}