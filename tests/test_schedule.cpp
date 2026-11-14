
#include <gtest/gtest.h>
#include "shared/Schedule.hpp"
#include "shared/Concert.hpp"
#include "shared/Room.hpp"
#include <memory>
#include <utility>


TEST(Schedule, BooksSeats)
{
    std::unique_ptr<Concert> concert = std::make_unique<Concert>("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");
    Room room("Studio", 100);
    Schedule schedule(std::move(concert), room, 2026, 11, 10, 18, 0, 100);

    EXPECT_TRUE(schedule.book("Marie", 20));
    EXPECT_EQ(schedule.getSeatsSold(), 20);
}

TEST(Schedule, RejectsInvalidBooking)
{
    std::unique_ptr<Concert> concert = std::make_unique<Concert>("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");
    Room room("Studio", 100);
    Schedule schedule(std::move(concert), room, 2026, 11, 10, 18, 0, 100);

    EXPECT_FALSE(schedule.book("Marie", 0));
    EXPECT_FALSE(schedule.book("Marie", -5));
}

TEST(Schedule, RejectsFullBooking)
{
    std::unique_ptr<Concert> concert = std::make_unique<Concert>("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");
    Room room("Studio", 100);
    Schedule schedule(std::move(concert), room, 2026, 11, 10, 18, 0, 100);

    EXPECT_TRUE(schedule.book("Marie", 80));
    EXPECT_FALSE(schedule.book("Marie", 30));
}


TEST(Schedule, NotSoldOut)
{
    std::unique_ptr<Concert> concert = std::make_unique<Concert>("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");
    Room room("Studio", 100);
    Schedule schedule(std::move(concert), room, 2026, 11, 10, 18, 0, 100);

    EXPECT_FALSE(schedule.isSoldOut());
}

TEST(Schedule, SoldOut)
{
    std::unique_ptr<Concert> concert = std::make_unique<Concert>("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");
    Room room("Studio", 100);
    Schedule schedule(std::move(concert), room, 2026, 11, 10, 18, 0, 100);

    EXPECT_TRUE(schedule.book("Marie", 100));
    EXPECT_TRUE(schedule.isSoldOut());
    EXPECT_EQ(schedule.getSeatsSold(), 100);
}


TEST(Schedule, DetectsCollision)
{
    std::unique_ptr<Concert> concert1 = std::make_unique<Concert>("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");
    std::unique_ptr<Concert> concert2 = std::make_unique<Concert>("Rock Night", 40.0, 90, "Rock", "Artist B", "16:00");

    Room room("Studio", 100);

    Schedule schedule1(std::move(concert1), room, 2026, 11, 10, 18, 0, 100);
    Schedule schedule2(std::move(concert2), room, 2026, 11, 10, 19, 0, 100);

    EXPECT_TRUE(schedule1.collidesWith(schedule2));
}

TEST(Schedule, NoCollisionDifferentRoom)
{
    std::unique_ptr<Concert> concert1 = std::make_unique<Concert>("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");
    std::unique_ptr<Concert> concert2 = std::make_unique<Concert>("Rock Night", 40.0, 90, "Rock", "Artist B", "16:00");

    Room room1("Studio", 100);
    Room room2("Main Hall", 200);

    Schedule schedule1(std::move(concert1), room1, 2026, 11, 10, 18, 0, 100);
    Schedule schedule2(std::move(concert2), room2, 2026, 11, 10, 19, 0, 200);

    EXPECT_FALSE(schedule1.collidesWith(schedule2));
}

TEST(Schedule, NoCollisionDifferentDate)
{
    std::unique_ptr<Concert> concert1 = std::make_unique<Concert>("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");
    std::unique_ptr<Concert> concert2 = std::make_unique<Concert>("Rock Night", 40.0, 90, "Rock", "Artist B", "16:00");

    Room room("Studio", 100);

    Schedule schedule1(std::move(concert1), room, 2026, 11, 10, 18, 0, 100);
    Schedule schedule2(std::move(concert2), room, 2026, 11, 11, 19, 0, 100);

    EXPECT_FALSE(schedule1.collidesWith(schedule2));
}

TEST(Schedule, NoCollisionBackToBack)
{
    std::unique_ptr<Concert> concert1 = std::make_unique<Concert>("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");
    std::unique_ptr<Concert> concert2 = std::make_unique<Concert>("Rock Night", 40.0, 90, "Rock", "Artist B", "16:00");

    Room room("Studio", 100);

    Schedule schedule1(std::move(concert1), room, 2026, 11, 10, 18, 0, 100);
    Schedule schedule2(std::move(concert2), room, 2026, 11, 10, 20, 0, 100);

    EXPECT_FALSE(schedule1.collidesWith(schedule2));
}
