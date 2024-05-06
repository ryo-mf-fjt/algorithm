#include "../base.hpp"
#include "../bit_op.hpp"

template <typename T>
void _base_fft_t(T x[], int n, const vector<T>& ep) {
  for (int k = n; k >= 2; k >>= 1) {
    int hk = k >> 1;
    int d = n / k;
    for (int p = 0; p < n; p += k) {
      rep(i, hk) {
        int j = i + hk;
        T a = x[p + i];
        T b = x[p + j];
        x[p + i] = a + b;
        x[p + j] = a * ep[d * i] + b * ep[d * j];
      }
    }
  }
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
