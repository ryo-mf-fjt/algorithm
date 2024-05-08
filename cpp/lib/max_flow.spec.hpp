#include <gtest/gtest.h>

#include "max_flow.hpp"

TEST(MaxFlow, normal) {
  struct E {
    int to, cap;
  };
  const int n = 5;
  MaxFlow<n, int> max_flow;
  vector<E> g[n];
  g[0].push_back({1, 10});
  g[0].push_back({2, 2});
  g[1].push_back({2, 6});
  g[1].push_back({3, 6});
  g[2].push_back({4, 5});
  g[3].push_back({4, 8});
  max_flow.init(g, n);
  EXPECT_EQ(max_flow.max_flow(0, 4), 11);
}
