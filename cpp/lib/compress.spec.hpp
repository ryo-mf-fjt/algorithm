#include <gtest/gtest.h>

#include "compress.hpp"

TEST(compress, normal) {
  vector<int> x = {2, 4, 3, 1};
  vector<pair<int, int>> correspondence = compress(x.begin(), 4);
  EXPECT_EQ(x, vector<int>({1, 3, 2, 0}));
  EXPECT_EQ(correspondence,
            (vector<pair<int, int>>({{1, 3}, {2, 0}, {3, 2}, {4, 1}})));
}
