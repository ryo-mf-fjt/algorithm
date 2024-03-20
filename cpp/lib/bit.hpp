#include "base.hpp"

template <typename T, int N, int& n>
class Bit {
 public:
  T bit[N + 1];

 public:
  Bit() { init(); }
  template <typename It>
  Bit(It first, It last) {
    init(first, last);
  }

  void init() { fill_n(bit, n + 1, 0); }
  template <typename It>
  void init(It first, It last) {
    vector<T> x(n + 1);
    copy(first, last, x.begin() + 1);
    rep(i, n) { x[i + 1] += x[i]; }
    rep(i, n + 1) { bit[i] = x[i] - x[i - (i & -i)]; }
  }

  void add(int i, const T& x) {
    int _i = i + 1;
    while (_i <= n) {
      bit[_i] += x;
      _i += _i & -_i;
    }
  }

  // 0 から i - 1 までの和
  T sum(int i) {
    T s = 0;
    int _i = i;
    while (_i > 0) {
      s += bit[_i];
      _i -= _i & -_i;
    }
    return s;
  }

  // i から j - 1 までの和
  T sum(int i, int j) { return sum(j) - sum(i); }

  vector<T> debug() {
    vector<T> x(n);
    rep(i, n) { x[i] = sum(i, i + 1); }
    return x;
  }
};
