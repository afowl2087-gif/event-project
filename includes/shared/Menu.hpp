#pragma once

class Menu {
public:
    void run();

private:
    void display() const;
    int readChoice() const;
};
