// https://judge.yosupo.jp/problem/chromatic_number --system

#include "../../lib/base.hpp"
#include "../../lib/chromatic_number.hpp"

int n, m;
vector<int> g[20];

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> n >> m;
  rep(i, m) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  cout << chromatic_number(g, n) << endl;
}
