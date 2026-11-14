#ifndef ROOM_HPP
#define ROOM_HPP
#include <string>

class Room
{
private:
    std::string name;
    int capacity;

public:
    Room(const std::string &name, int capacity);
    std::string getName() const;
    int getCapacity() const;
};

#endif