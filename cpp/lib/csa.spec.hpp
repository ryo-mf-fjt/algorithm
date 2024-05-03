#include <gtest/gtest.h>

#include "csa.hpp"

TEST(make_csa, normal) {
  char s[] = "abracadabra";
  EXPECT_EQ(make_csa(s, 12),
            vector<int>({11, 10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2}));
}

TEST(make_csa, one) {
  char s[] = "";
  EXPECT_EQ(make_csa(s, 1), vector<int>({0}));
}

TEST(make_csa, zero) {
  char s[] = {};
  EXPECT_EQ(make_csa(s, 0), vector<int>({}));
}
