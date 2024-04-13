#include "base.hpp"
#include "bit_op.hpp"

template <int N>
class BitVec {
 public:
  const static int M = (N + 63) / 64;
  const static int L = N / 64;

 public:
  ull bit[M];
  int acc[L + 1];

 public:
  BitVec() { init(); }
  template <typename It>
  BitVec(It first, It last) {
    init(first, last);
  }

  void init() {
    fill_n(bit, M, 0);
    fill_n(acc, L + 1, 0);
  }
  template <typename It>
  void init(It first, It last) {
    fill_n(bit, M, 0);
    int n = last - first;
    rep(i, n) { bit[i / 64] += ull(first[i]) << i % 64; }

    acc[0] = 0;
    for (int i = 1; i <= L; ++i) {
      acc[i] = acc[i - 1] + bit_popcount(bit[i - 1]);
    }
  }

  // 0 から i - 1 までの和
  int sum(int i) {
    return acc[i / 64] + bit_popcount(bit[i / 64] & ((ull(1) << i % 64) - 1));
  }

  // i から j - 1 までの和
  int sum(int i, int j) { return sum(j) - sum(i); }

  int get(int i) { return (bit[i / 64] >> i % 64) & 1; }

  vector<int> debug(int n) {
    vector<int> x(n);
    rep(i, n) { x[i] = get(i); }
    return x;
  }
};
