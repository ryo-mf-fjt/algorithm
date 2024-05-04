#include <gtest/gtest.h>

#include "hld.hpp"

TEST(HLD, normal) {
  const int n = 8;
  int _p[] = {-1, 0, 0, 1, 1, 2, 4, 4};
  vector<int> t[n];
  for (int i = 1; i < n; ++i) {
    t[_p[i]].push_back(i);
    t[i].push_back(_p[i]);
  }

  HLD<n> hld;
  hld.init(t);

  auto path_len = [&](int i, int j) {
    auto path = hld.path(i, j, false);
    int s = 0;
    for (auto &p : path) {
      s += p.second - p.first;
    }
    return s;
  };

  EXPECT_EQ(path_len(3, 3), 0);
  EXPECT_EQ(path_len(3, 7), 3);
  EXPECT_EQ(path_len(3, 5), 4);
}

TEST(HLD, lca) {
  const int n = 8;
  int _p[] = {-1, 0, 0, 1, 1, 2, 4, 4};
  vector<int> t[n];
  for (int i = 1; i < n; ++i) {
    t[_p[i]].push_back(i);
    t[i].push_back(_p[i]);
  }

  HLD<n> hld;
  hld.init(t);

  EXPECT_EQ(hld.lca(3, 3), 3);
  EXPECT_EQ(hld.lca(3, 7), 1);
  EXPECT_EQ(hld.lca(3, 5), 0);
}
