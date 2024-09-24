/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:21:08 by ychng             #+#    #+#             */
/*   Updated: 2024/09/24 21:26:01 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

using std::cout;

BitcoinExchange::BitcoinExchange() { cout << "Constructor Called\n"; }
BitcoinExchange::~BitcoinExchange() { cout << "Destructor Called\n"; }
BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) { (void)src; cout << "Copy Constructor Called\n"; }
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src) { if (this != &src) (void)src; cout << "Assignment Operator\n"; return *this; }

