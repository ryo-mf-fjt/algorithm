#include <gtest/gtest.h>

#include "sa.hpp"

TEST(sa, normal) {
  char s[] = "abracadabra";
  EXPECT_EQ(sa(s, 11), vector<int>({10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2}));
}

TEST(sa, one) {
  char s[] = "a";
  EXPECT_EQ(sa(s, 1), vector<int>({0}));
}

TEST(sa, zero) {
  char s[] = "";
  EXPECT_EQ(sa(s, 0), vector<int>({}));
}
