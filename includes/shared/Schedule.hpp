#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

#include <memory>
#include <vector>
#include "shared/Event.hpp"
#include "shared/Room.hpp"
#include "shared/Booking.hpp"


class Schedule {
private:
    std::unique_ptr<Event> event;
    std::vector<Booking> bookings;
    Room room;
    int year;
    int month;
    int day;
    int startHour;
    int startMinute;
    int seatsForSale;

public:
    Schedule(std::unique_ptr<Event> event, const Room& room, int year, int month, int day, int startHour, int startMinute, int seatsForSale);
    bool book(const std::string& clientName, int seats);
    bool collidesWith(const Schedule& other) const;
    bool isSoldOut() const;
    bool isBefore(const Schedule& other) const;
    std::string getRoomName() const;
    std::string getTitle() const;
    int getSeatsSold() const;
    double getPrice() const;
    int getDuration() const;
    double getRevenue() const;
    void describe() const;
};

#endif