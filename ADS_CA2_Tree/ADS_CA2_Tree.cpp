// ADS_CA2_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Utilities.h"
#include "Car.h"
#include "Date.h"
#include "Benchmark.h"
using namespace std;

void demoSimpleHash();
void demoDateHash();
void demoParseString();
void demoCSVToObject();
void demoBenchmarkVectorFindLast();

int main()
{
	cout << endl << "demoSimpleHash()..........." << endl;
	demoSimpleHash();

	cout << endl << "demoDateHash()..........." << endl;
	demoDateHash();

	cout << endl << "demoParseString()..........." << endl;
	demoParseString();

	cout << endl << "demoCSVToObject()..........." << endl;
	demoCSVToObject();

	cout << endl << "demoBenchmarkVectorFindLast()..........." << endl;
	demoBenchmarkVectorFindLast();

	return 0;
}

/*********************************** Hashing Objects ***********************************/

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

/*********************************** File IO ***********************************/

//best - supports rows of data that contain commas and parenthesis - thanks for Derek!
void demoCSVToObject()
{
	//note: data is a sub-folder under the folder with main CPP file
	string fileName = "data/data_4.csv";
	vector<vector<string>> allData = readDelimitedRows(fileName);

	for (vector<string> row : allData) {
		for (string field : row) {
			cout << field << ",";
		}
		cout << endl;
	}
}

/*********************************** String parsing ***********************************/

//useful - fails when a row of data contains a field (e.g., address) which contains commas
void demoParseString()
{
	string str = "ford, 2012, 1299.55, 25/12/2022";
	string delimiter = ",";

	vector<string> rowFromCSV = splitString(str, delimiter);

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

/*********************************** Benchmarking ***********************************/

/// <summary>
/// Search for a T in a vector of T objects
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="data"></param>
/// <param name="value"></param>
/// <returns></returns>
template <typename T>
int linearSearch(vector<T> data, T value)
{
	for (int i = 0; i < data.size(); i++)
		if (data[i] == value) return i;
	return -1;
}

/// <summary>
/// A functor that we make to test the linearSearch in a vector - we need a functor because that's what measureTime takes!
/// </summary>
class LinearStringSearchFunctor {
	vector<string> data;
	string target;
public:
	LinearStringSearchFunctor(vector<string> data, string target) : data(data), target(target) {};

	int operator()() {
		return linearSearch(data, target);
	}
};

vector<string> loadData(int N)
{
	vector<string> data;

	//load data (e.g., random strings) into a vector (this is like your tree or linked list)
	int stringLength = 4;

	for (int i = 0; i < N; i++)
		data.push_back(getRandomString(stringLength));

	return data;
}

//lets benchmark how long it takes to find the last string in a vector
//we should repeat the test below and run multiple tests on finding last string in a vector and get average run time
void demoBenchmarkVectorFindLast() {
	//number of strings in the vector (like your CSV where N=1000,10000,100000)
	int N = 1000;

	//get some data (yours would be data from CSV in a list/vector vs your BinaryTree)
	vector<string> data = loadData(N);

	//pick the last string in the structure
	string searchString = data[data.size() - 1];

	/******************************* IMPORTANT PART > *******************************/
	int numberOfTests = 100;
	double totalTestTimeInNS = 0;
	for (int i = 0; i < numberOfTests; i++)
	{
		//make up the functor
		LinearStringSearchFunctor searchFunc(data, searchString);

		//pass the functor into measureTime
		totalTestTimeInNS += measureTime(searchFunc);
	}

	//get average across all tests
	double averageSearchTimeInMS = totalTestTimeInNS / numberOfTests;

	//convert ns to ms
	averageSearchTimeInMS /= 1000;

	//see how long it takes to find the string
	cout << "Vector - Average last element search time [Nr = " << N << ",Tests = " << numberOfTests << "]: " << averageSearchTimeInMS << "ms" << endl;

	/******************************* < IMPORTANT PART *******************************/
}