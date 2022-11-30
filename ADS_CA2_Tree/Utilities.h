//https://www.geeksforgeeks.org/how-to-validate-time-in-24-hour-format-using-regular-expression/

#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
using namespace std;

/// <summary>
/// Reads a row, splits into fields (using comma delimiter) and returns a vector of vectors
/// </summary>
/// <param name="fileName">string</param>
/// <returns>Vector where each entry represents a row</returns>
vector<vector<string>> readDelimitedRows(string fileName)
{
	ifstream fin(fileName);
	if (!fin)
		throw runtime_error(fileName + " was not found! Is file in the correct sub-folder with main CPP file?");

	string rowStr;
	string field = "";
	vector<vector<string>> allRows;
	vector<string> rowFields;

	while (!fin.eof())
	{
		getline(fin, rowStr);
		bool quoteOpen = false;
		for (int i = 0; i < rowStr.length(); i++)
		{
			if (rowStr[i] == '"')
			{
				quoteOpen = !quoteOpen;
			}
			else if (!quoteOpen && rowStr[i] == ',')
			{
				rowFields.push_back(field);
				field = "";
			}
			else
			{
				field += rowStr[i];
			}
		}
		if (field != "")
		{
			rowFields.push_back(field);
		}
		field = "";

		if (rowFields.size() != 0)
			allRows.push_back(rowFields);

		rowFields.clear();
	}
	return allRows;
}

/// <summary>
/// Splits a string using a user-defined delimiter (e.g. ",")
/// </summary>
/// <param name="str">string</param>
/// <param name="delimiter">string</param>
/// <returns>Vector of strings (representing each word in parsed string)</returns>
vector<string> splitString(string str, string delimiter)
{
	vector<string> words;
	size_t pos = 0;
	std::string subString;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		words.push_back(str.substr(0, pos));
		str.erase(0, pos + delimiter.length());
	}
	words.push_back(str);

	return words;
}