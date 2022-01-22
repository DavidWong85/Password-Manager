#pragma once
#include "Password Manager.h"

#include <string>
#include <memory>

using namespace std;

class Menu
{
private:
	bool end = false;
	int select;
	string name, password;
	Password_Manager pm;
public:
	void menu();
	inline void Encrypting();
	inline void Authenticating();
	inline void pwGen();
	inline void decryption();
};