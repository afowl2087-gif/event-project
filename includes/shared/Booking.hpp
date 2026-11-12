#pragma once
#include <string>

class Booking {
private:
    int id;
    const std::string& clientName;
    int seats;

public:
    Booking(int id, const std::string& clientName, int seats);

    int getId() const;
    std::string getClientName() const;
    int getSeats() const;

    void display() const;
};