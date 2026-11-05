#ifndef SCREENING_HPP
#define SCREENING_HPP
#include <string>
#include "Event.hpp"

class Screening : public Event {
    private:
     std::string rating;
     

    public:
     Screening(const std::string& title, double price, int duration, const std::string& rating);
     std::string getRating() const;
     void describe() const override;
};

#endif