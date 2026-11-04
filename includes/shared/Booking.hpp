#pragma once

#include <string>

class Booking {
private:
    int id;
    std::string clientName;
    int seats;
    std::string state;   

public:
    Booking(int id, const std::string& clientName, int seats, const std::string& state);

    int getId() const;
    std::string getClientName() const;
    int getSeats() const;

    void setSeats(int n);

    void confirm();
    void cancel();

    std::string status() const;
    void display() const;
};