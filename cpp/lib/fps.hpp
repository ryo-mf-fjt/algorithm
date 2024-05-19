#include "util/ntt_polynomial_mul.hpp"

// g[0] = 1 とする
template <typename FIt, typename GIt,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul,
          typename T = typename iterator_traits<FIt>::value_type,
          typename Negate = negate<T>>
T nth_fps_div(FIt f, int _fn, GIt g, int _gn, ll n) {
  using VIt = typename vector<T>::iterator;
  int fn = min<ll>(_fn, n + 1);
  int gn = min<ll>(_gn, n + 1);
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
  int b = n % 2;
  int vn = (fn + gn - b) / 2;
    vector<T> v(vn);
  rep(i, vn) { v[i] = fsg[2 * i + b]; }
  return nth_fps_div<VIt, VIt, PolynomialMul, T, Negate>(v.begin(), vn,
                                                         p.begin(), gn, n / 2);
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
  vector<T> f_inv = fps_inv<It, PolynomialMul, T>(f, fn, n);
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
    vector<T> x = fps_log<VIt, PolynomialMul, T>(g.begin(), gn, 2 * gn);
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

// f[0] = 1 とする
template <typename It,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul,
          typename T = typename iterator_traits<It>::value_type>
vector<T> fps_pow(It f, int fn, typename iterator_traits<It>::value_type k,
                  int n) {
  using VIt = typename vector<T>::iterator;
  vector<T> x = fps_log<It, PolynomialMul, T>(f, fn, n);
  rep(i, n) { x[i] *= k; }
  return fps_exp<VIt, PolynomialMul, T>(x.begin(), n, n);
}

template <typename It, template <typename, typename> typename PolynomialMul,
          typename T = typename iterator_traits<It>::value_type>
struct _fps_func_inv {
  template <typename FIt, typename GIt>
  using TwoVariablePolynomialMul =
      TwoVariablePolynomialMulWith<FIt, GIt, PolynomialMul>;

  vector<T> operator()(It f, int fn, int n) {
    using V = vector<T>;
    using VV = vector<V>;
    using VIt = typename V::iterator;
    using VVIt = typename VV::iterator;
    struct Negate {
      V operator()(const V &x) const {
        V t = x;
        for (auto &v : t) {
          v = -v;
        }
        return t;
      }
    };
    VV p = {{1}};
    VV q(max(fn, 1));
    q[0] = {1};
    for (int i = 1; i < fn; ++i) {
      q[i].resize(2);
      q[i][1] = -f[i];
    }
    int k = max(n - 1, 1);
    V kth_f_pows = nth_fps_div<VVIt, VVIt, TwoVariablePolynomialMul, V, Negate>(
        p.begin(), 1, q.begin(), q.size(), k);
    V x(k);
    rep(i, k) { x[i] = kth_f_pows[k - i] * k / (k - i); }
    V x_pow = fps_pow<VIt, PolynomialMul, T>(x.begin(), k, -T(1) / k, k);
    V y(n);
    for (int i = 1; i < n; ++i) {
      y[i] = x_pow[i - 1];
    }
    return y;
  }
};
// f[0] = 0 とする
template <typename It,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul,
          typename T = typename iterator_traits<It>::value_type>
vector<T> fps_func_inv(It f, int fn, int n) {
  return _fps_func_inv<It, PolynomialMul, T>()(f, fn, n);
}
