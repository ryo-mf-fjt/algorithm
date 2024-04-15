#include <gtest/gtest.h>

#include "implicit_treap.hpp"

TEST(ImplicitTreap, insert) {
  ImplicitTreap<5> t;

  int a = t.insert(0);
  int b = t.insert(0);
  int c = t.insert(1);
  int d = t.insert(1);
  int e = t.insert(3);

  EXPECT_EQ(a, 0);
  EXPECT_EQ(b, 1);
  EXPECT_EQ(c, 2);
  EXPECT_EQ(d, 3);
  EXPECT_EQ(e, 4);
  EXPECT_EQ(t.debug(), vector<int>({b, d, c, e, a}));
}

TEST(ImplicitTreap, erase) {
  ImplicitTreap<5> t(5);
  t.erase(2);
  EXPECT_EQ(t.debug(), vector<int>({0, 1, 3, 4}));
}

TEST(ImplicitTreap, get) {
  ImplicitTreap<5> t(5);
  EXPECT_EQ(t.get(2), 2);
}
