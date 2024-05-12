#include "fps.hpp"
#include "util/ntt_polynomial_mul.hpp"

// k = 3 なら
// a_3 = c_2 * a_2 + c_1 * a_1 + c_0 * a_0
template <typename CIt, typename AIt,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul,
          typename T = typename iterator_traits<CIt>::value_type,
          typename Negate = negate<T>>
T nth_linear_recurrence(CIt c, AIt a, int k, ll n) {
  using VIt = typename vector<T>::iterator;
  vector<T> g(k + 1);
  g[0] = 1;
  for (int i = 1; i <= k; ++i) {
    g[i] = -c[k - i];
  }
  vector<T> f = PolynomialMul<AIt, VIt>()(a, k, g.begin(), k);
  f.erase(f.begin() + k, f.end());
  return nth_fps_div<VIt, VIt, PolynomialMul, T, Negate>(f.begin(), k,
                                                         g.begin(), k + 1, n);
}
