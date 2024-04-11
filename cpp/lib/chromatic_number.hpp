#include "base.hpp"
#include "mod.hpp"
#include "tuple.hpp"

template <ll... mods>
int chromatic_number_mods(const vector<int> g[], int n) {
  using M = tuple<Mod<mods>...>;

  // adj[1 << i] = i または i に隣接する頂点集合
  vector<int> adj(1 << n);
  rep(i, n) {
    adj[1 << i] |= 1 << i;
    for (int j : g[i]) {
      adj[1 << i] |= 1 << j;
    }
  }

  // ind[i] = i 内の独立集合の数
  vector<M> ind(1 << n);
  ind[0] = make_tuple(Mod<mods>(1)...);
  for (int i = 1; i < (1 << n); ++i) {
    int p = i & -i;
    ind[i] = ind[i ^ p] + ind[i & (~adj[p])];
  }

  // ind_k[i] = (i のパリティ) * (i 内の独立集合を k 個選ぶ方法の数)
  vector<M> ind_k(1 << n);
  ind_k[0] = make_tuple(Mod<mods>(1)...);
  for (int i = 1; i < (1 << n); ++i) {
    int p = i & -i;
    ind_k[i] = ind_k[i ^ p] * make_tuple(Mod<mods>(-1)...);
  }

  rep(k, n) {
    M s;
    rep(i, 1 << n) { s += ind_k[i]; }
    if (s != make_tuple(Mod<mods>(0)...)) {
      return k;
    }
    rep(i, 1 << n) { ind_k[i] *= ind[i]; }
  }
  return n;
}

// n <= 20
int chromatic_number(const vector<int> g[], int n) {
  // 2 ^ (n * (n - 1)) < mod の積
  return chromatic_number_mods<1000000007, 1000000009, 1000000021, 1000000033,
                               1000000087, 1000000093, 1000000097, 1000000103,
                               1000000123, 1000000181, 1000000207, 1000000223,
                               1000000241>(g, n);
}
