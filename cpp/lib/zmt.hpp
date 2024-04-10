#include "base.hpp"

// mode = 0 なら上位集合版
template <typename It>
auto subset_zt(int n, It f_it, int mode = 1) {
  vector<iterator_traits<It>::value_type> g(f_it, f_it + (1 << n));
  rep(i, n) {
    rep(j, 1 << n) {
      if ((j >> i) & 1 == mode) {
        g[j] += g[j ^ (1 << i)];
      }
    }
  }
  return g;
}

// mode = 0 なら上位集合版
template <typename It>
auto subset_mt(int n, It g_it, int mode = 1) {
  vector<iterator_traits<It>::value_type> f(g_it, g_it + (1 << n));
  rep(i, n) {
    rep(j, 1 << n) {
      if ((j >> i) & 1 == mode) {
        f[j] -= f[j ^ (1 << i)];
      }
    }
  }
  return f;
}
