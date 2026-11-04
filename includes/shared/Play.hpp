#ifndef PLAY_HPP
#define PLAY_HPP
#include <string>
#include "Event.hpp"

class Play : public Event {
    private:
     std::string intervalInfo;
     

    public:
     Play(const std::string& title, double price, int duration, const std::string& intervalInfo);
     void describe() const override;
};

#endif