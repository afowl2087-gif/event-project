#include "shared/Program.hpp"
#include "shared/Colors.hpp"
#include <iostream>
#include <utility>

std::string Program::lowerCase(const std::string& text) const
{
    std::string result = text;

    for (std::size_t i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] - 'A' + 'a';
        }
    }

    return result;
}

void Program::addRoom(const Room& room)
{
    if (findRoom(room.getName()) != nullptr) {
        return;
    }

    rooms.push_back(room);
}

const Room* Program::findRoom(const std::string& name) const
{
    for (std::size_t i = 0; i < rooms.size(); i++) {
        if (lowerCase(rooms[i].getName()) == lowerCase(name)) {
            return &rooms[i];
        }
    }
    return nullptr;
}

bool Program::addSchedule(std::unique_ptr<Schedule> schedule)
{
    if(schedule == nullptr){
        return false;
    }

    for (std::size_t i = 0; i < schedules.size(); i++) {
        if (schedules[i]->collidesWith(*schedule)) {
            return false;
        }
    }

    schedules.push_back(std::move(schedule));

    int position = getScheduleCount() - 1;
    while (position > 0 && schedules[position]->isBefore(*schedules[position - 1])) {
        std::unique_ptr<Schedule> temp = std::move(schedules[position]);
        schedules[position] = std::move(schedules[position - 1]);
        schedules[position - 1] = std::move(temp);
        position--;
    }
    return true;
}

bool Program::book(int index, const std::string& clientName, int seats)
{
    if (index < 0 || index >= getScheduleCount()) {
        return false;
    }
    return schedules[index]->book(clientName, seats);
}

int Program::getScheduleCount() const
{
    return schedules.size();
}

bool Program::displayByTitle(const std::string& title) const
{
    for (std::size_t i = 0; i < schedules.size(); i++) {
        if (lowerCase(schedules[i]->getTitle()) == lowerCase(title)) {
            schedules[i]->describe();
            return true;
        }
    }
    return false;
}

void Program::displayAll() const
{
    for (std::size_t i = 0; i < schedules.size(); i++) {
        std::cout << (i + 1) << ". ";
        schedules[i]->describe();
        std::cout << "\n----------------------------------------\n";
    }
}

double Program::totalRevenue() const
{
    double total = 0.0;
    for (std::size_t i = 0; i < schedules.size(); i++) {
        total += schedules[i]->getRevenue();
    }
    return total;
}

int Program::seatsSoldInRoom(const std::string& roomName) const
{
    int total = 0;
    for (std::size_t i = 0; i < schedules.size(); i++) {
        if (schedules[i]->getRoomName() == roomName) {
            total += schedules[i]->getSeatsSold();
        }
    }
    return total;
}

void Program::displayRooms() const
{
    if (rooms.empty()) {
        std::cout << "  No room yet.\n";
        return;
    }
    for (std::size_t i = 0; i < rooms.size(); i++) {
        std::cout << Colors::ROOM << "  " << rooms[i].getName() << Colors::RESET << " (" << rooms[i].getCapacity() << " seats)\n";
    }
}

void Program::displayBusiestRooms() const
{
    int maxSeats = 0;
    for (std::size_t i = 0; i < rooms.size(); i++) {
        int total = seatsSoldInRoom(rooms[i].getName());
        if (total > maxSeats) {
            maxSeats = total;
        }
    }

    if (maxSeats == 0) {
        std::cout << "No seats sold yet.\n";
        return;
    }
    for (std::size_t i = 0; i < rooms.size(); i++) {
        if (seatsSoldInRoom(rooms[i].getName()) == maxSeats) {
            std::cout << rooms[i].getName() << " : " << Colors::RED << maxSeats << " seats sold\n" << Colors::RESET;
        }
    }
}

bool Program::displayBookings(int index) const
{
    if (index < 0 || index >= getScheduleCount())
    {
        return false;
    }

    schedules[index]->describe();
    schedules[index]->displayBookings();
    return true;
}

std::vector<std::string> Program::getTitles() const
{
    std::vector<std::string> titles;
    for (std::size_t i = 0; i < schedules.size(); i++)
    {
        titles.push_back(schedules[i]->getTitle());
    }
    return titles;
}

std::vector<double> Program::getPrices() const
{
    std::vector<double> prices;
    for (std::size_t i = 0; i < schedules.size(); i++) {
        prices.push_back(schedules[i]->getPrice());
    }
    return prices;
}

std::vector<int> Program::getAttendances() const
{
    std::vector<int> attendances;
    for (std::size_t i = 0; i < schedules.size(); i++) {
        attendances.push_back(schedules[i]->getSeatsSold());
    }
    return attendances;
}

std::vector<int> Program::getDurations() const
{
    std::vector<int> durations;
    for (std::size_t i = 0; i < schedules.size(); i++) {
        durations.push_back(schedules[i]->getDuration());
    }
    return durations;
}