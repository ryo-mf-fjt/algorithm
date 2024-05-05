#include <gtest/gtest.h>

#include "gcd.hpp"
#include "mod.hpp"

TEST(gcd_ex, normal) {
  int x, y;
  int g = gcd_ex(6, 10, x, y);
  EXPECT_EQ(g, 2);
  EXPECT_EQ(x, 2);
  EXPECT_EQ(y, -1);
}

TEST(inv_mod_m, normal) {
  using M = Mod<6>;
  EXPECT_EQ(inv_mod_m(M(5)), M(5));
}
