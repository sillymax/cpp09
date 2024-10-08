/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:44:51 by ychng             #+#    #+#             */
/*   Updated: 2024/09/26 13:45:52 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

using std::cout;

RPN::RPN() { cout << "Constructor called\n"; }
RPN::~RPN() { cout << "Destructor called\n"; }
RPN::RPN(const RPN& src) { (void)src; cout << "Copy Constructor called\n"; }
RPN& RPN::operator=(const RPN& src) { if (this != &src) (void)src; cout << "Copy Constructor called\n"; return *this; }
