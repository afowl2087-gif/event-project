#include "Admin.hpp"

Admin::Admin(const std::string& login, const std::string& Password)
    : login(login), Password(Password), connected(false) {}

std::string Admin::getLogin() const {
    return login;
}

bool Admin::isConnected() const {
    return connected;
}

bool Admin::logIn(const std::string& pwd) {
    if (pwd == Password)
        connected = true;
    return connected;
}

void Admin::logOut() {
    connected = false;
}