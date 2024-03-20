#include "base.hpp"

constexpr int pow2(int n, int _n = 1) { return n <= _n ? _n : pow2(n, _n * 2); }

template <typename T, int N>
class St {
 public:
  static const int _N = pow2(N);
  using Comp = function<T(const T&, const T&)>;

 public:
  T bottom;
  Comp comp;

 public:
  T st[_N * 2 - 1];

 public:
  St(const T& bottom, const Comp& comp) : bottom(bottom), comp(comp) { init(); }

  void init() { fill_n(st, _N * 2 - 1, bottom); }
  template <typename It>
  T init(It first, int k = 0, int l = 0, int r = _N) {
    if (r - l == 1) {
      return st[k] = *(first + l);
    }
    return st[k] = comp(init(first, k * 2 + 1, l, (l + r) / 2),
                        init(first, k * 2 + 2, (l + r) / 2, r)

           );
  }

  T get(int i) { return st[i + _N - 1]; }

  void set(int i, const T& x) {
    int _i = i + _N - 1;
    st[_i] = x;
    while (_i > 0) {
      _i = (_i - 1) / 2;
      st[_i] = comp(st[_i * 2 + 1], st[_i * 2 + 2]);
    }
  }

  T query(int a, int b, int k = 0, int l = 0, int r = _N) {
    if (b <= l || r <= a) {
      return bottom;
    }
    if (a <= l && r <= b) {
      return st[k];
    }
    return comp(query(a, b, k * 2 + 1, l, (l + r) / 2),
                query(a, b, k * 2 + 2, (l + r) / 2, r)

    );
  }

  vector<T> debug(int n) { return vector<T>(st + _N - 1, st + _N - 1 + n); }
};
