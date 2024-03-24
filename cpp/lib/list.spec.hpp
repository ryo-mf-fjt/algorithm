#include <gtest/gtest.h>

#include "./list.hpp"

TEST(List, push_front_push_back_insert) {
  List<6> list;

  int a = list.push_front();
  int b = list.push_back();
  int c = list.insert(a);
  int d = list.push_front();
  int e = list.push_back();
  int f = list.insert(a);

  EXPECT_EQ(a, 0);
  EXPECT_EQ(b, 1);
  EXPECT_EQ(c, 2);
  EXPECT_EQ(d, 3);
  EXPECT_EQ(e, 4);
  EXPECT_EQ(f, 5);
  EXPECT_EQ(list.debug(), vector<int>({d, c, f, a, b, e}));
  EXPECT_EQ(list.size, 6);
}

TEST(List, pop_front_pop_back_erase) {
  List<5> list;
  list.push_back();
  int b = list.push_back();
  int c = list.push_back();
  int d = list.push_back();
  list.push_back();

  list.pop_front();
  list.pop_back();
  list.erase(c);

  EXPECT_EQ(list.debug(), vector<int>({b, d}));
  EXPECT_EQ(list.size, 2);
}
