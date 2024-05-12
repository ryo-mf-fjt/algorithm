#include "debug.hpp"
#include "util/ntt_polynomial_mul.hpp"

// g[0] = 1 とする
template <typename FIt, typename GIt,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul,
          typename T = typename iterator_traits<FIt>::value_type,
          typename Negate = negate<T>>
T nth_fps_div(FIt f, int fn, GIt g, int gn, ll n) {
  using VIt = typename vector<T>::iterator;
  if (n == 0) {
    return fn ? f[0] : T();
  }
  vector<T> sg(g, g + gn);
  for (int i = 1; i < gn; i += 2) {
    sg[i] = Negate()(sg[i]);
  }
  vector<T> gsg = PolynomialMul<GIt, VIt>()(g, gn, sg.begin(), gn);
  vector<T> p(gn);
  rep(i, gn) { p[i] = gsg[2 * i]; }
  vector<T> fsg = PolynomialMul<FIt, VIt>()(f, fn, sg.begin(), gn);
  if (n % 2 == 0) {
    int un = (fn + gn) / 2;
    vector<T> u(un);
    rep(i, un) { u[i] = fsg[2 * i]; }
    return nth_fps_div<VIt, VIt, PolynomialMul, T, Negate>(
        u.begin(), un, p.begin(), gn, n / 2);
  } else {
    int vn = (fn + gn - 1) / 2;
    vector<T> v(vn);
    rep(i, vn) { v[i] = fsg[2 * i + 1]; }
    return nth_fps_div<VIt, VIt, PolynomialMul, T, Negate>(
        v.begin(), vn, p.begin(), gn, (n - 1) / 2);
  }
}

// f[0] = 1 とする
template <typename It,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul,
          typename T = typename iterator_traits<It>::value_type>
vector<T> fps_inv(It f, int fn, int n) {
  using VIt = typename vector<T>::iterator;
  int k = 0;
  while ((1 << k) < n) {
    ++k;
  }
  vector<T> g(1 << k);
  g[0] = 1;
  int gn = 1;
  rep(i, k) {
    vector<T> gg = PolynomialMul<VIt, VIt>()(g.begin(), gn, g.begin(), gn);
    vector<T> fgg =
        PolynomialMul<It, VIt>()(f, min(fn, gn * 2), gg.begin(), gn * 2 - 1);
    rep(i, gn) { g[i] *= 2; }
    rep(i, min<int>(gn * 2, fgg.size())) { g[i] -= fgg[i]; }
    gn <<= 1;
  }
  g.erase(g.begin() + n, g.end());
  return g;
}

// f[0] = 1 とする
template <typename It,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul,
          typename T = typename iterator_traits<It>::value_type>
vector<T> fps_log(It f, int fn, int n) {
  using VIt = typename vector<T>::iterator;
  if (n == 0) {
    return {};
  }
  vector<T> f_inv = fps_inv(f, fn, n);
  vector<T> df(f + 1, f + fn);
  rep(i, fn - 1) { df[i] *= (i + 1); }
  vector<T> dl = PolynomialMul<VIt, VIt>()(f_inv.begin(), n, df.begin(),
                                           min(fn - 1, n - 1));
  vector<T> x(n);
  for (int i = 1; i < n; ++i) {
    x[i] = dl[i - 1] / i;
  }
  return x;
}

// f[0] = 0 とする
template <typename It,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul,
          typename T = typename iterator_traits<It>::value_type>
vector<T> fps_exp(It f, int fn, int n) {
  using VIt = typename vector<T>::iterator;
  int k = 0;
  while ((1 << k) < n) {
    ++k;
  }
  vector<T> g(1 << k);
  g[0] = 1;
  int gn = 1;
  rep(i, k) {
    vector<T> x = fps_log(g.begin(), gn, 2 * gn);
    rep(i, 2 * gn) { x[i] = -x[i]; }
    x[0] += 1;
    rep(i, min(fn, 2 * gn)) { x[i] += f[i]; }
    vector<T> y = PolynomialMul<It, VIt>()(g.begin(), gn, x.begin(), 2 * gn);
    copy(y.begin(), y.begin() + 2 * gn, g.begin());
    gn <<= 1;
  }
  g.erase(g.begin() + n, g.end());
  return g;
}
