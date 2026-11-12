#include <gtest/gtest.h>
#include <cstdio>
#include "Persistence.hpp"

TEST(PersistenceTest, SaveThenLoad) {
    Save s;
    s.customers.push_back({"Alice", "Concert", "A1", 1});
    s.savefile("test.bin");

    Save loaded;
    loaded.loadfile("test.bin");

    ASSERT_EQ(loaded.customers.size(), 1u);
    EXPECT_EQ(loaded.customers[0].name, "Alice");
    EXPECT_EQ(loaded.customers[0].id, 1);

    std::remove("test.bin");
}

TEST(PersistenceTest, MissingFile) {
    Save loaded;
    loaded.loadfile("inexistant.bin");
    EXPECT_TRUE(loaded.customers.empty());
}