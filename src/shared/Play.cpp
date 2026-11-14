#include "shared/Play.hpp"
#include "shared/Colors.hpp"
#include <iostream>

Play::Play(const std::string &title, double price, int duration, const std::string &intervalInfo) : Event(title, price, duration), intervalInfo(intervalInfo) {}

std::string Play::getIntervalInfo() const { return intervalInfo; }

void Play::describe() const
{
    std::cout << Colors::EVENT << "[Play] " << Colors::RESET << getTitle() << "  " << Colors::PRICE << getPrice() << " EUR\n" << Colors::RESET
              << Colors::GRAY << "  " << getDuration() << " min, interval " << intervalInfo << "\n" << Colors::RESET;
}