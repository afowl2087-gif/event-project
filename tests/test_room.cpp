#include <gtest/gtest.h>
#include "shared/Room.hpp"

TEST(Room, KeepsName)
{
    Room room("Studio", 120);
    EXPECT_EQ(room.getName(), "Studio");
}

TEST(Room, KeepsCapacity)
{
    Room room("Studio", 120);
    EXPECT_EQ(room.getCapacity(), 120);
}