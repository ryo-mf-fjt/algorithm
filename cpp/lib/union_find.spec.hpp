#include <gtest/gtest.h>

#include "union_find.hpp"

TEST(UnionFind, unite) {
  UnionFind<5> uf;

  uf.unite(0, 1);
  uf.unite(1, 2);
  uf.unite(2, 3);

  EXPECT_EQ(uf.same(0, 3), true);
  EXPECT_EQ(uf.same(0, 4), false);
}
