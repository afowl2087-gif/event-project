#include "shared/Screening.hpp"
#include "shared/Colors.hpp"
#include <iostream>

Screening::Screening(const std::string &title, double price, int duration, const std::string &rating) : Event(title, price, duration), rating(rating) {}

std::string Screening::getRating() const { return rating; }

void Screening::describe() const
{
    std::cout << Colors::EVENT << "[Screening] " << Colors::RESET << getTitle() << "  " << Colors::PRICE << getPrice() << " EUR\n" << Colors::RESET
              << Colors::GRAY << "  " << getDuration() << " min - " << rating << "\n" << Colors::RESET;
}