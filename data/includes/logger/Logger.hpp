#pragma once 
#include <string>
#include <ctime>
enum Log_Type{
    ERROR,
    WARNING,
    INFO,
    DEBUG,
};

class Logger {
    private:
    time_t time;
    Log_Type logerror;

    public:
    
    

}