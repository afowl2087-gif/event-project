#pragma once

#include <string>
#include <vector>
#include <functional>

class Menu {
private:
    std::string m_title;
    std::vector<std::string> m_labels;
    std::vector<std::function<void()>> m_actions;

    int readChoice() const;

public:
    Menu(const std::string& title);

    void addOption(const std::string& label, std::function<void()> action);
    void display() const;
    void run();


};