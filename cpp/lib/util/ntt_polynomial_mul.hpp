#include "../mod.hpp"
#include "../ntt.hpp"

template <typename FIt, typename GIt, int mod_p = ntt_mod_p_1>
class ModNTTPolynomialMul {
 public:
  vector<Mod<mod_p>> operator()(FIt f, int fn, GIt g, int gn) {
    return NTT<mod_p>::conv(f, f + fn, g, g + gn);
  }
};

template <typename FIt, typename GIt>
using NTTPolynomialMul = ModNTTPolynomialMul<FIt, GIt>;

template <typename FIt, typename GIt,
          template <typename, typename> typename PolynomialMul =
              NTTPolynomialMul,
          typename T = typename iterator_traits<FIt>::value_type::value_type>
class TwoVariablePolynomialMulWith {
 public:
  vector<vector<T>> operator()(FIt f, int fn, GIt g, int gn) {
    using VIt = typename vector<T>::iterator;
    int w = fn + gn - 1;
    int fyn = 0;
    rep(i, fn) { fyn = max(int(f[i].size()), fyn); }
    int gyn = 0;
    rep(i, gn) { gyn = max(int(g[i].size()), gyn); }
    vector<T> ff(w * (fyn - 1) + fn);
    rep(i, fn) {
      rep(j, f[i].size()) { ff[i + w * j] = f[i][j]; }
    }
    vector<T> gg(w * (gyn - 1) + gn);
    rep(i, gn) {
      rep(j, g[i].size()) { gg[i + w * j] = g[i][j]; }
    }
    vector<T> xx = NTTPolynomialMul<VIt, VIt>()(ff.begin(), ff.size(),
                                                gg.begin(), gg.size());
    vector<vector<T>> x(w, vector<T>(fyn + gyn - 1));
    rep(i, w) {
      rep(j, fyn + gyn - 1) { x[i][j] = xx[i + w * j]; }
      while (!x[i].empty() && x[i].back() == T(0)) {
        x[i].pop_back();
      }
    }
    return x;
  }
};

template <typename FIt, typename GIt>
using TwoVariablePolynomialMul = TwoVariablePolynomialMulWith<FIt, GIt>;
