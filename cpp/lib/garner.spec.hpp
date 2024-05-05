#include <gtest/gtest.h>

#include "garner.hpp"
#include "mod.hpp"

TEST(garner, normal) {
  using M4 = Mod<4>;
  using M15 = Mod<15>;
  EXPECT_EQ(garner<int>(M4(1), M15(3)), 33);
}

TEST(garner, mod) {
  using M4 = Mod<4>;
  using M15 = Mod<15>;
  using M10 = Mod<10>;
  EXPECT_EQ(garner<M10>(M4(1), M15(3)), M10(3));
}
