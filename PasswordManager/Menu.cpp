#include "Menu.h"
#include <limits>
#include <iostream>
#include <string>


Menu::Menu() {
	managerObject->setEncryptionMap();
}

void Menu::printMenuStr() {
	std::cout << this->menuStr << std::endl;
}

int Menu::getUserChoice() {
	auto choice = 0;
	std::cout << "Choose an option: ";
	std::cin >> choice;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		return getUserChoice();
	}
	std::cin.ignore(1, '\n');
	return choice;
}

void Menu::displayMenu() {
	while (isWorking) {
		printMenuStr();
		switch (getUserChoice()) {
		case 1:
			managerObject->getPasswords();
			break;
		case 2:
			managerObject->changeExistingPassword();
			break;
		case 3:
			managerObject->addBrandNewPassword();
			break;
		case 4:
			isWorking = false;
			break;
		default:
			managerObject->getPasswords();
			break;
		}
	}
}