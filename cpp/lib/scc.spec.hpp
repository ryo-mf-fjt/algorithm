#include <gtest/gtest.h>

#include "scc.hpp"

TEST(scc, normal) {
  int n = 4;
  vector<int> g[] = {{1, 2}, {0, 2}, {0, 1}, {}};
  EXPECT_EQ(scc(g, n), make_pair(2, vector<int>({1, 1, 1, 0})));
}
