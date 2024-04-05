#include <gtest/gtest.h>

#include "gcd.hpp"

TEST(gcd_ex, normal) {
  int x, y;
  int g = gcd_ex(6, 10, x, y);
  EXPECT_EQ(g, 2);
  EXPECT_EQ(x, 2);
  EXPECT_EQ(y, -1);
}
