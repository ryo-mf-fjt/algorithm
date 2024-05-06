// https://judge.yosupo.jp/problem/convolution_mod --system

#include "../../lib/base.hpp"
#include "../../lib/mod.hpp"
#include "../../lib/ntt.hpp"

using M = Mod<998244353>;

int n, m;
M a[1 << 19];
M b[1 << 19];

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> n >> m;
  rep(i, n) {
    int _a;
    cin >> _a;
    a[i] = _a;
  }
  rep(i, m) {
    int _b;
    cin >> _b;
    b[i] = _b;
  }
  vector<M> ans = NTT<>::conv(a, a + n, b, b + m);
  rep(i, n + m - 1) {
    cout << ans[i] << (i != n + m - 2 ? ' ' : '\n') << flush;
  }
}
