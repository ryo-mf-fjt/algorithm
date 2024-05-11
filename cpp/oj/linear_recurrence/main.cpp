// https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\ --system

#include "../../lib/base.hpp"
#include "../../lib/linear_recurrence.hpp"
#include "../../lib/mod.hpp"

using M = Mod<998244353>;

int d;
ll k;
M a[100000];
M c[100000];

int main() {
  scanf("%d%lld", &d, &k);
  rep(i, d) {
    int _a;
    scanf("%d", &_a);
    a[i] = _a;
  }
  rep(i, d) {
    int _c;
    scanf("%d", &_c);
    c[d - i - 1] = _c;
  }
  M ans = nth_linear_recurrence(c, a, d, k);
  printf("%lld\n", ans.val);
}
