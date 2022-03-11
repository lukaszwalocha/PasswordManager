#include <iostream>
#include <string>
#include <fstream>
#include "PasswordManager.h"



int main(){
    std::unique_ptr<PasswordManager> manager = std::make_unique<PasswordManager>();
    manager->setEncryptionMap();
    manager->getPasswords();

    return 0;
}
