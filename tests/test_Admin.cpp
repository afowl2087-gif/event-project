#include <gtest/gtest.h>
#include "Admin.hpp"

TEST(AdminTest, StartsDisconnected) {
    Admin a("root", "secret");
    EXPECT_FALSE(a.isConnected());
}

TEST(AdminTest, GoodPassword) {
    Admin a("root", "secret");
    EXPECT_TRUE(a.logIn("secret"));
}

TEST(AdminTest, WrongPassword) {
    Admin a("root", "secret");
    EXPECT_FALSE(a.logIn("wrong"));
}

TEST(AdminTest, LogOut) {
    Admin a("root", "secret");
    a.logIn("secret");
    a.logOut();
    EXPECT_FALSE(a.isConnected());
}