#include "util/ntt_polynomial_mul.hpp"

// g[0] = 1 とする
template <typename FIt, typename GIt,
          typename T = typename iterator_traits<FIt>::value_type,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul>
T nth_fps_div(FIt f, int fn, GIt g, int gn, ll n) {
  using VTIt = typename vector<T>::iterator;
  if (n == 0) {
    return fn ? f[0] : 0;
  }
  vector<T> sg(g, g + gn);
  for (int i = 1; i < gn; i += 2) {
    sg[i] *= -1;
  }
  vector<T> gsg = PolynomialMul<GIt, VTIt>()(g, gn, sg.begin(), gn);
  vector<T> p(gn);
  rep(i, gn) { p[i] = gsg[2 * i]; }
  vector<T> fsg = PolynomialMul<FIt, VTIt>()(f, fn, sg.begin(), gn);
  if (n % 2 == 0) {
    int un = (fn + gn) / 2;
    vector<T> u(un);
    rep(i, un) { u[i] = fsg[2 * i]; }
    return nth_fps_div<VTIt, VTIt, T, PolynomialMul>(u.begin(), un, p.begin(),
                                                     gn, n / 2);
  } else {
    int vn = (fn + gn - 1) / 2;
    vector<T> v(vn);
    rep(i, vn) { v[i] = fsg[2 * i + 1]; }
    return nth_fps_div<VTIt, VTIt, T, PolynomialMul>(v.begin(), vn, p.begin(),
                                                     gn, (n - 1) / 2);
  }
}

// f[0] = 1 とする
template <typename It, typename T = typename iterator_traits<It>::value_type,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul>
vector<T> fps_inv(It f, int fn, int n) {
  using VTIt = typename vector<T>::iterator;
  if (n == 0) {
    return {};
  }
  if (fn == 1) {
    vector<T> x(n);
    x[0] = 1;
    return x;
  }
  int k = 0;
  while ((1 << k) < n) {
    ++k;
  }
  vector<T> g(1 << k);
  g[0] = 1;
  int gn = 1;
  rep(i, k) {
    vector<T> gg = PolynomialMul<VTIt, VTIt>()(g.begin(), gn, g.begin(), gn);
    vector<T> fgg = PolynomialMul<It, VTIt>()(f, fn, gg.begin(), gn * 2 - 1);
    rep(i, gn) { g[i] *= 2; }
    rep(i, gn * 2) { g[i] -= fgg[i]; }
    gn <<= 1;
  }
  g.erase(g.begin() + n, g.end());
  return g;
}
