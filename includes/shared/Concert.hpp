#ifndef CONCERT_HPP
#define CONCERT_HPP
#include <string>
#include "Event.hpp"

class Concert : public Event {
    private:
     std::string style;
     std::string lineUp;
     std::string soundCheck;
     

    public:
     Concert(const std::string& title, double price, int duration, const std::string& style, const std::string& lineUp, const std::string& soundCheck);
     void describe() const override;
};

#endif