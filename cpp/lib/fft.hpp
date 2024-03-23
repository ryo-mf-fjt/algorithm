#include <complex>

#include "base.hpp"
#include "base_fft.hpp"

template <typename D = double>
class FFT {
 private:
  constexpr static int pow2_ceil(int n, int _n = 1) {
    return n <= _n ? _n : pow2_ceil(n, _n * 2);
  }

 public:
  using C = complex<D>;
  using V = vector<C>;

 public:
  template <typename It>
  static V t(It first, It last, int fft_n) {
    int _fft_n = pow2_ceil(fft_n);
    V x(_fft_n);
    copy(first, last, x.begin());
    V ep(_fft_n);
    rep(i, _fft_n) { ep[i] = polar(1.0, 2 * M_PI / _fft_n * i); }
    V y(_fft_n);
    V tmp(_fft_n);
    base_fft_t(x.data(), _fft_n, y.data(), ep, tmp.data());
    return y;
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
    V ep(_fft_n);
    rep(i, _fft_n) { ep[i] = polar(1.0, -2 * M_PI / _fft_n * i); }
    V y(_fft_n);
    V tmp(_fft_n);
    base_fft_t(x.data(), _fft_n, y.data(), ep, tmp.data());
    rep(i, _fft_n) { y[i] /= _fft_n; }
    return y;
  }
  template <typename T>
  static V inv_t(const vector<T>& x, int fft_n) {
    return inv_t(x.begin(), x.end(), fft_n);
  }

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

  static vector<complex<int>> round(const V& x) {
    vector<complex<int>> y;
    transform(x.begin(), x.end(), back_inserter(y), [](auto& v) {
      return complex<int>(std::round(v.real()), std::round(v.imag()));
    });
    return y;
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
