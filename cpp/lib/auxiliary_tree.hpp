#include "base.hpp"
#include "lca.hpp"

// 引数の x は空配列でないとする
// 戻り値の x の先頭は根
template <int N>
vector<int> make_auxiliary_tree(vector<int>& x, const LCA<N>& lca) {
  auto comp = [&](int i, int j) {
    return lca.first_index[i] < lca.first_index[j];
  };

  int n = x.size();
  sort(x.begin(), x.end(), comp);
  x.resize(2 * n - 1);
  rep(i, n - 1) { x[n + i] = lca.lca(x[i], x[i + 1]); }
  sort(x.begin(), x.end(), comp);
  x.erase(unique(x.begin(), x.end()), x.end());

  int xn = x.size();
  vector<int> xp(xn);
  xp[0] = -1;
  for (int i = 1; i < xn; ++i) {
    xp[i] = lca.lca(x[i - 1], x[i]);
  }
  return xp;
}
