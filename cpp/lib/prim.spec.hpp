#include <gtest/gtest.h>

#include "prim.hpp"

TEST(prim, normal) {
  struct E {
    int to, cost;
  };
  vector<E> g[] = {{{1, 1}, {2, 2}}, {{0, 1}, {2, 0}}, {{0, 2}, {1, 0}}, {}};

  bool used[] = {false, false, false, false};
  int c = prim(g, used, 0);

  EXPECT_EQ(c, 1);
  EXPECT_EQ(vector<bool>(used, used + 4),
            vector<bool>({true, true, true, false}));
}
