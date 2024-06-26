#include "base.hpp"
#include "mod.hpp"
#include "primitive_root.hpp"
#include "util/base_fft.hpp"
#include "util/pow2_ceil.hpp"

extern const int ntt_mod_p_1 = 998244353;
extern const int ntt_mod_p_2 = 167772161;
extern const int ntt_mod_p_3 = 469762049;

constexpr int pow2_divisor(int x, int n) {
  return x % (n * 2) == 0 ? pow2_divisor(x, n * 2) : n;
}

template <int mod_p = ntt_mod_p_1>
class NTT {
 public:
  constexpr static int MAX_N = pow2_divisor(mod_p - 1, 1);
  using Mod = Mod<mod_p>;
  using V = vector<Mod>;

 public:
  constexpr static int r = primitive_root<mod_p>::value;
  constexpr static int inv_r = const_inv_mod_p(r, mod_p);

 public:
  template <typename It>
  static V t(It first, It last, int ntt_n) {
    int _ntt_n = pow2_ceil(ntt_n);
    V x(_ntt_n);
    copy(first, last, x.begin());
    int e = const_pow_mod(r, (mod_p - 1) / _ntt_n, mod_p);
    V ep(_ntt_n);
    ep[0] = 1;
    for (int i = 1; i < _ntt_n; ++i) {
      ep[i] = ep[i - 1] * e;
    }
    base_fft_t(x.data(), _ntt_n, ep);
    return x;
  }
  template <typename T>
  static V t(const vector<T>& x, int ntt_n) {
    return t(x.begin(), x.end(), ntt_n);
  }

  template <typename It>
  static V inv_t(It first, It last, int ntt_n) {
    int _ntt_n = pow2_ceil(ntt_n);
    V x(_ntt_n);
    copy(first, last, x.begin());
    int e = const_pow_mod(inv_r, (mod_p - 1) / _ntt_n, mod_p);
    V ep(_ntt_n);
    ep[0] = 1;
    for (int i = 1; i < _ntt_n; ++i) {
      ep[i] = ep[i - 1] * e;
    }
    base_fft_t(x.data(), _ntt_n, ep);
    rep(i, _ntt_n) { x[i] /= _ntt_n; }
    return x;
  }
  template <typename T>
  static V inv_t(const vector<T>& x, int ntt_n) {
    return inv_t(x.begin(), x.end(), ntt_n);
  }

  // x の長さ + y の長さ - 1 <= MAX_N
  // 結果の長さは max(|x|, 1) + max(|y|, 1) - 1
  template <typename XIt, typename YIt>
  static V conv(XIt x_first, XIt x_last, YIt y_first, YIt y_last) {
    int n = max(int(x_last - x_first), 1) + max(int(y_last - y_first), 1) - 1;
    int _ntt_n = pow2_ceil(n);
    V a = t(x_first, x_last, _ntt_n);
    V b = t(y_first, y_last, _ntt_n);
    V c(_ntt_n);
    rep(i, _ntt_n) { c[i] = a[i] * b[i]; }
    V x = inv_t(c.begin(), c.end(), _ntt_n);
    x.erase(x.begin() + n, x.end());
    return x;
  }
  template <typename T, typename U>
  static V conv(const vector<T>& x, const vector<U>& y) {
    return conv(x.begin(), x.end(), y.begin(), y.end());
  }

  template <typename T>
  static vector<T> debug(const vector<T>& x) {
    V y(x);
    while (!y.empty() && y.back() == T()) {
      y.pop_back();
    }
    return y;
  }
};
