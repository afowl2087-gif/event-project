#ifndef COLORS_HPP
#define COLORS_HPP
#include <string>

namespace Colors {

    const std::string GREEN = "\033[32m";
    const std::string RED = "\033[31m";
    const std::string DATE = "\033[33m";
    const std::string EVENT = "\033[34m";
    const std::string PRICE = "\033[38;5;208m";
    const std::string TITLE = "\033[36m";
    const std::string BROWSE = "\033[38;5;141m";
    const std::string ADMIN = "\033[93m";
    const std::string STATISTICS = "\033[92m";
    const std::string BOOKING = "\033[38;5;211m";
    const std::string GRAY = "\033[90m";
    const std::string CYAN = "\033[96m";
    const std::string ROOM = "\033[95m";
    const std::string RESET = "\033[0m";
}

#endif