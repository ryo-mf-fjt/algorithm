#include <gtest/gtest.h>

#include "stn.hpp"

TEST(StN, normal) {
  const int n = 30;
  using U = St1<int, n>;
  using T = StN<U, n>;
  using S = StN<T, n>;
  S st(0, plus<int>());
  rep(i, n) {
    rep(j, n) {
      rep(k, n) { st.set(1, i, j, k); }
    }
  }
  EXPECT_EQ(st.query(0, 10, 0, 20, 0, 30), 6000);
  EXPECT_EQ(st.debug(10, 20, 30),
            vector<vector<vector<int>>>(
                10, vector<vector<int>>(20, vector<int>(30, 1))));
}
