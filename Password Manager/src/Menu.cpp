#include "Menu.h"

#include <iostream>
#include <Windows.h>

using namespace std;

void Menu::menu()
{
	while (!end)
	{
		system("cls");
		cout << "1. Creating Password" << endl;
		cout << "2. Authenticating Passwords" << endl;
		cout << "3. Generate Random Encrypted Passwords" << endl;
		cout << "4. Analysis Strength" << endl;
		cout << "5. Exit" << endl;
		cout << "Please choose your prefered action (1 - 5): " << endl;
		string _select;
		getline(cin, _select);
		try 
		{
			select = stoi(_select);
			switch(select) {
			case 1:
				Encrypting();
				break;
			case 2:
				Authenticating();
				break;
			case 3:
				pwGen();
				break;
			case 4:
				decryption();
				break;
			case 5:
				end = true;
				break;
			default:
				cout << "\nIncorrect input, please re-enter.";
				Sleep(1000);
				break;
			}
		} 
		catch (...) 
		{
				cout << "\nIncorrect input, please re-enter.";
				Sleep(1000);
		}
	}
}

void Menu::Encrypting()
{
	cout << "\nPlease enter your name : ";
	getline(cin, name);
	cout << "\nPlease enter your password : ";
	getline(cin, password);
	pm.encryption(name, password);
	cout << "\nYou have successfully created your username and passowrd!\n\n";
	Sleep(1000);
}

void Menu::Authenticating()
{
	cout << "\nPlease enter your name : ";
	getline(cin, name);

	if (pm.checkuser(name))
	{
		cout << "\nPlease enter your password : ";
		getline(cin, password);
		int attempts = 3;
		while (attempts > 0)
		{
			if (pm.authentication(password)) { cout << "\nSUCCESS!\n"; break; }
			else
			{
				attempts--;
				if (attempts != 0)
				{
					cout << "\nfailure!\nYou still have " << attempts << " more attempts!\nPlease re-enter your password : ";
					getline(cin, password);
				}
				else { cout << "\nYou have failed to enter the correct password 3 times.\n"; }
			}
		}
	}
	else
	{
		cout << "\nNo User Record\n";
	}
	Sleep(1000);
}

void Menu::pwGen()
{
	pm.pwGenerate();
	Sleep(1000);
}

void Menu::decryption()
{
	pm.crack();
	Sleep(1000);
}