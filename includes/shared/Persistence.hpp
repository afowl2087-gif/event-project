#pragma once
#include <string>
#include <memory>
#include <fstream>
#include "Program.hpp"

class Persistence {
private:
    void writeString(std::ofstream& out, const std::string& s);
    std::string readString(std::ifstream& in);
    void writeInt(std::ofstream& out, int v);
    int readInt(std::ifstream& in);
    void writeEvent(std::ofstream& out, const Event& e);
    std::unique_ptr<Event> readEvent(std::ifstream& in);
public:
    void savefile(const std::string& filename, const Program& program);
    void loadfile(const std::string& filename, Program& program);
};