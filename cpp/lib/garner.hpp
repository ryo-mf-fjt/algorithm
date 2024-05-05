#include "base.hpp"
#include "gcd.hpp"
#include "mod.hpp"

template <typename T, typename It>
T garner(It rs, It mods, int n) {
  vector<ll> c(n);
  rep(i, n) {
    ll m = mods[i];
    ll s = 0;
    ll p = 1;
    rep(j, i) {
      s += (c[j] * p) % m;
      s %= m;
      p *= mods[j];
      p %= m;
    }
    c[i] = reg_mod(rs[i] - s, m) * inv_mod_m(p, m) % m;
  }
  T x = 0;
  T p = 1;
  rep(i, n) {
    x += T(c[i]) * p;
    p *= mods[i];
  }
  return x;
}

template <typename T, ll... mods>
T garner(const Mod<mods>&... rs) {
  ll _mods[] = {mods...};
  ll _rs[] = {rs.val...};
  int n = sizeof...(mods);
  return garner<T>(_rs, _mods, n);
}
