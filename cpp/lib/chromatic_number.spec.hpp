#include <gtest/gtest.h>

#include "chromatic_number.hpp"

TEST(chromatic_number, path_graph) {
  int n = 20;
  vector<int> g[20];
  rep(i, n - 1) {
    g[i].push_back(i + 1);
    g[i + 1].push_back(i);
  }
  EXPECT_EQ(chromatic_number(g, n), 2);
}

TEST(chromatic_number, complete_graph) {
  int n = 20;
  vector<int> g[20];
  rep(i, n) {
    for (int j = i + 1; j < n; ++j) {
      g[i].push_back(j);
      g[j].push_back(i);
    }
  }
  EXPECT_EQ(chromatic_number(g, n), n);
}
