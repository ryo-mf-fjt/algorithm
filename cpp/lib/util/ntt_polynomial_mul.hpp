#include "../mod.hpp"
#include "../ntt.hpp"

template <typename FIt, typename GIt, int mod_p = ntt_mod_p_1>
class _NTTPolynomialMul {
 public:
  vector<Mod<mod_p>> operator()(FIt f, int fn, GIt g, int gn) {
    return NTT<mod_p>::conv(f, f + fn, g, g + gn);
  }
};

template <typename FIt, typename GIt>
using NTTPolynomialMul = _NTTPolynomialMul<FIt, GIt>;

template <typename FIt, typename GIt, int mod_p = ntt_mod_p_1>
class _NTT2VariablePolynomialMul {
 public:
  vector<vector<Mod<mod_p>>> operator()(FIt f, int fn, GIt g, int gn) {
    int w = fn + gn - 1;
    int fyn = 0;
    rep(i, fn) { fyn = max(int(f[i].size()), fyn); }
    int gyn = 0;
    rep(i, gn) { gyn = max(int(g[i].size()), gyn); }
    vector<Mod<mod_p>> ff(w * (fyn - 1) + fn);
    rep(i, fn) {
      rep(j, int(f[i].size())) { ff[i + w * j] = f[i][j]; }
    }
    vector<Mod<mod_p>> gg(w * (gyn - 1) + gn);
    rep(i, gn) {
      rep(j, int(g[i].size())) { gg[i + w * j] = g[i][j]; }
    }
    vector<Mod<mod_p>> xx =
        NTT<mod_p>::conv(ff.begin(), ff.end(), gg.begin(), gg.end());
    vector<vector<Mod<mod_p>>> x(w, vector<Mod<mod_p>>(fyn + gyn - 1));
    rep(i, w) {
      rep(j, fyn + gyn - 1) { x[i][j] = xx[i + w * j]; }
      while (!x[i].empty() && x[i].back() == Mod<mod_p>(0)) {
        x[i].pop_back();
      }
    }
    return x;
  }
};

template <typename FIt, typename GIt>
using NTT2VariablePolynomialMul = _NTT2VariablePolynomialMul<FIt, GIt>;
