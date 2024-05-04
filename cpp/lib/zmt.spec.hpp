#include <gtest/gtest.h>

#include "zmt.hpp"

TEST(divisor_zt, normal) {
  const int n = 6;
  vector<int> f(n + 1);
  for (int i = 1; i <= n; ++i) {
    f[i] = i * i;
  }
  auto g = divisor_zt(n, f.begin());
  g.erase(g.begin());
  EXPECT_EQ(g, vector<int>({f[1], f[2] + f[1], f[3] + f[1], f[4] + f[2] + f[1],
                            f[5] + f[1], f[6] + f[3] + f[2] + f[1]}));
}

TEST(divisor_mt, normal) {
  const int n = 12;
  vector<int> f(n + 1);
  for (int i = 1; i <= n; ++i) {
    f[i] = i * i;
  }
  auto g = divisor_zt(n, f.begin());
  auto h = divisor_mt(n, g.begin());
  EXPECT_EQ(h, f);
}

TEST(multiple_zt, normal) {
  const int n = 6;
  vector<int> f(n + 1);
  for (int i = 1; i <= n; ++i) {
    f[i] = i * i;
  }
  auto g = multiple_zt(n, f.begin());
  g.erase(g.begin());
  EXPECT_EQ(g,
            vector<int>({f[1] + f[2] + f[3] + f[4] + f[5] + f[6],
                         f[2] + f[4] + f[6], f[3] + f[6], f[4], f[5], f[6]}));
}

TEST(multiple_mt, normal) {
  const int n = 12;
  vector<int> f(n + 1);
  for (int i = 1; i <= n; ++i) {
    f[i] = i * i;
  }
  auto g = multiple_zt(n, f.begin());
  auto h = multiple_mt(n, g.begin());
  EXPECT_EQ(h, f);
}
