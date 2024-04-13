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
    rep(k, B) { bit[k].init(); }
  }
  template <typename It>
  void init(It first, It last) {
    n = last - first;

    vector<T> x(n);
    copy(first, last, x.begin());

    for (int k = B - 1; k >= 0; --k) {
      vector<int> b(n);
      rep(i, n) { b[i] = (x[i] >> k) & 1; }

      bit[k].init(b.begin(), b.end());

      vector<T> _x;
      rep(i, n) {
        if (!b[i]) {
          _x.push_back(x[i]);
        }
      }
      rep(i, n) {
        if (b[i]) {
          _x.push_back(x[i]);
        }
      }
      x = _x;
    }
  }

  T get(int i) {
    T s = 0;
    for (int k = B - 1; k >= 0; --k) {
      int b = bit[k].get(i);
      if (b) {
        s += T(1) << k;
      }
      if (b) {
        i = n - bit[k].sum(n) + bit[k].sum(i);
      } else {
        i = i - bit[k].sum(i);
      }
    }
    return s;
  }

  // i から j - 1 での v の出現回数
  int count(int i, int j, int v) {
    pair<int, int> p = sorted_range(i, j, v);
    return p.second - p.first;
  }

  // _n 番目の v の位置
  int nth(int v, int _n) {
    int i = sorted_range(0, n, v).first + _n;
    rep(k, B) {
      int b = (v >> k) & 1;
      int p = i - (b ? n - bit[k].sum(n) : 0);
      i = bit_nth(bit[k], b, p);
    }
    return i;
  }

  // i から j - 1 で _n 番目に小さい値
  T nth_smallest(int i, int j, int _n) {
    T s = 0;
    for (int k = B - 1; k >= 0; --k) {
      int z = j - i - (bit[k].sum(j) - bit[k].sum(i));
      if (_n >= z) {
        i = n - bit[k].sum(n) + bit[k].sum(i);
        j = n - bit[k].sum(n) + bit[k].sum(j);
        _n -= z;
        s += T(1) << k;
      } else {
        i = i - bit[k].sum(i);
        j = j - bit[k].sum(j);
      }
    }
    return s;
  }

  // i から j - 1 での [a, b) の出現回数
  enable_if_t<(MAX_V < MAX_V + 1), int> range_count(int i, int j, int a, int b,
                                                    int k = B - 1, int l = 0,
                                                    int r = T(1) << B) {
    if (b <= l || r <= a) {
      return 0;
    }
    if (a <= l && r <= b) {
      return j - i;
    }
    return range_count(n - bit[k].sum(n) + bit[k].sum(i),
                       n - bit[k].sum(n) + bit[k].sum(j), a, b, k - 1,
                       (l + r) / 2, r) +
           range_count(i - bit[k].sum(i), j - bit[k].sum(j), a, b, k - 1, l,
                       (l + r) / 2);
  }

  vector<T> debug() {
    vector<int> x(n);
    rep(i, n) { x[i] = get(i); }
    return x;
  }

 private:
  // bit での _n 番目の v の位置
  int bit_nth(Bit& bit, int b, int _n) {
    int l = 0, r = n;
    while (r - l > 1) {
      int m = (l + r) / 2;
      int c = b ? bit.sum(m) : m - bit.sum(m);
      if (c <= _n) {
        l = m;
      } else {
        r = m;
      }
    }
    return l;
  }

  // i から j - 1 での v がソート終了時に出現する範囲
  pair<int, int> sorted_range(int i, int j, int v) {
    for (int k = B - 1; k >= 0; --k) {
      int b = (v >> k) & 1;
      if (b) {
        i = n - bit[k].sum(n) + bit[k].sum(i);
        j = n - bit[k].sum(n) + bit[k].sum(j);
      } else {
        i = i - bit[k].sum(i);
        j = j - bit[k].sum(j);
      }
    }
    return make_pair(i, j);
  }
};
