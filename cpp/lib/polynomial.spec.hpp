#include <gtest/gtest.h>

#include "mod.hpp"
#include "polynomial.hpp"

TEST(nth_polynomial_div, normal) {
  using M = Mod<ntt_mod_p_1>;
  vector<M> f = {1};
  vector<M> g = {1, 1};
  EXPECT_EQ(nth_polynomial_div(f.begin(), 1, g.begin(), 2, 999999999), M(-1));
  EXPECT_EQ(nth_polynomial_div(f.begin(), 1, g.begin(), 2, 1000000000), M(1));
}
