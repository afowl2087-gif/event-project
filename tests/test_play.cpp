#include <gtest/gtest.h>
#include "shared/Play.hpp"


TEST(Play, KeepsTitle)
{
    Play play("The Chalk Circle", 14.0, 140, "after act two");

    EXPECT_EQ(play.getTitle(), "The Chalk Circle");
}

TEST(Play, KeepsPrice)
{
    Play play("The Chalk Circle", 14.0, 140, "after act two");

    EXPECT_DOUBLE_EQ(play.getPrice(), 14.0);
}

TEST(Play, KeepsDuration)
{
    Play play("The Chalk Circle", 14.0, 140, "after act two");

    EXPECT_EQ(play.getDuration(), 140);
}

TEST(Play, KeepsIntervalInfo)
{
    Play play("The Chalk Circle", 14.0, 140, "after act two");

    EXPECT_EQ(play.getIntervalInfo(), "after act two");
}
