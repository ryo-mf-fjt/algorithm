#include "base.hpp"

// mode = 0 なら上位集合版
template <typename It>
auto subset_zt(int n, It f_it, int mode = 1) {
  vector<typename iterator_traits<It>::value_type> g(f_it, f_it + (1 << n));
  rep(i, n) {
    rep(j, 1 << n) {
      if (((j >> i) & 1) == mode) {
        g[j] += g[j ^ (1 << i)];
      }
    }
  }
  return g;
}

// mode = 0 なら上位集合版
template <typename It>
auto subset_mt(int n, It g_it, int mode = 1) {
  vector<typename iterator_traits<It>::value_type> f(g_it, g_it + (1 << n));
  rep(i, n) {
    rep(j, 1 << n) {
      if (((j >> i) & 1) == mode) {
        f[j] -= f[j ^ (1 << i)];
      }
    }
  }
  return f;
}

// i は [1, n]
template <typename It>
auto divisor_zt(int n, It f_it) {
  vector<typename iterator_traits<It>::value_type> g(f_it, f_it + n + 1);
  for (int i = n; i >= 1; --i) {
    for (int j = i * 2; j <= n; j += i) {
      g[j] += g[i];
    }
  }
  return g;
}

// i は [1, n]
template <typename It>
auto divisor_mt(int n, It g_it) {
  vector<typename iterator_traits<It>::value_type> f(g_it, g_it + n + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = i * 2; j <= n; j += i) {
      f[j] -= f[i];
    }
  }
  return f;
}

// i は [1, n]
template <typename It>
auto multiple_zt(int n, It f_it) {
  vector<typename iterator_traits<It>::value_type> g(f_it, f_it + n + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = i * 2; j <= n; j += i) {
      g[i] += g[j];
    }
  }
  return g;
}

// i は [1, n]
template <typename It>
auto multiple_mt(int n, It g_it) {
  vector<typename iterator_traits<It>::value_type> f(g_it, g_it + n + 1);
  for (int i = n; i >= 1; --i) {
    for (int j = i * 2; j <= n; j += i) {
      f[i] -= f[j];
    }
  }
  return f;
}
