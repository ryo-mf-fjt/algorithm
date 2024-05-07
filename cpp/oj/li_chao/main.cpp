// https://judge.yosupo.jp/problem/line_add_get_min --system

#include "../../lib/base.hpp"
#include "../../lib/li_chao.hpp"

const ll inf = 3e18;

int n, q;
ll a[200000];
ll b[200000];
int t[200000];
ll qa[200000];
ll qb[200000];

vector<ll> comp;
int comp_n;

LiChao<ll, 200000> lc(inf);

int lb(ll x) { return lower_bound(comp.begin(), comp.end(), x) - comp.begin(); }

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cin >> n >> q;
  rep(i, n) { cin >> a[i] >> b[i]; }
  rep(i, q) {
    cin >> t[i];
    if (t[i] == 0) {
      cin >> qa[i] >> qb[i];
    } else {
      cin >> qa[i];
    }
  }
  rep(i, q) {
    if (t[i] != 0) {
      comp.push_back(qa[i]);
    }
  }
  sort(comp.begin(), comp.end());
  comp.erase(unique(comp.begin(), comp.end()), comp.end());
  comp_n = comp.size();
  rep(i, q) {
    if (t[i] != 0) {
      qa[i] = lb(qa[i]);
    }
  }
  rep(i, n) {
    lc.add(0, comp_n, [=](int k) { return a[i] * comp[k] + b[i]; });
  }
  rep(i, q) {
    if (t[i] == 0) {
      lc.add(0, comp_n, [=](int k) { return qa[i] * comp[k] + qb[i]; });
    } else {
      ll x = lc.get(qa[i]);
      if (x != inf) {
        cout << x << endl;
      } else {
        cout << "INFINITY" << endl;
      }
    }
  }
}
