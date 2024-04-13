#include "base.hpp"
#include "bit_vec.hpp"

template <typename T, int N, int B, typename Bit = BitVec<N>>
class Wavelet {
 public:
  constexpr static T MAX_V = (T(1) << B) - 1;

 public:
  int n;
  Bit bit[B];

 public:
  Wavelet() : n(N) {}
  template <typename It>
  Wavelet(It first, It last) {
    init(first, last);
  }

  void init() {
    n = N;
    rep(i, B) { bit[i].init(); }
  }
  template <typename It>
  void init(It first, It last) {
    n = last - first;

    vector<T> x(n);
    copy(first, last, x.begin());

    for (int i = B - 1; i >= 0; --i) {
      vector<int> b(n);
      rep(j, n) { b[j] = (x[j] >> i) & 1; }

      bit[i].init(b.begin(), b.end());

      vector<T> _x;
      rep(j, n) {
        if (!b[j]) {
          _x.push_back(x[j]);
        }
      }
      rep(j, n) {
        if (b[j]) {
          _x.push_back(x[j]);
        }
      }
      x = _x;
    }
  }

  T get(int k) {
    T s = 0;
    for (int i = B - 1; i >= 0; --i) {
      int b = bit[i].get(k);
      if (b) {
        s += T(1) << i;
      }
      if (b) {
        k = n - bit[i].sum(n) + bit[i].sum(k);
      } else {
        k = k - bit[i].sum(k);
      }
    }
    return s;
  }

  vector<T> debug() {
    vector<int> x(n);
    rep(i, n) { x[i] = get(i); }
    return x;
  }
};
