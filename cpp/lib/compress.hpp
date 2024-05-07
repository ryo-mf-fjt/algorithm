#include "base.hpp"

template <typename It, typename T = typename iterator_traits<It>::value_type>
vector<T> compress(It first, int n) {
  vector<T> x(first, first + n);
  sort(x.begin(), x.end());
  x.erase(unique(x.begin(), x.end()), x.end());
  rep(i, n) {
    first[i] = lower_bound(x.begin(), x.end(), first[i]) - x.begin();
  }
  return x;
}
