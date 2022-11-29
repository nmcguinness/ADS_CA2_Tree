#pragma once
#include <ostream>
#include <string>
#include "Date.h"
using namespace std;

/// <summary>
/// Represents a row of data in a CSV file of Student records
/// </summary>
class Student {
#pragma region Fields
	string make;
	int year;
	double price;
	Date date;
#pragma endregion

public:

#pragma region Constructors
	Student(string make, int year, double price, Date date)
		: make(make), year(year), price(price), date(date)
	{
	}
#pragma endregion

#pragma region Get/Set
	string getMake() const { return this->make; }
	int getYear() const { return this->year; }
	double getPrice() const { return this->price; }
	Date getDate() const { return this->date; }
#pragma endregion

#pragma region Operators & Hash

	bool operator==(const Student& student)
	{
		return this->make == student.make
			&& this->year == student.year
			&& this->price == student.price
			&& this->date == student.date;
	}

	friend ostream& operator<<(ostream& output, Student& student) {
		output << student.make << ",";
		output << student.year << ",";
		output << student.price << ",";
		output << student.date;
		return output;
	}

	friend istream& operator>>(istream& input, Student& student) {
		string studentAsStr;
		input >> studentAsStr;

		return input;
	}

	std::size_t hash() const
	{
		//What is the size of size_t? https://www.geeksforgeeks.org/size_t-data-type-c-language/
		size_t hash = std::hash<string>()(this->make)
			+ 31 * std::hash<int>()(this->year)
			+ 57 * std::hash<double>()(this->price)
			+ 349 * date.hash();
	}

#pragma endregion
};
