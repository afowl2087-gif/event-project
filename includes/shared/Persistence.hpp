
#pragma once
#include <string>
#include <vector>
#include <fstream>

struct Customer {
    std::string name;
    std::string event;
    std::string seats;
    int id;
};

class Save {
private:
    void writeString(std::ofstream& out, const std::string& s);
    std::string readString(std::ifstream& in);
public:
    void savefile(const std::string& filename);
    void loadfile(const std::string& filename);

    std::vector<Customer> customers;


};