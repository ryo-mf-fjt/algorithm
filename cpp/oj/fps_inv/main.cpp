// https://judge.yosupo.jp/problem/inv_of_formal_power_series --system

#include "../../lib/base.hpp"
#include "../../lib/fps.hpp"
#include "../../lib/mod.hpp"

using M = Mod<998244353>;

int n;
M a[500000];

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> n;
  rep(i, n) {
    int _a;
    cin >> _a;
    a[i] = _a;
  }
  M inv_t = M(1) / a[0];
  rep(i, n) { a[i] *= inv_t; }
  vector<M> ans = fps_inv(a, n, n);
  rep(i, n) { ans[i] *= inv_t; }
  rep(i, n) { cout << ans[i] << (i != n - 1 ? ' ' : '\n') << flush; }
}
