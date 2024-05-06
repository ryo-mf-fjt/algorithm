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
