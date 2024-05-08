// https://judge.yosupo.jp/problem/static_range_count_distinct --system

#include <set>

#include "../../lib/base.hpp"
#include "../../lib/compress.hpp"
#include "../../lib/mo.hpp"

int n, q;
int a[500000];

int c[500000];
Mo mo;

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> n >> q;
  rep(i, n) { cin >> a[i]; }
  compress(a, n);
  rep(i, q) {
    int l, r;
    cin >> l >> r;
    mo.add_query(l, r);
  }
  int s = 0;
  vector<int> ans = mo.make_answers(
      [&](int i) {
        if (!c[a[i]]) {
          ++s;
        }
        ++c[a[i]];
      },
      [&](int i) {
        --c[a[i]];
        if (!c[a[i]]) {
          --s;
        }
      },
      [&](int, int) { return s; });
  for (int v : ans) {
    cout << v << endl;
  }
}
