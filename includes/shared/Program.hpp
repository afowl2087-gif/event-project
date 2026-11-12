#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <memory>
#include <string>
#include <vector>
#include "shared/Room.hpp"
#include "shared/Schedule.hpp"


class Program {
private:
    std::vector<Room> rooms;
    std::vector<std::unique_ptr<Schedule>> schedules;
    std::string lowerCase(const std::string& text) const;


public:
    void addRoom(const Room& room);

    const Room* findRoom(const std::string& name) const;

    bool addSchedule(std::unique_ptr<Schedule> schedule);

    bool book(int index, const std::string& clientName, int seats);

    int seatsSoldInRoom(const std::string& roomName) const;
    int getScheduleCount() const;
    bool displayByTitle(const std::string& title) const;
    void displayAll() const;
    double totalRevenue() const;
    void displayRooms() const;
    void displayBusiestRooms() const;

    std::vector<double> getPrices() const;
    std::vector<int> getAttendances() const;
    std::vector<int> getDurations() const;

};

#endif