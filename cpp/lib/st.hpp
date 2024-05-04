#include <functional>

#include "base.hpp"
#include "util/pow2_ceil.hpp"

template <typename T, int N>
class St {
 public:
  constexpr static const int _N = pow2_ceil(N, 1);
  using Comp = function<T(const T&, const T&)>;

 public:
  const T bottom;
  const Comp comp;

 public:
  T st[_N * 2 - 1];

 public:
  St(const T& bottom, const Comp& comp) : bottom(bottom), comp(comp) { init(); }
  St(const T& bottom, const Comp& comp, const T& v)
      : bottom(bottom), comp(comp) {
    init(v, _N);
  }

  void init() { fill_n(st, _N * 2 - 1, bottom); }
  void init(const T& v, int n) {
    vector<T> x(n, v);
    init(x.begin(), x.end());
  }
  template <typename It>
  T init(It first, It last, int k = 0, int l = 0, int r = _N) {
    if (r - l == 1) {
      return st[k] = (first + l < last ? *(first + l) : bottom);
    }
    return st[k] = comp(init(first, last, k * 2 + 1, l, (l + r) / 2),
                        init(first, last, k * 2 + 2, (l + r) / 2, r)

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

  T query(int a, int b, int k = 0, int l = 0, int r = _N) const {
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
