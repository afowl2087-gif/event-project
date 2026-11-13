#include "shared/Booking.hpp"
#include "shared/Colors.hpp"
#include <iostream>
#include <stdexcept>

Booking::Booking(int id, const std::string& clientName, int seats)
    : id(id), clientName(clientName), seats(seats)
{
    if (seats <= 0)
        throw std::invalid_argument("A reservation must be for at least one seat");
    if (clientName.empty())
        throw std::invalid_argument("The customer's name can't be empty");
}

int Booking::getId() const { return id; }
std::string Booking::getClientName() const { return clientName; }
int Booking::getSeats() const { return seats; }

void Booking::display() const {
    std::cout << Colors::CYAN << "Reservation #" << id
              << " | " << clientName
              << " | " << seats << " seat(s)\n" << Colors::RESET;
}