#include <iostream>
#include <string>
#include <fstream>
#include "PasswordManager.h"
#include "Menu.h"



int main(){
    std::unique_ptr<Menu> menuObject{ std::make_unique<Menu>() };
    menuObject->displayMenu();

    return 0;
}
