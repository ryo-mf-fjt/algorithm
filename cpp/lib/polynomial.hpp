#include <functional>

#include "mod.hpp"
#include "ntt.hpp"

template <typename It, int mod_p = ntt_mod_p_1>
vector<Mod<mod_p>> ntt_polynomial_mul(It f, int fn, It g, int gn) {
  return NTT<mod_p>::conv(f, f + fn, g, g + gn);
}

// g[0] = 1 とする
template <typename It, typename T = typename iterator_traits<It>::value_type>
T nth_polynomial_div(It f, int fn, It g, int gn, ll n,
                     const function<vector<T>(It, int, It, int)>&
                         polynomial_mul = ntt_polynomial_mul<It, ntt_mod_p_1>) {
  if (n == 0) {
    return fn ? f[0] : 0;
  }
  vector<T> sg(g, g + gn);
  for (int i = 1; i < gn; i += 2) {
    sg[i] *= -1;
  }
  vector<T> gsg = polynomial_mul(g, gn, sg.begin(), gn);
  vector<T> p(gn);
  rep(i, gn) { p[i] = gsg[2 * i]; }
  vector<T> fsg = polynomial_mul(f, fn, sg.begin(), gn);
  if (n % 2 == 0) {
    int un = (fn + gn) / 2;
    vector<T> u(un);
    rep(i, un) { u[i] = fsg[2 * i]; }
    return nth_polynomial_div(u.begin(), un, p.begin(), gn, n / 2,
                              polynomial_mul);
  } else {
    int vn = (fn + gn - 1) / 2;
    vector<T> v(vn);
    rep(i, vn) { v[i] = fsg[2 * i + 1]; }
    return nth_polynomial_div(v.begin(), vn, p.begin(), gn, (n - 1) / 2,
                              polynomial_mul);
  }
}
