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
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> d >> k;
  rep(i, d) {
    int _a;
    cin >> _a;
    a[i] = _a;
  }
  rep(i, d) {
    int _c;
    cin >> _c;
    c[d - i - 1] = _c;
  }
  M ans = nth_linear_recurrence(c, a, d, k);
  cout << ans << endl;
}
