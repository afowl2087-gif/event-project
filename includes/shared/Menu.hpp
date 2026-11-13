#pragma once

class Menu {
public:
    void run();

private:
    void display() const;
    int readChoice() const;
    void saveState(int screen) const;   
    int  loadState() const;             
};
