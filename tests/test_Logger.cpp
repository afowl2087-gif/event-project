#include <gtest/gtest.h>
#include "Logger.hpp"

TEST(LoggerTest, InfoDoesNotCrash) {
    EXPECT_NO_THROW(Logger::log(Logger::Level::Info, "hello"));
}

TEST(LoggerTest, ErrorDoesNotCrash) {
    EXPECT_NO_THROW(Logger::log(Logger::Level::Error, "boom"));
}