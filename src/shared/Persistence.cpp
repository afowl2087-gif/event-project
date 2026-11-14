#include "Persistence.hpp"
#include "shared/Concert.hpp"
#include "shared/Play.hpp"
#include "shared/Screening.hpp"

void Persistence::writeString(std::ofstream& out, const std::string& s) {
    size_t n = s.size();
    out.write((char*)&n, sizeof(n));
    out.write(s.data(), n);
}

std::string Persistence::readString(std::ifstream& in) {
    size_t n;
    in.read((char*)&n, sizeof(n));
    std::string s(n, ' ');
    in.read(&s[0], n);
    return s;
}

void Persistence::writeInt(std::ofstream& out, int v) {
    out.write((char*)&v, sizeof(v));
}

int Persistence::readInt(std::ifstream& in) {
    int v;
    in.read((char*)&v, sizeof(v));
    return v;
}


void Persistence::writeEvent(std::ofstream& out, const Event& e) {
    const Concert* c = dynamic_cast<const Concert*>(&e);
    const Play* p = dynamic_cast<const Play*>(&e);
    const Screening* s = dynamic_cast<const Screening*>(&e);

    int type = 0;
    if (c) type = 1;
    else if (p) type = 2;
    else if (s) type = 3;

    writeInt(out, type);
    writeString(out, e.getTitle());
    double price = e.getPrice();
    out.write((char*)&price, sizeof(price));
    writeInt(out, e.getDuration());

    if (c) {
        writeString(out, c->getStyle());
        writeString(out, c->getLineUp());
        writeString(out, c->getSoundCheck());
    } else if (p) {
        writeString(out, p->getIntervalInfo());
    } else if (s) {
        writeString(out, s->getRating());
    }
}

std::unique_ptr<Event> Persistence::readEvent(std::ifstream& in) {
    int type = readInt(in);
    std::string title = readString(in);
    double price;
    in.read((char*)&price, sizeof(price));
    int duration = readInt(in);

    if (type == 1) {
        std::string style = readString(in);
        std::string lineUp = readString(in);
        std::string soundCheck = readString(in);
        return std::make_unique<Concert>(title, price, duration, style, lineUp, soundCheck);
    }
    if (type == 2) {
        std::string info = readString(in);
        return std::make_unique<Play>(title, price, duration, info);
    }
    std::string rating = readString(in);
    return std::make_unique<Screening>(title, price, duration, rating);
}

void Persistence::savefile(const std::string& filename, const Program& program) {
    std::ofstream out(filename, std::ios::binary);

    
    writeInt(out, (int)program.rooms.size());
    for (const Room& r : program.rooms) {
        writeString(out, r.getName());
        writeInt(out, r.getCapacity());
    }

    
    writeInt(out, (int)program.schedules.size());
    for (const std::unique_ptr<Schedule>& s : program.schedules) {
        writeEvent(out, *s->event);
        writeString(out, s->room.getName());
        writeInt(out, s->room.getCapacity());
        writeInt(out, s->year);
        writeInt(out, s->month);
        writeInt(out, s->day);
        writeInt(out, s->startHour);
        writeInt(out, s->startMinute);
        writeInt(out, s->seatsForSale);

       
        writeInt(out, (int)s->bookings.size());
        for (const Booking& b : s->bookings) {
            writeInt(out, b.getId());
            writeString(out, b.getClientName());
            writeInt(out, b.getSeats());
        }
    }
}

void Persistence::loadfile(const std::string& filename, Program& program) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return;

    program.rooms.clear();
    program.schedules.clear();

    
    int roomCount = readInt(in);
    for (int i = 0; i < roomCount; i++) {
        std::string name = readString(in);
        int capacity = readInt(in);
        program.rooms.push_back(Room(name, capacity));
    }

   
    int scheduleCount = readInt(in);
    for (int i = 0; i < scheduleCount; i++) {
        std::unique_ptr<Event> event = readEvent(in);
        std::string roomName = readString(in);
        int roomCapacity = readInt(in);
        int year = readInt(in);
        int month = readInt(in);
        int day = readInt(in);
        int startHour = readInt(in);
        int startMinute = readInt(in);
        int seatsForSale = readInt(in);

        std::unique_ptr<Schedule> s = std::make_unique<Schedule>(
            std::move(event), Room(roomName, roomCapacity),
            year, month, day, startHour, startMinute, seatsForSale);

        
        int bookingCount = readInt(in);
        for (int j = 0; j < bookingCount; j++) {
            int id = readInt(in);
            std::string clientName = readString(in);
            int seats = readInt(in);
            s->bookings.emplace_back(id, clientName, seats);
        }

        program.schedules.push_back(std::move(s));
    }
}