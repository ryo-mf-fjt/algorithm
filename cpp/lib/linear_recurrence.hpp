#include "ntt.hpp"
#include "polynomial.hpp"

// k = 3 なら
// a_3 = c_2 * a_2 + c_1 * a_1 + c_0 * a_0
template <typename It, typename T = typename iterator_traits<It>::value_type>
T nth_linear_recurrence(
    It c, It a, int k, ll n,
    const function<vector<T>(It, int, It, int)>& polynomial_mul =
        ntt_polynomial_mul<It, ntt_mod_p_1>) {
  vector<T> g(k + 1);
  g[0] = 1;
  for (int i = 1; i <= k; ++i) {
    g[i] = -c[k - i];
  }
  vector<T> f = polynomial_mul(a, k, g.begin(), k);
  f.erase(f.begin() + k, f.end());
  return nth_polynomial_div(f.begin(), k, g.begin(), k + 1, n);
}
