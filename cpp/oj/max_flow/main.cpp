// https://judge.yosupo.jp/problem/bipartitematching --system

#include "../../lib/base.hpp"
#include "../../lib/max_flow.hpp"

struct E {
  int to, cap;
};

int l, r, m;

vector<E> g[200000 + 2];

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> l >> r >> m;
  rep(i, m) {
    int a, b;
    cin >> a >> b;
    g[a].push_back({b + l, 1});
  }
  int s = l + r;
  rep(i, l) { g[s].push_back({i, 1}); }
  int t = l + r + 1;
  rep(i, r) { g[i + l].push_back({t, 1}); }
  MaxFlow<200000 + 2, int> max_flow(g, l + r + 2);
  int flow = max_flow.max_flow(s, t);
  cout << flow << endl;
  auto& gg = max_flow.gg;
  rep(i, l) {
    for (auto& e : gg[i]) {
      if (e.to != s && e.cap == 0) {
        cout << i << ' ' << (e.to - l) << endl;
      }
    }
  }
}
