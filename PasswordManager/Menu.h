#pragma once
#include <string>

class Menu{
	std::string menuStr = 
		"______PWDMANAGER______\n"
		"1.Get passwords\n"
		"2.Change existing password\n"
		"3.Add brand-new password\n"
		"4.End\n**********************";
	bool isWorking{ true };
public:
	void displayMenu();
};

