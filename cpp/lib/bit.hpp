#include "base.hpp"

template <typename T, int N>
class Bit {
 public:
  T bit[N + 1];

 public:
  Bit() { init(); }
  template <typename It>
  Bit(It first, It last) {
    init(first, last);
  }

  void init() { fill_n(bit, N + 1, T()); }
  template <typename It>
  void init(It first, It last) {
    vector<T> x(N + 1);
    copy(first, last, x.begin() + 1);
    rep(i, N) { x[i + 1] += x[i]; }
    rep(i, N + 1) { bit[i] = x[i] - x[i - (i & -i)]; }
  }

  void add(int i, const T& x) {
    int _i = i + 1;
    while (_i <= N) {
      bit[_i] += x;
      _i += _i & -_i;
    }
  }

  // 0 から i - 1 までの和
  T sum(int i) {
    T s = T();
    int _i = i;
    while (_i > 0) {
      s += bit[_i];
      _i -= _i & -_i;
    }
    return s;
  }

  // i から j - 1 までの和
  T sum(int i, int j) { return sum(j) - sum(i); }

  T get(int i) { return sum(i, i + 1); }

  vector<T> debug(int n) {
    vector<T> x(n);
    rep(i, n) { x[i] = get(i); }
    return x;
  }
};
