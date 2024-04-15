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
  ImplicitTreap<5> t;
  int a = t.insert(0);
  int b = t.insert(1);
  int c = t.insert(2);
  int d = t.insert(3);
  int e = t.insert(4);

  t.erase(2);

  EXPECT_EQ(a, 0);
  EXPECT_EQ(b, 1);
  EXPECT_EQ(c, 2);
  EXPECT_EQ(d, 3);
  EXPECT_EQ(e, 4);
  EXPECT_EQ(t.debug(), vector<int>({a, b, d, e}));
}

TEST(ImplicitTreap, get) {
  ImplicitTreap<5> t;
  int a = t.insert(0);
  int b = t.insert(1);
  int c = t.insert(2);
  int d = t.insert(3);
  int e = t.insert(4);

  EXPECT_EQ(a, 0);
  EXPECT_EQ(b, 1);
  EXPECT_EQ(c, 2);
  EXPECT_EQ(d, 3);
  EXPECT_EQ(e, 4);
  EXPECT_EQ(t.get(2), c);
}
