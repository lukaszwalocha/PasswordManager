#pragma once
#include <string>
#include "PasswordManager.h"

class Menu{
	std::string menuStr = 
		"\n______PWDMANAGER______\n"
		"1.Get passwords\n"
		"2.Change existing password\n"
		"3.Add brand-new password\n"
		"4.End\n**********************";
	bool isWorking{ true };
	std::unique_ptr<PasswordManager> managerObject{ std::make_unique<PasswordManager>() };
public:
	Menu();
	~Menu() = default;
	void displayMenu();
	int getUserChoice();
	void printMenuStr();
};

