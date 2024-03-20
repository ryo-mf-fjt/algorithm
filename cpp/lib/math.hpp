#include "base.hpp"

template <typename T>
T gcd(const T& a, const T& b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

template <typename T>
T b_pow(const T& x, int n, const T& e = 1) {
  T m = e;
  T p = x;
  int _n = n;
  while (_n > 0) {
    if (_n & 1) {
      m *= p;
    }
    p *= p;
    _n >>= 1;
  }
  return m;
}
