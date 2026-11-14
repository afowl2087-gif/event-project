
#pragma once

#include <string>

class Logger {
public:
    enum class Level { Info, Warning, Error };

    static void log(Level level, const std::string& message);
};