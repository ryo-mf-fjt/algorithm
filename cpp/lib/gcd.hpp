#include "base.hpp"

template <typename T>
T gcd(const T& a, const T& b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}
