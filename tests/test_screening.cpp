#include <gtest/gtest.h>
#include "shared/Screening.hpp"

TEST(Screening, KeepsTitle)
{
    Screening screening("Wild nights", 7.50, 112, "not recommended under 12");

    EXPECT_EQ(screening.getTitle(), "Wild nights");
}

TEST(Screening, KeepsPrice)
{
    Screening screening("Wild nights", 7.50, 112, "not recommended under 12");

    EXPECT_DOUBLE_EQ(screening.getPrice(), 7.50);
}

TEST(Screening, KeepsDuration)
{
    Screening screening("Wild nights", 7.50, 112, "not recommended under 12");

    EXPECT_EQ(screening.getDuration(), 112);
}

TEST(Screening, KeepsRating)
{
    Screening screening("Wild nights", 7.50, 112, "not recommended under 12");

    EXPECT_EQ(screening.getRating(), "not recommended under 12");
}