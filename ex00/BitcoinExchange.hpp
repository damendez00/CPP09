/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:54:47 by damendez          #+#    #+#             */
/*   Updated: 2024/11/04 17:40:09 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>
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
        static bool getBTC(const std::map<std::string, float> &data, std::string file);
        static void parseFileLine(std::string data, float value);
        static void parseDate(std::string date);
        static void printCSV(const std::map<std::string, float> &data);

    public:
        static void btc(std::string argv);
};
