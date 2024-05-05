#include "base.hpp"
#include "mod.hpp"

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

template <typename T>
T inv_mod_m(const T& x, const T& mod) {
  T p, q;
  gcd_ex(x, mod, p, q);
  return reg_mod(p, mod);
}
template <ll mod>
Mod<mod> inv_mod_m(const Mod<mod>& x) {
  return inv_mod_m(x.val, mod);
}
