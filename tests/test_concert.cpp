#include <gtest/gtest.h>
#include "shared/Concert.hpp"


TEST(Concert, KeepsTitle)
{
    Concert concert("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");

    EXPECT_EQ(concert.getTitle(), "Jazz Night");
}

TEST(Concert, KeepsPrice)
{
    Concert concert("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");

    EXPECT_DOUBLE_EQ(concert.getPrice(), 35.0);
}

TEST(Concert, KeepsDuration)
{
    Concert concert("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");

    EXPECT_EQ(concert.getDuration(), 120);
}

TEST(Concert, KeepsStyle)
{
    Concert concert("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");

    EXPECT_EQ(concert.getStyle(), "Jazz");
}

TEST(Concert, KeepsLineUp)
{
    Concert concert("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");

    EXPECT_EQ(concert.getLineUp(), "Artist A");
}

TEST(Concert, KeepsSoundCheck)
{
    Concert concert("Jazz Night", 35.0, 120, "Jazz", "Artist A", "17:00");

    EXPECT_EQ(concert.getSoundCheck(), "17:00");
}