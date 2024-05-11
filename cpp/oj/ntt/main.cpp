// https://judge.yosupo.jp/problem/convolution_mod --system

#include "../../lib/base.hpp"
#include "../../lib/mod.hpp"
#include "../../lib/ntt.hpp"

using M = Mod<998244353>;

int n, m;
M a[1 << 19];
M b[1 << 19];

int main() {
  scanf("%d%d", &n, &m);
  rep(i, n) {
    int _a;
    scanf("%d", &_a);
    a[i] = _a;
  }
  rep(i, m) {
    int _b;
    scanf("%d", &_b);
    b[i] = _b;
  }
  vector<M> ans = NTT<>::conv(a, a + n, b, b + m);
  rep(i, n + m - 1) {
    printf("%lld%c", ans[i].val, i != n + m - 2 ? ' ' : '\n');
  }
}
