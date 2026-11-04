#pragma once

#include <string>

class Admin {
private:
    std::string login;
    std::string Password;
    bool connected;

public:
    Admin(const std::string& login, const std::string& Password);

    std::string getLogin() const;
    bool isConnected() const;

    bool logIn(const std::string& Password);
    void logOut();
};