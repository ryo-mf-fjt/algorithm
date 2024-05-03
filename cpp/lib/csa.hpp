#include "base.hpp"
#include "util/stable_counting_sort_by.hpp"

// cyclic shift array
template <typename It>
vector<int> make_csa(It first, int n) {
  vector<pair<typename iterator_traits<It>::value_type, int>> t(n);
  rep(i, n) {
    t[i].first = first[i];
    t[i].second = i;
  }
  sort(t.begin(), t.end());
  vector<int> rank(n);
  int r = 0;
  rep(i, n) {
    if (i > 0 && t[i - 1].first != t[i].first) {
      ++r;
    }
    rank[t[i].second] = r;
  }
  vector<int> csa(n);
  vector<int> tmp_csa(n);
  vector<int> shifted_rank(n);
  vector<int> tmp_rank(n);
  vector<int> tmp_tc(n);
  vector<int> tmp_c(n);
  for (int k = 1; k < n; k *= 2) {
    rep(i, n) { csa[i] = i; }
    rep(i, n) { shifted_rank[i] = rank[(i + k) % n]; }
    stable_counting_sort_by(csa.begin(), n, shifted_rank.begin(),
                            tmp_csa.begin(), 0, n, tmp_tc.begin(),
                            tmp_c.begin());
    stable_counting_sort_by(tmp_csa.begin(), n, rank.begin(), csa.begin(), 0, n,
                            tmp_tc.begin(), tmp_c.begin());
    int r = 0;
    rep(i, n) {
      if (i > 0 && (rank[csa[i - 1]] != rank[csa[i]] ||
                    shifted_rank[csa[i - 1]] != shifted_rank[csa[i]])) {
        ++r;
      }
      tmp_rank[csa[i]] = r;
    }
    rank = tmp_rank;
  }
  return csa;
}
