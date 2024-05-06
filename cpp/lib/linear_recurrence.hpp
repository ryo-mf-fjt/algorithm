#include "fps.hpp"
#include "util/ntt_polynomial_mul.hpp"

// k = 3 なら
// a_3 = c_2 * a_2 + c_1 * a_1 + c_0 * a_0
template <typename CIt, typename AIt,
          typename T = typename iterator_traits<CIt>::value_type,
          template <typename, typename>
          typename PolynomialMul = NTTPolynomialMul>
T nth_linear_recurrence(CIt c, AIt a, int k, ll n) {
  using VTIt = typename vector<T>::iterator;
  vector<T> g(k + 1);
  g[0] = 1;
  for (int i = 1; i <= k; ++i) {
    g[i] = -c[k - i];
  }
  vector<T> f = PolynomialMul<AIt, VTIt>()(a, k, g.begin(), k);
  f.erase(f.begin() + k, f.end());
  return nth_fps_div(f.begin(), k, g.begin(), k + 1, n);
}
