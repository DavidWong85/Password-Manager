#include "Password Generator.h"

#include <random>
#include <sstream>
#include <vector>
#include <numeric>
#include <iostream>

string Password_Generactor::randomGen(int length, int range)
{
	stringstream ss;
	string s;
	vector<int> v(255);
	vector<int> lowercase(26);
	vector<int> selected(10, 0);
	std::iota(v.begin(), v.end(), 1);
	std::iota(lowercase.begin(), lowercase.end(), 97);
	int x, y;
	switch (range)
	{
	case 1:
		for (int i = 0; i < 10; i++)
		{
			x = (rand() % lowercase.size());
			selected.at(i) = lowercase.at(x);
			lowercase.erase(lowercase.begin() + x);
		}
		for (int i = 0; i < length; i++)
		{
			x = (rand() % selected.size());
			ss << char(selected.at(x));
		}
		s = ss.str();
		return s;
		break;
	case 2:
		for (int i = 0; i < length; i++)
		{
			y = (rand() % v.size());
			ss << char(v.at(y));
			v.erase(v.begin() + y);
		}
		s = ss.str();
		return s;
		break;
	default:
		break;
	}
}