#include "base.hpp"

template <typename It, typename T = typename iterator_traits<It>::value_type>
vector<pair<T, int>> compress(It first, int n) {
  vector<pair<T, int>> x(n);
  rep(i, n) {
    x[i].first = first[i];
    x[i].second = i;
  }
  sort(x.begin(), x.end());
  rep(i, n) {
    first[i] =
        lower_bound(x.begin(), x.end(), make_pair(first[i], 0)) - x.begin();
  }
  return x;
}
