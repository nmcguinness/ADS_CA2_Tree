#pragma once
#include <iostream>
#include <vector>
using namespace std;

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