#include "../base.hpp"
#include "../bit_op.hpp"

template <typename T>
void _base_fft_t(T x[], int n, const vector<T>& ep) {
  if (n == 1) {
    return;
  }
  int hn = n >> 1;
  int d = ep.size() / n;
  rep(i, hn) {
    int j = i + hn;
    T a = x[i];
    T b = x[j];
    x[i] = a + b;
    x[j] = a * ep[d * i] + b * ep[d * j];
  }
  _base_fft_t(x, hn, ep);
  _base_fft_t(x + hn, hn, ep);
}

template <typename T>
void index_bit_reverse(T x[], int k) {
  rep(i, 1 << k) {
    int j = (bit_reverse(i) >> (32 - k)) & ((1 << k) - 1);
    if (i < j) {
      swap(x[i], x[j]);
    }
  }
}

template <typename T>
void base_fft_t(T x[], int n, const vector<T>& ep) {
  _base_fft_t(x, n, ep);
  int k = 0;
  while ((1 << k) < n) {
    ++k;
  }
  index_bit_reverse(x, k);
}
