#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

#include <memory>
#include "shared/Event.hpp"
#include "shared/Room.hpp"


class Schedule {
private:
    std::unique_ptr<Event> event;
    Room room;
    int year;
    int month;
    int day;
    int startHour;
    int startMinute;
    int seatsForSale;
    int seatsSold;

public:
    Schedule(std::unique_ptr<Event> event, const Room& room, int year, int month, int day, int startHour, int startMinute, int seatsForSale);
    bool book(int seats);
    bool collidesWith(const Schedule& other) const;
    bool isSoldOut() const;
    void describe() const;
};

#endif