#include <gtest/gtest.h>

#include "linear_recurrence.hpp"
#include "mod.hpp"

TEST(nth_linear_recurrence, normal) {
  using M = Mod<ntt_mod_p_1>;
  vector<M> c = {1, 1};
  vector<M> a = {0, 1};
  EXPECT_EQ(nth_linear_recurrence(c.begin(), a.begin(), 2, 12), M(144));
}
