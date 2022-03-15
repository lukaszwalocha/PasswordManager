#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <array>
#include <sstream>

class PasswordManager {
public:
    ~PasswordManager();
    void setEncryptionMap();
    void getPasswords();
    void printPasswords();

    void changeExistingPassword();
    void addBrandNewPassword();
    void saveExistingPasswords();

    std::pair<std::string, std::string> encryptLabelPassword(const std::string& label,
        const std::string& password);
    std::pair<std::string, std::string> decryptLabelPassword(const std::string& label,
        const std::string& password);

    void logCommunicate(std::string str);

private:
    const std::string mainPassword{ "testPassword" };
    const std::string dictionaryPath{ "D:/decryption/dictionary.txt" };
    const std::string passwordFilePath{ "D:/encryption/encryptedPasswords.txt" };
    std::unordered_map<char, std::string> encryptionMap;
    std::unordered_map<std::string, std::string> passwordsMap;
};