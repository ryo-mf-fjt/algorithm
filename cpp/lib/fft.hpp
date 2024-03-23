#include "base.hpp"
#include "mod.hpp"
#include "primitive_root.hpp"

const int fft_mod_p_1 = 998244353;
const int fft_mod_p_2 = 167772161;
const int fft_mod_p_3 = 469762049;

constexpr int pow2_divisor(int x, int n) {
  return x % (n * 2) == 0 ? pow2_divisor(x, n * 2) : n;
}

template <int mod_p = fft_mod_p_1>
class fft {
 private:
  constexpr static int pow2_ceil(int n, int _n = 1) {
    return n <= _n ? _n : pow2_ceil(n, _n * 2);
  }

 public:
  constexpr static int MAX_N = pow2_divisor(mod_p - 1, 1);
  using Mod = Mod<mod_p>;
  using V = vector<Mod>;

 public:
  constexpr static int r = primitive_root<mod_p>::value;
  constexpr static int inv_r = const_inv_mod_p(r, mod_p);

 public:
  template <typename It>
  static V t(It first, It last, int fft_n) {
    int _fft_n = pow2_ceil(fft_n);
    V x(_fft_n);
    copy(first, last, x.begin());
    int e = const_pow_mod(r, (mod_p - 1) / _fft_n, mod_p);
    return _t(x, e);
  }
  template <typename T>
  static V t(const vector<T>& x, int fft_n) {
    return t(x.begin(), x.end(), fft_n);
  }

  template <typename It>
  static V inv_t(It first, It last, int fft_n) {
    int _fft_n = pow2_ceil(fft_n);
    V x(_fft_n);
    copy(first, last, x.begin());
    int e = const_pow_mod(inv_r, (mod_p - 1) / _fft_n, mod_p);
    V y = _t(x, e);
    int inv_underscore_fft_n = const_inv_mod_p(_fft_n, mod_p);
    rep(i, _fft_n) { y[i] *= inv_underscore_fft_n; }
    return y;
  }
  template <typename T>
  static V inv_t(const vector<T>& x, int fft_n) {
    return inv_t(x.begin(), x.end(), fft_n);
  }

  // x の長さ + y の長さ - 1 <= MAX_N
  template <typename It>
  static V conv(It x_first, It x_last, It y_first, It y_last) {
    int _fft_n = pow2_ceil((x_last - x_first) + (y_last - y_first) - 1);
    V a = t(x_first, x_last, _fft_n);
    V b = t(y_first, y_last, _fft_n);
    V c(_fft_n);
    rep(i, _fft_n) { c[i] = a[i] * b[i]; }
    return inv_t(c.begin(), c.end(), _fft_n);
  }
  template <typename T, typename U>
  static V conv(const vector<T>& x, const vector<U>& y) {
    return conv(x.begin(), x.end(), y.begin(), y.end());
  }

  static V debug(const V& x) {
    V y(x);
    while (!y.empty() && y.back() == 0) {
      y.pop_back();
    }
    return y;
  }

 private:
  static V _t(const V& x, const Mod& e) {
    int n = x.size();

    if (n == 1) {
      return x;
    }

    V ep(n);
    ep[0] = 1;
    for (int i = 1; i < n; ++i) {
      ep[i] = ep[i - 1] * e;
    }

    V a[2] = {V(n / 2), V(n / 2)};
    rep(i, 2) {
      rep(j, n) { a[i][j % (n / 2)] += x[j] * ep[i * j]; }
    }

    V y[2] = {_t(a[0], e * e), _t(a[1], e * e)};

    V z(n);
    rep(i, n) { z[i] = y[i % 2][i / 2]; }
    return z;
  }
};
