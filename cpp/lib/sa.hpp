#include "base.hpp"

template <typename It, typename ByIt, typename ByCntIt>
void stable_counting_sort_by(It first, int n, ByIt by, It result,
                             ByCntIt tmp_tc, ByCntIt tmp_c) {
  fill_n(tmp_tc, n, 0);
  fill_n(tmp_c, n, 0);
  rep(i, n) { ++tmp_tc[by[first[i]]]; }
  rep(i, n - 1) { tmp_tc[i + 1] += tmp_tc[i]; }
  rep(i, n) {
    auto& k = by[first[i]];
    result[(k > 0 ? tmp_tc[k - 1] : 0) + tmp_c[k]] = first[i];
    ++tmp_c[k];
  }
}

// cyclic shift array
template <typename It>
vector<int> csa(It first, int n) {
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
  vector<int> tmp_rank(n);
  vector<int> tmp_tc(n);
  vector<int> tmp_c(n);
  for (int k = 1; k < n; k *= 2) {
    rep(i, n) { csa[i] = i; }
    rep(i, n) { tmp_rank[i] = rank[(i + k) % n]; }
    stable_counting_sort_by(csa.begin(), n, tmp_rank.begin(), tmp_csa.begin(),
                            tmp_tc.begin(), tmp_c.begin());
    stable_counting_sort_by(tmp_csa.begin(), n, rank.begin(), csa.begin(),
                            tmp_tc.begin(), tmp_c.begin());
    int r = 0;
    rep(i, n) {
      if (i > 0 && (rank[csa[i - 1]] != rank[csa[i]] ||
                    rank[(csa[i - 1] + k) % n] != rank[(csa[i] + k) % n])) {
        ++r;
      }
      tmp_rank[csa[i]] = r;
    }
    rank = tmp_rank;
  }
  return csa;
}

// first[n] = '\0'
vector<int> sa(const char first[], int n) {
  auto x = csa(first, n + 1);
  x.erase(x.begin());
  return x;
}
