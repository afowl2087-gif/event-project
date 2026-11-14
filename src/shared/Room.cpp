#include "shared/Room.hpp"

Room::Room(const std::string &name, int capacity) : name(name), capacity(capacity) {}

std::string Room::getName() const { return name; }
int Room::getCapacity() const { return capacity; }

