#include <gtest/gtest.h>

#include "auxiliary_tree.hpp"
#include "lca.hpp"

TEST(make_auxiliary_tree, normal) {
  const int n = 8;
  int _p[] = {-1, 0, 0, 1, 1, 2, 4, 4};
  vector<int> t[n];
  for (int i = 1; i < n; ++i) {
    t[_p[i]].push_back(i);
    t[i].push_back(_p[i]);
  }

  LCA<n> lca;
  lca.init(t, n);

  vector<int> x = {1, 5, 6, 7};
  vector<int> xp = make_auxiliary_tree(x, lca);

  EXPECT_EQ(x, vector<int>({0, 1, 4, 6, 7, 5}));
  EXPECT_EQ(xp, vector<int>({-1, 0, 1, 4, 4, 0}));
}
