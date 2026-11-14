
#include "Logger.hpp"

#include <iostream>

void Logger::log(Level level, const std::string& message) {
    const char* prefix = "INFO";
    if (level == Level::Warning) prefix = "WARNING";
    if (level == Level::Error)   prefix = "ERROR";

    std::cerr << "[" << prefix << "] " << message << "\n";
}