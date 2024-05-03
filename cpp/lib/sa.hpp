#include "base.hpp"

template <typename It, typename ByIt, typename ByCntIt>
void stable_counting_sort_by(It first, int n, ByIt by, It result, int by_from,
                             int by_to, ByCntIt tmp_tc, ByCntIt tmp_c) {
  int by_n = by_to - by_from;
  fill_n(tmp_tc, by_n, 0);
  fill_n(tmp_c, by_n, 0);
  rep(i, n) { ++tmp_tc[by[first[i]] - by_from]; }
  rep(i, by_n - 1) { tmp_tc[i + 1] += tmp_tc[i]; }
  rep(i, n) {
    int k = by[first[i]] - by_from;
    result[(k > 0 ? tmp_tc[k - 1] : 0) + tmp_c[k]] = first[i];
    ++tmp_c[k];
  }
}

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
