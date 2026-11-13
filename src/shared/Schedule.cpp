#include "shared/Schedule.hpp"
#include "shared/Colors.hpp"
#include <iostream>
#include <utility>

Schedule::Schedule(std::unique_ptr<Event> event, const Room &room, int year, int month, int day, int startHour, int startMinute, int seatsForSale) : event(std::move(event)), room(room), year(year),
                                                                                                                                                     month(month),
                                                                                                                                                     day(day),
                                                                                                                                                     startHour(startHour),
                                                                                                                                                     startMinute(startMinute),
                                                                                                                                                     seatsForSale(seatsForSale) {}

bool Schedule::book(const std::string& clientName, int seats)
{

    if (clientName.empty() || seats <= 0 || seats > seatsForSale - getSeatsSold())
    {
        return false;
    }

    int bookingId = bookings.size() + 1;

    Booking newBooking(bookingId, clientName, seats);

    bookings.push_back(newBooking);

    return true;
}

bool Schedule::collidesWith(const Schedule &other) const
{
    if (room.getName() != other.room.getName())
    {
        return false;
    }
    if (year != other.year || month != other.month || day != other.day)
    {
        return false;
    }

    int start = startHour * 60 + startMinute;
    int end = start + event->getDuration();
    int otherStart = other.startHour * 60 + other.startMinute;
    int otherEnd = otherStart + other.event->getDuration();

    if (end <= otherStart || otherEnd <= start)
    {
        return false;
    }
    return true;
}

bool Schedule::isSoldOut() const
{
    if (getSeatsSold() >= seatsForSale)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool Schedule::isBefore(const Schedule &other) const
{
    if (year != other.year)
    {
        if (year < other.year)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (month != other.month)
    {
        if (month < other.month)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (day != other.day)
    {
        if (day < other.day)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (startHour != other.startHour)
    {
        if (startHour < other.startHour)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (startMinute < other.startMinute)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Schedule::displayBookings() const
{
    if (bookings.empty())
    {
        std::cout << Colors::CYAN << "  No booking yet.\n" << Colors::RESET;
        return;
    }

    for (std::size_t i = 0; i < bookings.size(); i++)
    {
        bookings[i].display();
    }
}

std::string Schedule::getTitle() const { return event->getTitle(); }

std::string Schedule::getRoomName() const { return room.getName(); }

int Schedule::getSeatsSold() const { 

    int total = 0;

    for (std::size_t i = 0; i < bookings.size(); i++)
    {
        total += bookings[i].getSeats();
    }

    return total;
}

double Schedule::getPrice() const { return event->getPrice(); }

int Schedule::getDuration() const { return event->getDuration(); }

double Schedule::getRevenue() const
{
    return getSeatsSold() * event->getPrice();
}

void Schedule::describe() const
{
    std::cout << Colors::DATE << day << "/" << month << "/" << year << "  " << startHour << ":";

    if (startMinute < 10)
    {
        std::cout << "0";
    }
    std::cout << startMinute << "  " << Colors::RESET << Colors::ROOM << room.getName() << "\n" << Colors::RESET;

    event->describe();

    std::cout << Colors::GREEN << "  " << getSeatsSold() << " / " << seatsForSale << " seats\n" << Colors::RESET;

    if (isSoldOut())
    {
        std::cout << Colors::RED << " - sold out\n" << Colors::RESET;
    }
    std::cout << "\n";
}