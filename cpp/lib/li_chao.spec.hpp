#include <gtest/gtest.h>

#include "li_chao.hpp"

TEST(LiChao, normal) {
  const int n = 5;
  LiChao<int, n> lc(100);
  EXPECT_EQ(lc.debug(n), vector<int>({100, 100, 100, 100, 100}));
  lc.add(1, 4, [](int i) { return i * 5 + 1; });
  EXPECT_EQ(lc.debug(n), vector<int>({100, 6, 11, 16, 100}));
  lc.add(0, 5, [](int i) { return -i * 2 + 10; });
  EXPECT_EQ(lc.debug(n), vector<int>({10, 6, 6, 4, 2}));
}
