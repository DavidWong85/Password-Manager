#pragma once
#include "Password Generator.h"

#include <string>
#include <memory>
#include <map>
#include <vector>

using namespace std;

class Password_Manager
{
private:
	string name, password, authpw;
	size_t found;
	unique_ptr<Password_Generactor> pg;
	multimap<string, int> keymap;
	bool getChar = false;
public:
	inline void CC(string& password);
	void encryption(const string& name, string& password);
	bool checkuser(const string& name);
	bool authentication(string& password);
	void pwGenerate();
	inline void createMap();
	void crack();
};