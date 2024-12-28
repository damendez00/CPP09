/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:54:47 by damendez          #+#    #+#             */
/*   Updated: 2024/12/28 17:46:42 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange 
{
    private:
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange &operator=(const BitcoinExchange& other);
        
        std::map<std::string, double> exchangeRates;

        void loadDatabase(const std::string& dbFile);
        double getExchangeRate(const std::string& date) const;
        bool isValidDate(const std::string& date) const;
        bool isValidValue(const std::string& value) const;
        double stod(const std::string& str) const;

    public:
        BitcoinExchange(const std::string& dbFile);
        void processInputFile(const std::string& inputFile);
        ~BitcoinExchange();
};

#endif // BITCOINEXCHANGE_HPP