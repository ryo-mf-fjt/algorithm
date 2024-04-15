#include <gtest/gtest.h>

#include "dynamic_st.hpp"

TEST(DynamicSt, insert) {
  DynamicSt<int, 5> t(0, [](int a, int b) { return a + b; });

  t.insert(0, 0);
  t.insert(1, 1);
  t.insert(2, 2);
  t.insert(3, 3);
  t.insert(4, 4);

  EXPECT_EQ(t.query(0, 5), 10);
}

TEST(DynamicSt, erase) {
  DynamicSt<int, 5> t(
      0, [](int a, int b) { return a + b; }, 5, 1);
  t.erase(2);
  EXPECT_EQ(t.query(0, 5), 4);
}
