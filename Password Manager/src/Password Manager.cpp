#include "Password Manager.h"

#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <numeric>
#include <iostream>
#include <chrono>

using namespace std;

void Password_Manager::CC(string& password)
{
	stringstream ss;
	string s;
	int offset = 0;
	for (int i = 0; i < password.size(); i++)
	{
		int temp = int(password.at(i) & 255) + offset;
		int step = 0;
		while (temp != 1)
		{
			if (temp % 2 == 0) { temp = temp / 2; }
			else { temp = (3 * temp) + 1; }
			step++;
		}
		ss << step;
		offset = step;
	}
	s = ss.str();
	password.resize(s.size());
	password = s;
}

void Password_Manager::encryption(const string& name, string& password)
{
	stringstream ss;
	CC(password);
	ss << name << " " << password;
	string s = ss.str();

	ofstream outFile;
	outFile.open("password.txt", ios::app);
	if (outFile.is_open())
	{
		outFile << s << "\n";
		outFile.close();
	}
	else { cout << "Unable to open file."; }
}

bool Password_Manager::checkuser(const string& name)
{
	ifstream inFile("password.txt");
	string line;

	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			found = line.find(name);
			if (found != string::npos)
			{
				authpw = line.substr(found + name.size() + 1);
				return true;
			}
		}
		inFile.close();
	}
	else { cout << "Unable to open file."; }
	return false;
}

bool Password_Manager::authentication(string& password)
{
	CC(password);
	if (authpw == password) { return true; }
	else { return false; }
}

void Password_Manager::pwGenerate()
{
	srand((unsigned)time(0));
	stringstream ss;
	string s;
	ofstream outFile;
	outFile.open("passwordtest.txt");
	if (outFile.is_open())
	{
		int range = 1;
		int length = 1;
		for (int i = 1; i <= 20000; i++)
		{
			if (i > 10000) { range = 2; }
			if (i % 100 == 0) { length++; }
			if (i == 10000) { length = 1; }
			s = pg->randomGen(length, range);
			CC(s);
			ss << s << "\n";
		}
		s = ss.str();
		outFile << s;
		outFile.close();
		cout << "\nYou have successfully generate 20000 password.";
	}
	else { cout << "Unable to open file."; }
}

void Password_Manager::createMap()
{
	vector<int> v(255);
	std::iota(v.begin(), v.end(), 1);
	string s;

	for (int i = 0; i < 255; i++)
	{
		s = char(v.at(i));
		CC(s);
		keymap.insert({ s,i + 1 });
	}
}

void Password_Manager::crack()
{
	createMap();
	ifstream file("passwordtest.txt", ios::in);
	if (file.is_open())
	{
		string line;
		int numoflines = 0;
		int size = 3;
		int previousSize = size;
		stringstream ss;
		string s;
		int failed = 0;
		vector<int> pos, step, previousPos, previousStep;
		auto duration_total = 0;
		while (getline(file, line))
		{
			auto start = chrono::high_resolution_clock::now();
			s = {};
			pos.erase(pos.begin(), pos.end());
			pos.push_back(0);
			step.erase(step.begin(), step.end());
			step.push_back(0);
			bool timeup = false;
			while (pos.back() < line.size() && timeup == false)
			{
				if (line.size() < size)
				{
					size = line.size();
				}
				getChar = false;
				ss.str(std::string());
				ss << line.substr(pos.back(), size);
				s = ss.str();
				typedef multimap<string, int>::iterator itr;
				pair<itr, itr> result = keymap.equal_range(s);
				for (itr it = result.first; it != result.second; it++)
				{
					if ((it->second - step.back()) > 0 && !getChar)
					{
						getChar = true;
						step.push_back(stoi(s));
						pos.push_back(pos.back() + size);
					}
					if (it->second == 0)
					{
						pos.pop_back();
						size = 2;
					}
				}
				if (size != 0)
				{
					if (!getChar) { size--; }
					else { size = 3; }
				}
				else
				{
					size = previousSize - 1;
					if (pos.size() != 1) { pos.pop_back(); }
					if (step.size() != 1) { step.pop_back(); }
				}
				auto elapsed = chrono::high_resolution_clock::now() - start;
				if (chrono::duration_cast<chrono::milliseconds>(elapsed).count() >= 1000)
				{
					timeup = true;
					failed++;
				}
			}
			auto duration = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start).count();
			duration_total = duration_total + duration;
			numoflines++;
			if (numoflines % 100 == 0)
			{
				auto average_duration = duration_total / 100;
				duration_total = 0;
				cout << "The Rate of success for password between " << numoflines - 99 << " to " << numoflines << " are: " << ((100 - failed) / float(100)) * 100 << "%, Average Run Time in Set: " << average_duration << " microseconds.\n" << endl;

				failed = 0;
			}
		}
	}
	else { cout << "Unable to open file."; }
}