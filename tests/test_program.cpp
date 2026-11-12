#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "shared/Concert.hpp"
#include "shared/Program.hpp"


static std::unique_ptr<Schedule> makeSchedule(const std::string& title, const Room& room,
                                              int day, int hour, int seatsForSale)
{
    return std::unique_ptr<Schedule>(new Schedule(
        std::unique_ptr<Event>(new Concert(title, 10.0, 100, "jazz", "Band", "18:00")),
        room, 2026, 10, day, hour, 0, seatsForSale));
}

TEST(Program, Empty)
{
    Program program;
    EXPECT_EQ(program.getScheduleCount(), 0);
}

TEST(Program, FindRoom)
{
    Program program;
    program.addRoom(Room("Studio", 120));

    const Room* room = program.findRoom("Studio");
    ASSERT_TRUE(room != nullptr);
    EXPECT_EQ(room->getCapacity(), 120);
}

TEST(Program, FindRoomCase)
{
    Program program;
    program.addRoom(Room("Main hall", 400));

    EXPECT_TRUE(program.findRoom("main HALL") != nullptr);
}

TEST(Program, UnknownRoom)
{
    Program program;
    EXPECT_TRUE(program.findRoom("Nowhere") == nullptr);
}

TEST(Program, DuplicateRoom)
{
    Program program;
    program.addRoom(Room("Studio", 120));
    program.addRoom(Room("studio", 50));

    const Room* room = program.findRoom("Studio");
    ASSERT_TRUE(room != nullptr);
    EXPECT_EQ(room->getCapacity(), 120);
}

TEST(Program, NoCollision)
{
    Program program;
    Room hall("Main hall", 400);

    EXPECT_TRUE(program.addSchedule(makeSchedule("A", hall, 3, 20, 400)));
    EXPECT_TRUE(program.addSchedule(makeSchedule("B", hall, 3, 23, 400)));
    EXPECT_EQ(program.getScheduleCount(), 2);
}

TEST(Program, Collision)
{
    Program program;
    Room hall("Main hall", 400);

    EXPECT_TRUE(program.addSchedule(makeSchedule("A", hall, 3, 20, 400)));
    EXPECT_FALSE(program.addSchedule(makeSchedule("B", hall, 3, 21, 400)));
    EXPECT_EQ(program.getScheduleCount(), 1);
}

TEST(Program, OtherRoom)
{
    Program program;
    Room hall("Main hall", 400);
    Room studio("Studio", 120);

    EXPECT_TRUE(program.addSchedule(makeSchedule("A", hall, 3, 20, 400)));
    EXPECT_TRUE(program.addSchedule(makeSchedule("B", studio, 3, 20, 120)));
}

TEST(Program, NullSchedule)
{
    Program program;
    EXPECT_FALSE(program.addSchedule(std::unique_ptr<Schedule>()));
}

TEST(Program, SortedByDate)
{
    Program program;
    Room hall("Main hall", 400);

    program.addSchedule(makeSchedule("Late", hall, 5, 20, 400));
    program.addSchedule(makeSchedule("Early", hall, 3, 20, 400));

    program.book(0, "Alice", 5);

    std::vector<int> attendances = program.getAttendances();
    EXPECT_EQ(attendances[0], 5);
    EXPECT_EQ(attendances[1], 0);
}

TEST(Program, BookBadIndex)
{
    Program program;
    Room hall("Main hall", 400);
    program.addSchedule(makeSchedule("A", hall, 3, 20, 400));

    EXPECT_FALSE(program.book(-1, "Alice", 10));
    EXPECT_FALSE(program.book(1, "Alice", 10));
}

TEST(Program, BookFull)
{
    Program program;
    Room hall("Main hall", 400);
    program.addSchedule(makeSchedule("A", hall, 3, 20, 100));

    EXPECT_TRUE(program.book(0, "Alice", 100));
    EXPECT_FALSE(program.book(0, "Bob", 1));
}

TEST(Program, BookBadInput)
{
    Program program;
    Room hall("Main hall", 400);
    program.addSchedule(makeSchedule("A", hall, 3, 20, 100));

    EXPECT_FALSE(program.book(0, "", 10));
    EXPECT_FALSE(program.book(0, "Alice", 0));
}

TEST(Program, Revenue)
{
    Program program;
    Room hall("Main hall", 400);
    program.addSchedule(makeSchedule("A", hall, 3, 20, 400));
    program.addSchedule(makeSchedule("B", hall, 3, 23, 400));

    program.book(0, "Alice", 5);
    program.book(1, "Bob", 3);

    EXPECT_DOUBLE_EQ(program.totalRevenue(), 80.0);
}

TEST(Program, FindTitle)
{
    Program program;
    Room hall("Main hall", 400);
    program.addSchedule(makeSchedule("Malandain Trio", hall, 3, 20, 400));

    EXPECT_TRUE(program.displayByTitle("malandain TRIO"));
    EXPECT_FALSE(program.displayByTitle("Unknown"));
}

TEST(Program, Lists)
{
    Program program;
    Room hall("Main hall", 400);
    program.addSchedule(makeSchedule("A", hall, 3, 20, 400));
    program.addSchedule(makeSchedule("B", hall, 3, 23, 400));
    program.book(0, "Alice", 5);
    program.book(1, "Bob", 3);

    EXPECT_EQ(program.getPrices().size(), 2u);
    EXPECT_EQ(program.getDurations().size(), 2u);

    std::vector<int> attendances = program.getAttendances();
    ASSERT_EQ(attendances.size(), 2u);
    EXPECT_EQ(attendances[0], 5);
    EXPECT_EQ(attendances[1], 3);
}