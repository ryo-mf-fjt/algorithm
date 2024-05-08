#include <gtest/gtest.h>

#include <bitset>

#include "frac.hpp"
#include "matrix.hpp"

TEST(row_reduction, normal) {
  using Q = Frac<>;
  const int n = 4;
  const int m = 5;
  vector<vector<Q>> a = {
      {1, 2, 3, 1, 6}, {2, -1, 1, -4, 3}, {5, 6, 11, -7, 12}, {2, 2, 4, 2, 12}};
  vector<int> pivots = row_reduction(a, n, m);
  EXPECT_EQ(a, vector<vector<Q>>({{1, 2, 3, 1, 6},
                                  {0, 1, 1, Q(6, 5), Q(9, 5)},
                                  {0, 0, 0, 1, Q(3, 2)},
                                  {0, 0, 0, 0, 0}}));
  EXPECT_EQ(pivots, vector<int>({0, 1, 3}));
}

TEST(row_reduction, bool) {
  const int n = 4;
  const int m = 5;
  using B = bitset<m>;
  auto rb = [](string s) {
    reverse(s.begin(), s.end());
    return B(s);
  };
  vector<B> a = {rb("01010"), rb("10110"), rb("10001"), rb("00100")};
  vector<int> pivots = row_reduction(a, n, m);
  EXPECT_EQ(a, vector<B>({rb("10110"), rb("01010"), rb("00111"), rb("00011")}));
  EXPECT_EQ(pivots, vector<int>({0, 1, 2, 3}));
}
