// https://judge.yosupo.jp/problem/segment_add_get_min --system

#include "../../lib/base.hpp"
#include "../../lib/li_chao.hpp"

const ll inf = 3e18;

int n, q;
ll l[200000];
ll r[200000];
ll a[200000];
ll b[200000];
int t[200000];
ll ql[200000];
ll qr[200000];
ll qa[200000];
ll qb[200000];

vector<ll> comp;

LiChao<ll, 200000> lc(inf);

int lb(ll x) { return lower_bound(comp.begin(), comp.end(), x) - comp.begin(); }

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> n >> q;
  rep(i, n) { cin >> l[i] >> r[i] >> a[i] >> b[i]; }
  rep(i, q) {
    cin >> t[i];
    if (t[i] == 0) {
      cin >> ql[i] >> qr[i] >> qa[i] >> qb[i];
    } else {
      cin >> ql[i];
    }
  }
  rep(i, q) {
    if (t[i] != 0) {
      comp.push_back(ql[i]);
    }
  }
  sort(comp.begin(), comp.end());
  comp.erase(unique(comp.begin(), comp.end()), comp.end());
  rep(i, n) {
    l[i] = lb(l[i]);
    r[i] = lb(r[i]);
  }
  rep(i, q) {
    if (t[i] == 0) {
      ql[i] = lb(ql[i]);
      qr[i] = lb(qr[i]);
    } else {
      ql[i] = lb(ql[i]);
    }
  }
  rep(i, n) {
    lc.add(l[i], r[i], [=](int k) { return a[i] * comp[k] + b[i]; });
  }
  rep(i, q) {
    if (t[i] == 0) {
      lc.add(ql[i], qr[i], [=](int k) { return qa[i] * comp[k] + qb[i]; });
    } else {
      ll x = lc.get(ql[i]);
      if (x != inf) {
        cout << x << endl;
      } else {
        cout << "INFINITY" << endl;
      }
    }
  }
}
