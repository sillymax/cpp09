/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:25:33 by ychng             #+#    #+#             */
/*   Updated: 2024/09/24 02:04:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

using std::cout;

PmergeMe::PmergeMe() { std::cout << "Default Constructor called\n"; }
PmergeMe::~PmergeMe() { std::cout << "Destructor called\n"; }
PmergeMe::PmergeMe(const PmergeMe& src) { (void)src; std::cout << "Copy Constructor called\n"; }
PmergeMe& PmergeMe::operator=(const PmergeMe& src) { if (this != &src) (void)src; std::cout << "Assignment Operator called\n"; return *this; }
