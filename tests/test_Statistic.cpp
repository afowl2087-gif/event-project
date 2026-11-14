#include <gtest/gtest.h>
#include <stdexcept>
#include "statistics.hpp"

TEST(StatisticsTest, SmallestAndLargest) {
    Statistics<int> s;
    s.add(10);
    s.add(5);
    s.add(20);
    EXPECT_EQ(s.smallest(), 5);
    EXPECT_EQ(s.largest(), 20);
}

TEST(StatisticsTest, Average) {
    Statistics<double> s;
    s.add(10.0);
    s.add(20.0);
    EXPECT_DOUBLE_EQ(s.average(), 15.0);
}

TEST(StatisticsTest, EmptyThrows) {
    Statistics<int> s;
    EXPECT_THROW(s.smallest(), std::logic_error);
}