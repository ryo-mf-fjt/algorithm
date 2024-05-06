#include <gtest/gtest.h>

#include "fps.hpp"
#include "mod.hpp"

TEST(nth_fps_div, normal) {
  using M = Mod<ntt_mod_p_1>;
  vector<M> f = {1};
  vector<M> g = {1, 1};
  EXPECT_EQ(nth_fps_div(f.begin(), 1, g.begin(), 2, 999999999), M(-1));
  EXPECT_EQ(nth_fps_div(f.begin(), 1, g.begin(), 2, 1000000000), M(1));
}

TEST(fps_inv, normal) {
  using M = Mod<ntt_mod_p_1>;
  vector<M> f = {1, 1};
  EXPECT_EQ(fps_inv(f.begin(), 2, 10),
            vector<M>({1, -1, 1, -1, 1, -1, 1, -1, 1, -1}));
}
