#include "base.hpp"

template <typename T>
void base_fft_t(T x[], int n, T result[], const vector<T>& ep, T tmp[]) {
  if (n == 1) {
    result[0] = x[0];
    return;
  }

  fill_n(tmp, n, 0);
  T* a[2] = {tmp, tmp + n / 2};
  int d = ep.size() / n;
  rep(i, 2) {
    rep(j, n) { a[i][j % (n / 2)] += x[j] * ep[d * i * j]; }
  }

  T* y[2] = {x, x + n / 2};
  base_fft_t(a[0], n / 2, y[0], ep, result);
  base_fft_t(a[1], n / 2, y[1], ep, result + n / 2);

  rep(i, n) { result[i] = y[i % 2][i / 2]; }
}
