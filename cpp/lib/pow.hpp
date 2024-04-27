#include "base.hpp"

template <typename T>
T b_pow(const T& x, ll n, const T& e = 1) {
  T m = e;
  T p = x;
  ll _n = n;
  while (_n > 0) {
    if (_n & 1) {
      m *= p;
    }
    p *= p;
    _n >>= 1;
  }
  return m;
}

constexpr int const_pow_mod(int x, ll n, int mod) {
  return n == 0  ? 1
         : n & 1 ? const_pow_mod(ll(x) * x % mod, n >> 1, mod) * ll(x) % mod
                 : const_pow_mod(ll(x) * x % mod, n >> 1, mod);
}

constexpr int const_inv_mod_p(int x, int mod_p) {
  return const_pow_mod(x, mod_p - 2, mod_p);
}
