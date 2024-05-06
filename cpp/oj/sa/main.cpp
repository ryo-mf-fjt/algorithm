// https://judge.yosupo.jp/problem/suffixarray --system

#include "../../lib/base.hpp"
#include "../../lib/sa.hpp"

int n;
string s;

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> s;
  n = s.size();
  vector<int> ans = make_sa(s.begin(), n);
  rep(i, n) { printf("%d%c", ans[i], i != n - 1 ? ' ' : '\n'); }
}
