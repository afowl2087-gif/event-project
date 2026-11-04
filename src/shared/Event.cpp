#include "shared/Event.hpp"

Event::Event(const std::string& title, double price, int duration) : title(title), price(price), duration(duration) {}

std::string Event::getTitle() const { return title; }
double Event::getPrice() const { return price; }
int Event::getDuration() const { return duration; }