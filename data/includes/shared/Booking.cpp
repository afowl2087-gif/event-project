
#include "Booking.hpp"
#include <iostream>
#include <stdexcept>

namespace {
    int nextId = 1;   
}

Booking::Booking(int id , const std::string& clientName, int seats)
    : id(Id), , clientName(clientName),
      seats(seats), state("pending")
{
    if (seats <= 0)
        throw std::invalid_argument("Une réservation doit etre d au moins un siège");
    if (clientName.empty())
        throw std::invalid_argument("Le nom du client ne peut pas être vide");
}

int Booking::getId() const {
    return id;
}


}

std::string Booking::getClientName() const {
    return clientName;
}

int Booking::getSeats() const {
    return seats;
}

void Booking::setSeats(int n) {
    if (n <= 0)
        throw std::invalid_argument("Une réservation doit etre d au moins un siège");
    seats = n;
}

void Booking::confirm() {
    if (state == "cancelled")
        throw std::logic_error("Impossible de confirmer une réservation annulée");
    state = "confirmed";
}

void Booking::cancel() {
    state = "cancelled";
}

std::string Booking::status() const {
    return state;
}

void Booking::display() const {
    std::cout << "Réservation #" << id
              << " | evenement " << eventId
              << " | " << clientName
              << " | " << seats << " siège(s)"
              << " | " << state << "\n";
}