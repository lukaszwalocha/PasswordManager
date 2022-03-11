#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <array>
#include <sstream>

class Decryptor {
public:
    ~Decryptor();
    void setEncryptionMap();
    void getPasswords();

    void changeExistingPassword();
    void addBrandNewPassword();
    void saveExistingPasswords();

    std::pair<std::string, std::string> encryptLabelPassword(const std::string& label, 
        const std::string& password);

    void logCommunicate(std::string str);

private:
    const std::string mainPassword{ "testPassword" };
    const std::string dictionaryPath{ "D:/decryption/dictionary.txt" };
    const std::string passwordFilePath{ "D:/decryption/encryptedPasswords.txt" };
    std::unordered_map<char, std::string> encryptionMap;
    std::unordered_map<std::string, std::string> passwordsMap;
};

Decryptor::~Decryptor() {
    this->saveExistingPasswords();
}

void Decryptor::logCommunicate(std::string str) {
    std::cout << str;
}

void Decryptor::changeExistingPassword() {
    std::string labelName;
    std::getline(std::cin, labelName);

    if (this->passwordsMap.find(labelName) != passwordsMap.end()) {
        logCommunicate("Please type new password: ");
        std::string newPassword;
        std::getline(std::cin, newPassword);

        logCommunicate("Please retype new password: ");
        std::string newPasswordRetype;
        std::getline(std::cin, newPasswordRetype);

        if (newPassword == newPasswordRetype) {
            passwordsMap[labelName] = newPassword;
            logCommunicate("Password to: " + labelName + " changed successfully!\n");
        }
        else {
            logCommunicate("Passwords doesn't match! Password has not been changed.\n");
            return;
        }
    }
    else {
        logCommunicate("No such a label. Please create one first.\n");
    }
}

void Decryptor::getPasswords() {
    std::ifstream fileWithPasswords(passwordFilePath);
    std::string currentLine;

    while (std::getline(fileWithPasswords, currentLine)) {
        std::string nameBuffer;
        std::string passwordBuffer;
        const auto colonPos = currentLine.find(':');
        if (colonPos == std::string::npos) {
            logCommunicate("Passwords file not properly formatted.\n");
            return;
        }
        for (auto i = 0; i < currentLine.length(); i++) {
            if (i < colonPos) {
                nameBuffer += currentLine[i];
            }
            else if (i > colonPos) {
                passwordBuffer += currentLine[i];
            }
        }
        if (this->passwordsMap.count(nameBuffer) > 0) {
            throw std::exception("Error. No name given.");
        }
        this->passwordsMap[nameBuffer] = passwordBuffer;
    }
}

void Decryptor::setEncryptionMap() {
    std::ifstream dictionary(dictionaryPath);
    std::string currentLine;
   
    while (std::getline(dictionary, currentLine)) {
        const auto letter = currentLine.front();
        std::string symbolsBuffer;
        auto colonPos = currentLine.find(":");
        for (auto i = ++colonPos; i < currentLine.length(); i++) {
            symbolsBuffer += currentLine[i];
        }
        this->encryptionMap.insert(std::make_pair(letter, symbolsBuffer));
    }
}

void Decryptor::addBrandNewPassword() {
    std::vector<std::pair<std::string, std::string>> data{ 
        {"Please type label name for the brand-new password: ", ""}, 
        {"Please type password: ",""},
        {"Please repeat password: ", ""} };

    for (auto &element : data) {
        logCommunicate(element.first);
        std::getline(std::cin, element.second);
    }

    if (this->passwordsMap.find(data[0].first) != passwordsMap.end()) {
        logCommunicate("Given label name already exists!\n");
        return;
    }

    auto arePasswordsEqual = data[1].second == data[2].second ? true : false;
    if (!arePasswordsEqual) {
        logCommunicate("Passwords are not equal. Password has not been added to the base.");
        return;
    }
    passwordsMap[data[0].second] = data[1].second;
}

std::pair<std::string, std::string> Decryptor::encryptLabelPassword(const std::string& label, 
    const std::string& password) {

    std::string encryptedLabel, encryptedPassword;

    for (const auto& letter : label) {
        encryptedLabel += encryptionMap[letter];
    }
    for (const auto& letter : password) {
        encryptedPassword += encryptionMap[letter];
    }
    return std::make_pair(encryptedLabel, encryptedPassword);
}

void Decryptor::saveExistingPasswords() {
    std::vector<std::pair<std::string, std::string>> encryptedPasswords;
    std::stringstream stream;

    for (auto &[key, value] : passwordsMap) {
        std::pair<std::string, std::string> encryptedLabelPassword = encryptLabelPassword(key, value);
        stream << encryptedLabelPassword.first << ':' << encryptedLabelPassword.second;
    }

    std::ofstream ofs;
    ofs.open(passwordFilePath, std::ofstream::out | std::ofstream::trunc);
    ofs << stream.str();
    ofs.close();
}


int main(){

    return 0;
}
