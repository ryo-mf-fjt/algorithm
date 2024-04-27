#include <gtest/gtest.h>

#include "dynamic_bit_vec.hpp"

TEST(DynamicBitVec, random_erase_insert) {
  const int n = 100;
  const int q = 1000;
  DynamicBitVec<n + q> b;
  vector<int> x(n);
  b.init(x.begin(), x.end());

  random_device seed_gen;
  mt19937 engine(seed_gen());

  rep(i, q) {
    int p = engine() % n;
    int v = engine() % 2;
    b.erase(p);
    b.insert(p, v);
    x[p] = v;
    EXPECT_EQ(b.debug(), x);
  }
}
