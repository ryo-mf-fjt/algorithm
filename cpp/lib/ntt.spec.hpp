#include <gtest/gtest.h>

#include "ntt.hpp"

TEST(NTT, conv) {
  using F = NTT<>;
  vector<int> x = {1, 2};
  vector<int> y = {3, 4};
  EXPECT_EQ(F::conv(x, y), F::V({3, 10, 8, 0}));
}
