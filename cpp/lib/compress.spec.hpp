#include <gtest/gtest.h>

#include "compress.hpp"

TEST(compress, normal) {
  vector<int> x = {2, 4, 3, 1};
  vector<int> coord = compress(x.begin(), 4);
  EXPECT_EQ(x, vector<int>({1, 3, 2, 0}));
  EXPECT_EQ(coord, vector<int>({1, 2, 3, 4}));
}
