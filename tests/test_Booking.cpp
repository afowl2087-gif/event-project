#include <gtest/gtest.h>
#include "Booking.hpp"

TEST(BookingTest, Getters) {
    Booking b(1, "Alice", 3);
    EXPECT_EQ(b.getId(), 1);
    EXPECT_EQ(b.getClientName(), "Alice");
    EXPECT_EQ(b.getSeats(), 3);
}

TEST(BookingTest, AnotherBooking) {
    Booking b(2, "Bob", 1);
    EXPECT_EQ(b.getId(), 2);
    EXPECT_EQ(b.getClientName(), "Bob");
    EXPECT_EQ(b.getSeats(), 1);
}