#include "base.hpp"
#include "util/stable_counting_sort_by.hpp"

// suffix array
template <typename It>
vector<int> make_sa(It first, int n) {
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
  vector<int> sa(n);
  vector<int> tmp_sa(n);
  vector<int> shifted_rank(n);
  vector<int> tmp_rank(n);
  vector<int> tmp_tc(n + 1);
  vector<int> tmp_c(n + 1);
  for (int k = 1; k < n; k *= 2) {
    rep(i, n) { sa[i] = i; }
    rep(i, n) { shifted_rank[i] = i + k < n ? rank[i + k] : -1; }
    stable_counting_sort_by(sa.begin(), n, shifted_rank.begin(), tmp_sa.begin(),
                            -1, n, tmp_tc.begin(), tmp_c.begin());
    stable_counting_sort_by(tmp_sa.begin(), n, rank.begin(), sa.begin(), 0, n,
                            tmp_tc.begin(), tmp_c.begin());
    int r = 0;
    rep(i, n) {
      if (i > 0 && (rank[sa[i - 1]] != rank[sa[i]] ||
                    shifted_rank[sa[i - 1]] != shifted_rank[sa[i]])) {
        ++r;
      }
      tmp_rank[sa[i]] = r;
    }
    rank = tmp_rank;
  }
  return sa;
}

template <typename It, typename SaIt>
vector<int> make_lcp(It first, int n, SaIt sa) {
  vector<int> rank(n);
  rep(i, n) { rank[sa[i]] = i; }
  vector<int> lcp(n - 1);
  int h = 0;
  rep(i, n) {
    if (h > 0) {
      --h;
    }
    if (rank[i] == n - 1) {
      continue;
    }
    int j = sa[rank[i] + 1];
    while (i + h < n && j + h < n && first[i + h] == first[j + h]) {
      ++h;
    }
    lcp[rank[i]] = h;
  }
  return lcp;
}
