// ADS_CA2_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Utilities.h"
#include "Car.h"
#include "Date.h"
using namespace std;

void demoSimpleHash();
void demoDateHash();
void demoReadFromFileToCar();

int main()
{
	cout << endl << "demoSimpleHash()..........." << endl;
	demoSimpleHash();

	cout << endl << "demoDateHash()..........." << endl;
	demoDateHash();

	cout << endl << "demoReadFromFileToCar()..........." << endl;
	demoReadFromFileToCar();

	return 0;
}

void demoSimpleHash() {
	//hasher for strings
	hash<string> hasherStr;
	string email = "john.smith@hotmail.com";
	cout << "hash[" << email << "]: " << hasherStr(email) << endl;

	//hasher for doubles
	hash<double> hasherDbl;
	double price = 123123.322;
	cout << "hash[" << price << "]: " << hasherDbl(price) << endl;

	//we can re-use a hasher
	double weight = 12345.9897;
	cout << "hash[" << weight << "]: " << hasherDbl(weight) << endl;

	//we can store the hash value using size_t (basically an unsigned int)
	size_t myHash = hasherStr("this is a hash value store in a uint");
	cout << myHash << endl;
}

void demoDateHash() {
	Date myDate(25, 12, 2022);
	cout << myDate << endl;
	cout << "hash[" << myDate << "]: " << myDate.hash() << endl;
}

void demoReadFromFileToCar()
{
	//TODO - read one line from the CSV here...

	vector<string> rowFromCSV = splitString("ford, 2012, 1299.55, 25/12/2022", ",");

	if (rowFromCSV.size() == 4)
	{
		string make = rowFromCSV[0];
		int year = stoi(rowFromCSV[1]);
		double price = stod(rowFromCSV[2]);
		vector<string> dateWords = splitString(rowFromCSV[3], "/");

		if (dateWords.size() == 3)
		{
			int date_day = stoi(dateWords[0]);
			int date_month = stoi(dateWords[1]);
			int date_year = stoi(dateWords[2]);

			Date registrationDate(date_day, date_month, date_year);
			Car myCar(make, year, price, registrationDate);

			cout << "Car: " << myCar << endl;
		}
	}
}