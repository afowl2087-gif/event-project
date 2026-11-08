#include "Booking.hpp"
#include <iostream>
#include <stdexcept>

Booking::Booking(int id, const std::string& clientName, int seats)
    : id(id), clientName(clientName), seats(seats)
{
    if (seats <= 0)
        throw std::invalid_argument("Une réservation doit être d'au moins un siège");
    if (clientName.empty())
        throw std::invalid_argument("Le nom du client ne peut pas être vide");
}

int Booking::getId() const { return id; }
std::string Booking::getClientName() const { return clientName; }
int Booking::getSeats() const { return seats; }

void Booking::display() const {
    std::cout << "Réservation #" << id
              << " | " << clientName
              << " | " << seats << " siège(s)\n";
}