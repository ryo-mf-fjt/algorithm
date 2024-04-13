#include <gtest/gtest.h>

#include "bit_vec.hpp"

TEST(BitVec, get) {
  const int n = 1000;
  vector<int> x(n);
  rep(i, n) { x[i] = i & 1; }

  BitVec<n> bit_vec(x.begin(), x.end());

  EXPECT_EQ(bit_vec.get(500), 0);
  EXPECT_EQ(bit_vec.get(999), 1);
}

TEST(BitVec, sum) {
  const int n = 1000;
  vector<int> x(n);
  rep(i, n) { x[i] = i & 1; }

  BitVec<n> bit_vec(x.begin(), x.end());

  EXPECT_EQ(bit_vec.sum(501), 250);
  EXPECT_EQ(bit_vec.sum(1000), 500);
}
