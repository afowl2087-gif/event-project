#include "persistence.hpp"

void Save::writeString(std::ofstream& out, const std::string& s) {
    size_t n = s.size();
    out.write((char*)&n, sizeof(n));
    out.write(s.data(), n);
}

std::string Save::readString(std::ifstream& in) {
    size_t n;
    in.read((char*)&n, sizeof(n));
    std::string s(n, ' ');
    in.read(&s[0], n);
    return s;
}

void Save::savefile(const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);

    size_t count = customers.size();
    out.write((char*)&count, sizeof(count));

    for (const Customer& c : customers) {
        writeString(out, c.name);
        writeString(out, c.event);
        writeString(out, c.seats);
        out.write((char*)&c.id, sizeof(c.id));
    }
}

void Save::loadfile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return;

    customers.clear();

    size_t count;
    in.read((char*)&count, sizeof(count));

    for (size_t i = 0; i < count; i++) {
        Customer c;
        c.name = readString(in);
        c.event = readString(in);
        c.seats = readString(in);
        in.read((char*)&c.id, sizeof(c.id));
        customers.push_back(c);
    }
}