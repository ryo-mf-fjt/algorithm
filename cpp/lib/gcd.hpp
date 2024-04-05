#include "base.hpp"

template <typename T>
T gcd(const T& a, const T& b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

template <typename T>
T gcd_ex(const T& a, const T& b, T& x, T& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  T g = gcd_ex(b, a % b, x, y);
  T tx = x;
  x = y;
  y = tx - (a / b) * y;
  return g;
}
