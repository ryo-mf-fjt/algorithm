#include <gtest/gtest.h>

#include "sa.hpp"

TEST(make_sa, normal) {
  char s[] = "abracadabra";
  EXPECT_EQ(make_sa(s, 11), vector<int>({10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2}));
}

TEST(make_sa, one) {
  char s[] = "a";
  EXPECT_EQ(make_sa(s, 1), vector<int>({0}));
}

TEST(make_sa, zero) {
  char s[] = "";
  EXPECT_EQ(make_sa(s, 0), vector<int>({}));
}

TEST(make_lcp, normal) {
  char s[] = "abracadabra";
  vector<int> sa = make_sa(s, 11);
  EXPECT_EQ(make_lcp(s, 11, sa), vector<int>({1, 4, 1, 1, 0, 3, 0, 0, 0, 2}));
}
