#include <gtest/gtest.h>
#include <cstdio>
#include <memory>
#include "shared/Persistence.hpp"
#include "shared/Concert.hpp"

TEST(Persistence, SaveAndLoad) {
    Program original;
    original.addRoom(Room("Salle A", 100));
    original.addSchedule(std::make_unique<Schedule>(
        std::make_unique<Concert>("Jazz", 20.0, 90, "Jazz", "Trio", "17h"),
        Room("Salle A", 100), 2026, 12, 5, 20, 0, 100));
    original.book(0, "Alice", 2);

    Persistence p;
    p.savefile("test.bin", original);

    Program loaded;
    p.loadfile("test.bin", loaded);

    EXPECT_EQ(loaded.findRoom("Salle A")->getCapacity(), 100);
    EXPECT_EQ(loaded.getScheduleCount(), 1);
    EXPECT_EQ(loaded.getTitles()[0], "Jazz");
    EXPECT_EQ(loaded.getPrices()[0], 20.0);
    EXPECT_EQ(loaded.getDurations()[0], 90);
    EXPECT_EQ(loaded.seatsSoldInRoom("Salle A"), 2);
    EXPECT_EQ(loaded.totalRevenue(), original.totalRevenue());

    std::remove("test.bin");
}