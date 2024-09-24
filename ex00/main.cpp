/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:26:10 by ychng             #+#    #+#             */
/*   Updated: 2024/09/25 00:36:46by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "BitcoinExchange.hpp"
#include <iostream>

#include <map>
#include <fstream>
#include <sstream>


void trimSpacesAround(std::string& str)
{
	size_t first = str.find_first_not_of(" \t");
	size_t last = str.find_last_not_of(" \t");
	if (first == std::string::npos)
		str.clear();
	else
		str = str.substr(first, (last - first + 1));
}

bool isValidNumber(const std::string& str)
{
	if (str.empty())
		return false;

	bool hasDecimalPoint = false;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
		{
			if (hasDecimalPoint)
				return false; // Only one decimal point allowed
			hasDecimalPoint = true;
		}
		else if (!std::isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return false; // Found non-digit character
	}
	return true;
}

// Function to check if the date is in the format YYYY-MM-DD
bool isValidDate(const std::string& date)
{
	// Check if the date is exactly 10 characters long
	if (date.length() != 10)
		return false;

	// Check the format YYYY-MM-DD
	if (date[4] != '-' || date[7] != '-')
		return false;
	
	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);

	isValidNumber(yearStr);
	isValidNumber(monthStr);
	isValidNumber(dayStr);
	int year = atoi(yearStr.c_str());
	int month = atoi(monthStr.c_str());
	int day = atoi(dayStr.c_str());

	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;
	if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			if (day > 29) // Leap year
				return false;
		}
		else
		{
			if (day > 28) // Non-leap year
				return false;
		}
	}
	return true;
}

bool isValidValue(const std::string& value)
{
	if (!isValidNumber(value))
		return false;

	float rate = atof(value.c_str());
	return !(rate < 0 || rate > 1000);
}


std::map<std::string, std::string> parseInput(const std::string& filename)
{
	std::map<std::string, std::string> inputDB;
	std::ifstream file(filename.c_str());
	std::string line, date, value;

	if (file.is_open())
	{
		std::getline(file, line);
		while (!file.eof())	
		{
			std::getline(file, line);
			std::stringstream stream(line);
			std::getline(stream, date, '|');
			std::getline(stream, value);
			trimSpacesAround(date);
			trimSpacesAround(value);
			if (isValidDate(date) && isValidValue(value))
			{
				if (inputDB.find(date) != inputDB.end())
					inputDB[date] += "," + value; // If the date already exists, append the new value
				else
					inputDB[date] = value;
			}
		}
	}
	file.close();
	return inputDB;
}

std::map<std::string, std::string> parseCSV(const std::string& csv)
{
	std::map<std::string, std::string> csvDB;
	std::ifstream file(csv.c_str());
	std::string line, date, rate;

	if (file.is_open())
	{
		std::getline(file, line);
		while (!file.eof())
		{
			std::getline(file, line);
			std::stringstream stream(line);
			std::getline(stream, date, ',');
			std::getline(stream, rate);
			csvDB[date] = rate;
		}
	}
	file.close();
	return csvDB;
}

std::string findClosestDate(const std::map<std::string, std::string>& csvDB, const std::string& dateInput)
{
	std::string closestDate;
	for (std::map<std::string, std::string>::const_iterator it = csvDB.begin(); it != csvDB.end(); it++)
	{
		const std::string& dateCSV = it->first;
		if (dateCSV < dateInput) // Compare dates (assuming YYYY-MM-DD format)
			closestDate = dateCSV;
		else
			break ;
	}
	return closestDate;
}

void printResults(std::map<std::string, std::string> inputDB, std::map<std::string, std::string> csvDB)
{
	if (inputDB.empty() || csvDB.empty())
		return ;
	for (std::map<std::string, std::string>::const_iterator it1 = inputDB.begin(); it1 != inputDB.end(); it1++)
	{
		const std::string& dateInput = it1->first;
		const std::string& valueInput = it1->second;

		// Check if the date exists in csvDB
		std::map<std::string, std::string>::const_iterator it2 = csvDB.find(dateInput);
		const std::string& valueCSV = (it2 != csvDB.end()) ? it2->second : "";
		if (!valueCSV.empty())
		{
			// Exact match
			std::stringstream stream(valueInput);
			std::string value;
			while (std::getline(stream, value, ','))
			{
				float result = atof(value.c_str()) * atof(valueCSV.c_str());
				std::cout << dateInput << " => " << value << " = " << result << "\n";
			}
		}
		else
		{
			std::string closestDate = findClosestDate(csvDB, dateInput);
			if (!closestDate.empty())
			{
				const std::string& closestValueCSV = csvDB.at(closestDate);
				std::stringstream stream(valueInput);
				std::string value;
				while (std::getline(stream, value, ','))
				{
					float result = atof(value.c_str()) * atof(closestValueCSV.c_str());
					std::cout << dateInput << " => " << value << " = " << result << "\n";
				}
			}
		}
	}

}

void printDB(const std::map<std::string, std::string>& DB)
{
	if (DB.empty())
		return ;
	for (std::map<std::string, std::string>::const_iterator it = DB.begin(); it != DB.end(); it++)
		std::cout << "Date: " << it->first << ", Rate: " << it->second << "\n";
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Error: could not open file.\n";
		return -1;
	}
	std::map<std::string, std::string> inputDB = parseInput(argv[1]);
	std::map<std::string, std::string> csvDB = parseCSV("data.csv");
	printResults(inputDB, csvDB);
	// printDB(inputDB);
}
