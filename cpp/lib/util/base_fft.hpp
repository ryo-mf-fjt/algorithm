#include "../base.hpp"

template <typename T>
void base_fft_t(T x[], int n, T result[], const vector<T>& ep,
                int result_step = 1) {
  if (n == 1) {
    result[0] = x[0];
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
  base_fft_t(x, hn, result, ep, result_step << 1);
  base_fft_t(x + hn, hn, result + result_step, ep, result_step << 1);
}
