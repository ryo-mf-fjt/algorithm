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

TEST(nth_fps_div, two_variable) {
  using M = Mod<ntt_mod_p_1>;
  using V = vector<M>;
  using VV = vector<V>;
  using VVIt = VV::iterator;
  struct Negate {
    V operator()(const V &x) const {
      V t = x;
      for (auto &v : t) {
        v = -v;
      }
      return t;
    }
  };
  VV f = {{1}};
  VV g = {{1}, {0, 1}};
  EXPECT_EQ((nth_fps_div<VVIt, VVIt, NTT2VariablePolynomialMul, V, Negate>(
                f.begin(), 1, g.begin(), 2, 5)),
            V({0, 0, 0, 0, 0, -1}));
}

TEST(fps_inv, normal) {
  using M = Mod<ntt_mod_p_1>;
  vector<M> f = {1, 1};
  EXPECT_EQ(fps_inv(f.begin(), 2, 10),
            vector<M>({1, -1, 1, -1, 1, -1, 1, -1, 1, -1}));
}

TEST(fps_log, normal) {
  using M = Mod<ntt_mod_p_1>;
  vector<M> f = {1, 1};
  EXPECT_EQ(fps_log(f.begin(), 2, 5),
            vector<M>({0, 1, -M(1) / 2, M(1) / 3, -M(1) / 4}));
}

TEST(fps_exp, normal) {
  using M = Mod<ntt_mod_p_1>;
  vector<M> f = {0, 1};
  EXPECT_EQ(fps_exp(f.begin(), 2, 5),
            vector<M>({1, 1, M(1) / 2, M(1) / 6, M(1) / 24}));
}
