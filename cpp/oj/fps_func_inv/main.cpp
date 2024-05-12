// https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series\ --system

#include "../../lib/base.hpp"
#include "../../lib/fps.hpp"
#include "../../lib/mod.hpp"

using M = Mod<998244353>;

int n;
M a[8000];

int main() {
  scanf("%d", &n);
  rep(i, n) {
    int _a;
    scanf("%d", &_a);
    a[i] = _a;
  }
  M t = a[1];
  M inv_t = M(1) / t;
  rep(i, n) { a[i] *= inv_t; }
  vector<M> ans = fps_func_inv(a, n, n);
  M p = 1;
  rep(i, n) {
    ans[i] *= p;
    p *= inv_t;
  }
  rep(i, n) { printf("%lld%c", ans[i].val, i != n - 1 ? ' ' : '\n'); }
}
