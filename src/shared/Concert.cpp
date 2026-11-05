#include "shared/Concert.hpp"
#include <iostream>

Concert::Concert(const std::string &title, double price, int duration, const std::string &style, const std::string &lineUp, const std::string &soundCheck) : Event(title, price, duration), style(style), lineUp(lineUp), soundCheck(soundCheck) {}

std::string Concert::getStyle() const { return style; }
std::string Concert::getLineUp() const { return lineUp; }
std::string Concert::getSoundCheck() const { return soundCheck; }

void Concert::describe() const
{
    std::cout << "[Concert] " << getTitle() << "  " << getPrice() << " EUR\n"
              << "  " << style << " - " << lineUp << " - "
              << getDuration() << " min - sound check " << soundCheck << "\n";
}

