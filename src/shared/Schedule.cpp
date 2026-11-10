#include "shared/Schedule.hpp"
#include <iostream>
#include <utility>

Schedule::Schedule(std::unique_ptr<Event> event, const Room& room, int year, int month, int day, int startHour, int startMinute, int seatsForSale) : event(std::move(event)), room(room), year(year),
      month(month),
      day(day),
      startHour(startHour),
      startMinute(startMinute),
      seatsForSale(seatsForSale),
      seatsSold(0) {}

bool Schedule::book(int seats)
{
    if (seats <= 0 || seatsSold + seats > seatsForSale) {
        return false;
    }
    seatsSold += seats;
    return true;
}

bool Schedule::collidesWith(const Schedule& other) const
{
    if (room.getName() != other.room.getName()) {
        return false;
    }
    if (year != other.year || month != other.month || day != other.day) {
        return false;
    }

    int start = startHour * 60 + startMinute;
    int end = start + event->getDuration();
    int otherStart = other.startHour * 60 + other.startMinute;
    int otherEnd = otherStart + other.event->getDuration();

    if (end <= otherStart || otherEnd <= start) {
        return false;
    }
    return true;
}

bool Schedule::isSoldOut() const
{
    return seatsSold >= seatsForSale;
}

void Schedule::describe() const
{
    std::cout << day << "/" << month << "/" << year << "  " << startHour << ":";
    
    if (startMinute < 10) {
        std::cout << "0";
    }
    std::cout << startMinute << "  " << room.getName() << "\n";

    event->describe();

    std::cout << "  " << seatsSold << " / " << seatsForSale << " seats";
    
    if (isSoldOut()) {
        std::cout << " - sold out";
    }
    std::cout << "\n";
}