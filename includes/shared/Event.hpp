#ifndef EVENT_HPP
#define EVENT_HPP
#include <string>

class Event
{
private:
    std::string title;
    double price;
    int duration;
    

public:
    Event(std::string title, double price, int duration);
    virtual ~Event() = default;
    virtual void describe() const = 0;
    std::string getTitle() const;
    double getPrice() const;
    int getDuration() const;
};

#endif