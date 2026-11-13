#include "shared/Concert.hpp"
#include "shared/Colors.hpp"
#include <iostream>

Concert::Concert(const std::string &title, double price, int duration, const std::string &style, const std::string &lineUp, const std::string &soundCheck) : Event(title, price, duration), style(style), lineUp(lineUp), soundCheck(soundCheck) {}

std::string Concert::getStyle() const { return style; }
std::string Concert::getLineUp() const { return lineUp; }
std::string Concert::getSoundCheck() const { return soundCheck; }

void Concert::describe() const
{
    std::cout << Colors::EVENT << "[Concert] " << Colors::RESET << getTitle() << "  "  << Colors::PRICE << getPrice() << " EUR\n" << Colors::RESET
              << Colors::GRAY << "  " << style << " - " << lineUp << " - "
              << getDuration() << " min - sound check " << soundCheck << "\n" << Colors::RESET;
}

