#include "shared/Screening.hpp"
#include <iostream>

Screening::Screening(const std::string &title, double price, int duration, const std::string &rating) : Event(title, price, duration), rating(rating) {}

std::string Screening::getRating() const { return rating; }

void Screening::describe() const
{
    std::cout << "[Screening] " << getTitle() << "  " << getPrice() << " EUR\n"
              << "  " << getDuration() << " min - " << rating << "\n";
}