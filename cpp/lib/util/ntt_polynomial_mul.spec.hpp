#include <gtest/gtest.h>

#include "../mod.hpp"
#include "ntt_polynomial_mul.hpp"

TEST(TwoVariablePolynomialMul, normal) {
  using M = Mod<ntt_mod_p_1>;
  using VV = vector<vector<M>>;
  using VVIt = VV::iterator;
  VV x = {{0, 1}, {1}};
  EXPECT_EQ(
      (TwoVariablePolynomialMul<VVIt, VVIt>()(x.begin(), 2, x.begin(), 2)),
      VV({{0, 0, 1}, {0, 2}, {1}}));
}
