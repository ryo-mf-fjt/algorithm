#include <gtest/gtest.h>

#include "dijkstra.hpp"

TEST(dijkstra, normal) {
  struct E {
    int to, cost;
  };
  int n = 5;
  vector<E> g[] = {{{1, 1}, {2, 2}}, {{3, 3}}, {{3, 3}}, {}, {}};

  EXPECT_EQ(dijkstra(g, n, 0), vector<int>({0, 1, 2, 4, -1}));
}
