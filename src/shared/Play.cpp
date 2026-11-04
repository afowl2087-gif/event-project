#include "shared/Play.hpp"
#include <iostream>

Play::Play(const std::string &title, double price, int duration, const std::string &intervalInfo) : Event(title, price, duration), intervalInfo(intervalInfo) {}

void Play::describe() const
{
    std::cout << "[Play] " << getTitle() << "  " << getPrice() << " EUR\n"
              << "  " << getDuration() << " min, interval " << intervalInfo << "\n";
}