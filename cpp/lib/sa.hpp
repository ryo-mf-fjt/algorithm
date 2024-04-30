#include "base.hpp"

vector<int> sa(char s[], int n) {
  if (n <= 1) {
    return vector<int>(n);
  }
  using P = pair<int, int>;
  using PP = pair<P, int>;
  vector<int> rank(s, s + n);
  for (int k = 1; k < n; k *= 2) {
    vector<PP> pairs(n);
    rep(i, n) { pairs[i] = PP({rank[i], i + k < n ? rank[i + k] : -1}, i); }
    sort(pairs.begin(), pairs.end());
    vector<int> tmp_rank(n);
    int r = 0;
    rep(i, n) {
      if (i > 0 && pairs[i - 1].first != pairs[i].first) {
        ++r;
      }
      tmp_rank[pairs[i].second] = r;
    }
    rank = tmp_rank;
  }
  vector<int> sa(n);
  rep(i, n) { sa[rank[i]] = i; }
  return sa;
}
