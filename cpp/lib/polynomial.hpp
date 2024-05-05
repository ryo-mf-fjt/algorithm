#include <functional>

#include "mod.hpp"
#include "ntt.hpp"

template <typename FIt, typename GIt, int mod_p = ntt_mod_p_1>
class ModNTTPolynomialMul {
 public:
  vector<Mod<mod_p>> operator()(FIt f, int fn, GIt g, int gn) {
    return NTT<mod_p>::conv(f, f + fn, g, g + gn);
  }
};

template <typename FIt, typename GIt>
using NTTPolynomialMul = ModNTTPolynomialMul<FIt, GIt>;

// g[0] = 1 とする
template <typename FIt, typename GIt,
          typename T = typename iterator_traits<FIt>::value_type,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul>
T nth_polynomial_div(FIt f, int fn, GIt g, int gn, ll n) {
  using VTIt = typename vector<T>::iterator;
  if (n == 0) {
    return fn ? f[0] : 0;
  }
  vector<T> sg(g, g + gn);
  for (int i = 1; i < gn; i += 2) {
    sg[i] *= -1;
  }
  vector<T> gsg = PolynomialMul<GIt, VTIt>()(g, gn, sg.begin(), gn);
  vector<T> p(gn);
  rep(i, gn) { p[i] = gsg[2 * i]; }
  vector<T> fsg = PolynomialMul<FIt, VTIt>()(f, fn, sg.begin(), gn);
  if (n % 2 == 0) {
    int un = (fn + gn) / 2;
    vector<T> u(un);
    rep(i, un) { u[i] = fsg[2 * i]; }
    return nth_polynomial_div<VTIt, VTIt, T, PolynomialMul>(
        u.begin(), un, p.begin(), gn, n / 2);
  } else {
    int vn = (fn + gn - 1) / 2;
    vector<T> v(vn);
    rep(i, vn) { v[i] = fsg[2 * i + 1]; }
    return nth_polynomial_div<VTIt, VTIt, T, PolynomialMul>(
        v.begin(), vn, p.begin(), gn, (n - 1) / 2);
  }
}
