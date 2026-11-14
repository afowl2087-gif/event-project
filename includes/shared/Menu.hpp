#ifndef MENU_HPP
#define MENU_HPP

#include "shared/Program.hpp"
#include "shared/Admin.hpp"

class Menu
{
private:
    Program &program;
    Admin &admin;
    int readChoice() const;
    void browseProgram() const;
    void bookSeats();
    void adminMenu();
    void statistics() const;
    bool Cancel(const std::string &text) const;
    bool YesNo(const std::string &question) const;

public:
    Menu(Program &program, Admin &admin);
    void run();
};

#endif