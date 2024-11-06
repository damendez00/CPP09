/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:54:47 by damendez          #+#    #+#             */
/*   Updated: 2024/11/05 16:12:51 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>
#include <exception>
#include <string>

class BtcExchange
{
    private:
        BtcExchange();
        BtcExchange(const BtcExchange& rhs);
        BtcExchange& operator=(const BtcExchange& rhs);
        ~BtcExchange();

        static bool getCSV(std::map<std::string, float> &data);
        static bool getBTC(const std::map<std::string, float> &data, std::string infile);
        static void parseFileLine(std::string data, float value);
        static void parseDate(std::string date);
        static void printCSV(const std::map<std::string, float> &data);
        static float stringToFloat(const std::string &str);
        static int stringToInt(const std::string &str);

    public:
        static void btc(std::string argv);
};
