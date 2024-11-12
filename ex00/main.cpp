/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:34:53 by damendez          #+#    #+#             */
/*   Updated: 2024/11/05 15:43:21 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Invalid number of arguments: ./btc <input.txt>";
        return (1);
    }
    try
    {
        BtcExchange::btc(argv[1]);
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;   
    }
}
