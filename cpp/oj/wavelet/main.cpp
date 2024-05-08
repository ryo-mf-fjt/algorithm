// https://judge.yosupo.jp/problem/range_kth_smallest --system

#include "../../lib/base.hpp"
#include "../../lib/wavelet.hpp"

int n, q;
int a[200000];

Wavelet<30, BitVec<200000>> wavelet;

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> n >> q;
  rep(i, n) { cin >> a[i]; }
  wavelet.init(a, a + n);
  rep(i, q) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << wavelet.nth_smallest(l, r, k) << endl;
  }
}
