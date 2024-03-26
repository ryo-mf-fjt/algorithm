#include <gtest/gtest.h>

#include "frac.hpp"

TEST(Frac, plus) {
  using Q = Frac<>;
  EXPECT_EQ(Q(1, 3) + Q(1, 6), Q(1, 2));
}

TEST(Frac, minus) {
  using Q = Frac<>;
  EXPECT_EQ(Q(1, 2) - Q(1, 6), Q(1, 3));
}

TEST(Frac, multiply) {
  using Q = Frac<>;
  EXPECT_EQ(Q(2, 3) * Q(3, 2), Q(1, 1));
}

TEST(Frac, divide) {
  using Q = Frac<>;
  EXPECT_EQ(Q(2, 3) / Q(2, 1), Q(1, 3));
}

TEST(Frac, greater) {
  using Q = Frac<>;
  EXPECT_EQ(Q(1, 2) > Q(1, 3), true);
}
