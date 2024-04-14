#include "base.hpp"
#include "bit_vec.hpp"

template <int N, int B, typename BitVec = BitVec<N>>
class Wavelet {
 public:
  int n;
  BitVec bit[B];

 public:
  Wavelet() : n(N) {}
  template <typename It>
  Wavelet(It first, It last) {
    init(first, last);
  }

  void init() {
    n = N;
    rep(k, B) { bit[k] = BitVec(); }
  }
  template <typename It>
  void init(It first, It last) {
    n = last - first;

    vector<int> x(n);
    copy(first, last, x.begin());

    for (int k = B - 1; k >= 0; --k) {
      vector<int> b(n);
      rep(i, n) { b[i] = (x[i] >> k) & 1; }
      bit[k].init(b.begin(), b.end());
      vector<int> _x;
      rep(i, 2) {
        rep(j, n) {
          if (b[j] == i) {
            _x.push_back(x[j]);
          }
        }
      }
      x = _x;
    }
  }

  int get(int i) { return nth_smallest(i, i + 1, 0); }

  // _n 番目の v の位置
  int nth(int v, int _n) {
    int i = range_count(0, n, 0, v) + _n;
    rep(k, B) {
      int b = (v >> k) & 1;
      int p = i - (b ? n - bit[k].sum(n) : 0);
      i = bit_nth(bit[k], n, b, p);
    }
    return i;
  }

  // i から j - 1 で _n 番目に小さい値
  int nth_smallest(int i, int j, int _n) {
    int s = 0;
    for (int k = B - 1; k >= 0; --k) {
      int z = j - i - (bit[k].sum(j) - bit[k].sum(i));
      if (_n >= z) {
        i = n - bit[k].sum(n) + bit[k].sum(i);
        j = n - bit[k].sum(n) + bit[k].sum(j);
        _n -= z;
        s += 1 << k;
      } else {
        i = i - bit[k].sum(i);
        j = j - bit[k].sum(j);
      }
    }
    return s;
  }

  // i から j - 1 での [a, b) の出現回数
  int range_count(int i, int j, int a, int b, int k = B - 1, int l = 0,
                  int r = 1 << B) {
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

  // i から j - 1 に出現する値で v の直後の値
  int next_value(int i, int j, int v) {
    int c = range_count(i, j, 0, v + 1);
    if (c == j - i) {
      return 1 << B;
    }
    return nth_smallest(i, j, c);
  }

  // i から j - 1 に出現する値で v の直前の値
  int prev_value(int i, int j, int v) {
    int c = range_count(i, j, 0, v);
    if (c == 0) {
      return -1;
    }
    return nth_smallest(i, j, c - 1);
  }

  vector<int> debug() {
    vector<int> x(n);
    rep(i, n) { x[i] = get(i); }
    return x;
  }

 private:
  // bit での _n 番目の b の位置
  static int bit_nth(BitVec& bit, int n, int b, int _n) {
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
};
