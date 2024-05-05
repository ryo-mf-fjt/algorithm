#include <gtest/gtest.h>

#include "debug.hpp"
#include "dynamic_st.hpp"

TEST(DynamicSt, insert) {
  DynamicSt<int, 5> t(0, plus<int>());

  t.insert(0, 0);
  t.insert(1, 1);
  t.insert(2, 2);
  t.insert(3, 3);
  t.insert(4, 4);

  EXPECT_EQ(t.query(0, 5), 10);
}

TEST(DynamicSt, erase) {
  DynamicSt<int, 5> t(0, plus<int>(), 5, 1);
  t.erase(2);
  EXPECT_EQ(t.query(0, 5), 4);
}

TEST(DynamicSt, random_erase_insert) {
  const int n = 100;
  const int q = 1000;
  DynamicSt<int, n + q> t(0, plus<int>(), n);
  vector<int> x(n);

  random_device seed_gen;
  mt19937 engine(seed_gen());

  rep(i, q) {
    int p = engine() % n;
    int v = engine();
    t.erase(p);
    t.insert(p, v);
    x[p] = v;
    EXPECT_EQ(t.debug(), x);
  }
}
